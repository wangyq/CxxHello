/*
 * ChatServer.cxx
 *
 *  Created on: 2016年4月16日
 *      Author: wang
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <time.h>

//#include "TheTypeDefine.h"

#define MAX_BUF     1024        /* Maximum bytes fetched by a single read() */
#define MAX_EVENTS     5        /* Maximum number of events to be returned from a single epoll_wait() call */

/**
 *
 */
void getCurDateTime(char* buf, int size) {
    if (buf == NULL)
        return;
    static const char *wday[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep); //get current time.
    snprintf(buf, size, "%d/%d/%d %s %d:%d:%d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);
    //printf ("%d%d%d ", (1900+p->tm_year), (l+p->tm_mon), p->tm_mday);
    //printf("%s%d:%d:%d\n", wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);
}

/**
 *
 *
 */
int setnonblocking(int sock) {
    int opts = fcntl(sock, F_GETFL);
    if (opts < 0) {
        perror("fcntl(sock,F_GETFL) error!");
        return -1;
    }
    opts = opts | O_NONBLOCK;
    if (fcntl(sock, F_SETFL, opts) < 0) {
        perror("fcntl(sock, F_SETFL, opts) error!");
        return -1;
    }
    return 0;
}

int handle_accept(int fd, int epfd) {
    struct epoll_event ev;  //temp varible, it is OK?
    int newsock = 0;

    do {  //edge-triger
        struct sockaddr_in client_addr;
        socklen_t len;
        //char strHost[MAX_BUF], strPortNum[MAX_BUF];

        len = sizeof(client_addr);

        newsock = accept(fd, (struct sockaddr*) &client_addr, &len); //accept new connection and the peer address.

        if (-1 == newsock) {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                break;
            else {
                perror("accept");
                return -1;
            }
        } else { //accept ok
            printf("Connection of client %s:%d accepted.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

            setnonblocking(newsock); //set non-blocking
            ev.data.fd = newsock;
            ev.events = EPOLLIN | EPOLLET; //edge-trigger
            if (-1 == epoll_ctl(epfd, EPOLL_CTL_ADD, newsock, &ev)) {
                perror("epoll_ctl");
                return -1;
            }
        }
    } while (1);

    return 0;
}

int handle_read(int fd, int epfd) {
    int beClosed = 0;
    struct epoll_event ev;
    do {
        char buf[MAX_BUF + 1] = { 0 };
        int count = 0;
        count = recv(fd, buf, MAX_BUF, 0);
        if (-1 == count) { //no more recv operation.
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) { // no more data available
                ev.data.fd = fd;
                ev.events = EPOLLOUT | EPOLLET; //edge-trigger
                if (-1 == epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev)) {
                    perror("epoll_ctl EPOLL_CTL_MOD");
                    beClosed = 1;  //error and close it!
                }
            } else { //recv error occur!
                perror("recv error");
                beClosed = 1;
            }
            break; // finish loop now!
        } else if (0 == count) { // peer already close.
            beClosed = 1;
            break;
        } else { // already get data now!
            buf[count + 1] = '\0';
            printf("Recieving from client %d: %s\n", fd, buf);
        }
    } while (1);  //repeat read data!

    //finish this client connection.
    if (beClosed) {
        printf("Connection on descriptor %d is closed.\n", fd);
        close(fd);
    }
    return 0;
}

int handle_write(int fd, int epfd) {

    char buf[MAX_BUF + 1] = { 0 }, *pCur = buf;
    int ntotal = 0, count = 0;
    struct epoll_event ev;
    int beClosed = 0;
    snprintf(buf, MAX_BUF, "Hello, client #%d.", fd);
    ntotal = strlen(buf);
    pCur = buf;
    while (ntotal > 0) {  // more data to send!
        count = send(fd, pCur, ntotal, 0);
        if (count > 0) {
            ntotal -= count;
            pCur += count;
        } else if (count == -1) {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                ev.data.fd = fd;
                ev.events = EPOLLIN | EPOLLET; //edge-trigger
                if (-1 == epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev)) {
                    perror("epoll_ctl EPOLL_CTL_MOD of EPOLLIN");
                    beClosed = 1;  //error and close it!
                }
            } else { //error occur!
                perror("send error.");
                beClosed = 1;
            }
            break;  //finish send.
        }

        if (ntotal <= 0) {//no more data to send.
            ev.data.fd = fd;
            ev.events = EPOLLIN | EPOLLET; //edge-trigger
            if (-1 == epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev)) {
                perror("epoll_ctl EPOLL_CTL_MOD of EPOLLIN");
                beClosed = 1;  //error and close it!
            }
            break;
        }
    } //end of while
    if (beClosed) {
        printf("Close connection of client %d . ", fd);
        close(fd);
    } else { //non-close. so add EPOOLIN

    }
    return 0;
}
/*
 *
 */
//int main(int argc, const char* argv[])
int main_echoclient_stub(int argc, const char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s [ServerIP] [port] \n", argv[0]);
        printf("\t ServerIP : Server IPv4 Address, such as A.B.C.D \n");
        printf("\t port : port number and need to be greater than 1024.\n");

        return -1;
    }
    const char* strServerIP = argv[1];
    int nPort = atoi(argv[2]);
    if (nPort <= 0) {
        printf("Error Port number : %s\n", argv[2]);
        return -1;
    }

    ///定义sockfd
    int client_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    ///定义sockaddr_in
    struct sockaddr_in server_sockaddr = { 0 };
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(nPort);
    server_sockaddr.sin_addr.s_addr = inet_addr(strServerIP);

    //connect to server now...
    if (connect(client_sockfd, (struct sockaddr*) &server_sockaddr, sizeof(server_sockaddr)) < 0) {
        perror("connect to server");
        return -1;
    }

    {
        char strTime[MAX_BUF];
        getCurDateTime(strTime, sizeof(strTime) - 1);
        printf("[%s] Connected to Server %s:%d Success.\n ", strTime, strServerIP, nPort);
    }

    int linenum = 0;
    do {
        int len = 0;
        char buf[MAX_BUF + 1];
        printf("[%d] : ", linenum);
        //scanf("%s", buf);
        if (buf != fgets(buf, MAX_BUF, stdin)) {//get carridge return char.
            perror(("fgets"));
            break;
        }
        {//remove the last carriage return or newline char.
            int l = strlen(buf);
            while(l>0){
                if( (buf[l-1] == '\n') || (buf[l-1] == '\r') ){
                    buf[l-1] = '\0';
                    l--;
                }else{
                    break;
                }
            }
        }

        if ((strcmp("exit", buf) == 0) || (strcmp("quit", buf) == 0)) {
            break;
        }
        //send.
        if (-1 == send(client_sockfd, buf, strlen(buf), 0)) {
            printf("send failed.");
            break;
        }

        //recv
        len = recv(client_sockfd, buf, MAX_BUF, 0);
        if (len == -1) {
            printf("recv failed.");
            break;
        }
        buf[len] = '\0'; //end of string.
        printf("%s\n", buf);
        fflush(stdin);
        fflush(stdout);

        linenum++; //goto next line.
    } while (1);

    close(client_sockfd); // close socket.
    return 0;
}

/**
 *
 */
//int main(int argc, const char* argv[])
int main_echoserver_stub(int argc, const char* argv[]) {
    int epfd;
    unsigned short portnum = 0;

    struct epoll_event ev;
    struct epoll_event evlist[MAX_EVENTS];

    if (argc < 2) {
        printf("Usage: %s [port] \n", argv[0]);
        printf("\t port : port number and need to be greater than 1024.\n");

        return -1;
    }
    portnum = atoi(argv[1]);
    if (portnum <= 0 || portnum >= 65535) {
        printf("Port Number %s Error\n", argv[1]);
        return -1;
    }

    epfd = epoll_create(argc - 1);
    if (epfd == -1) {
        printf("epoll_create");
        return -1;
    }

    ///定义sockfd
    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    ///定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(portnum);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    ///bind，成功返回0，出错返回-1
    if (bind(server_sockfd, (struct sockaddr *) &server_sockaddr, sizeof(server_sockaddr)) == -1) {
        perror("bind");
        exit(-1);
    }

    //set non blocking
    setnonblocking(server_sockfd);

    ///listen，成功返回0，出错返回-1
    ///proc/sys/net/ipv4/tcp_max_syn_backlog ,default value is 128
    if (listen(server_sockfd, 0) == -1) {
        perror("listen");
        exit(-1);
    }

    ev.events = EPOLLIN | EPOLLET; //edge-trigged
    ev.data.fd = server_sockfd;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, server_sockfd, &ev) == -1) {
        perror("epoll_ctl");
        return -1;
    }

    {
        char strTime[MAX_BUF];
        getCurDateTime(strTime, sizeof(strTime) - 1);
        printf("[%s] Server start at port %d now ......\n ", strTime, portnum);
    }

    /* The event loop 事件循环*/
    while (1) {
        int n, i;
        n = epoll_wait(epfd, evlist, MAX_EVENTS, -1);
        printf("Ready: %d\n", n);

        if (-1 == n) { //error occur!
            if ( errno == EINTR) {
                printf("Get an interrupted signal ");
                continue;
            } else {
                perror(" epoll_wait error!");
                exit(-1);
            }
        } else if (0 == n) {
            //epoll_wait timeout and no file descriptor became ready.
        }

        // process every active event.
        for (i = 0; i < n; i++) {
            printf("  fd=%d; events: %s%s%s%s\n", evlist[i].data.fd, (evlist[i].events & EPOLLIN) ? "EPOLLIN " : "", (evlist[i].events & EPOLLOUT) ? "EPOLLOUT " : "", (evlist[i].events & EPOLLHUP) ? "EPOLLHUP " : "",
                    (evlist[i].events & EPOLLERR) ? "EPOLLERR " : "");

            if (evlist[i].events & EPOLLIN) {
                if (evlist[i].data.fd == server_sockfd) {
                    handle_accept(evlist[i].data.fd, epfd);
                } else {
                    handle_read(evlist[i].data.fd, epfd);
                }
            } else if (evlist[i].events & EPOLLOUT) {
                handle_write(evlist[i].data.fd, epfd);
            } else { //if ( evlist[i].events & (EPOLLERR | EPOLLHUP | EPOLLRDHUP) ){ // || (!(evlist[i].events & EPOLLIN))) {

                /* 发生了错误或者被挂断，或者没有数据可读
                 * An error has occured on this fd, or the socket is not ready for reading (why were we notified then?) */

                printf("Connection of fd: %d closed. \n", evlist[i].data.fd);
                if (close(evlist[i].data.fd) == -1) {
                    perror("close fd");
                    //exit(-1);  //
                }
                continue;

            } // end if
        } //end of for
    } //end of while

    close(server_sockfd);

    return 0;
}

