/*
 * test_main.cxx
 *
 *  Created on: 2016年1月9日
 *      Author: wang
 */

#include <memory>
#include <iostream>
//==
//#define TEST_VFORK

//#ifdef TEST_VFORK
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


//#endif

using namespace std;

typedef long long INT;

INT gcd(INT, INT, INT*, INT*);

extern int G1();

//========= for icpc 2014 test! ===============
void test_gcd() {
	INT x, y, a, b, g;
	do {
		cout << "please enter (a,b) for calculate GCD: " << endl;
		cin >> a >> b;
		if (a == 0 || b == 0)
			break;
		g = gcd(a, b, &x, &y);
		cout << "Answer is: gcd=" << g << ", (x,y)=(" << x << "," << y << ")"
				<< endl;
	} while (true);
}

void test_icpc2014() {
	G1();
}

int fac(int x) {
	if (x <= 1)
		return 1;
	else
		return x * fac(x - 1);
}

void test_autoptr() {
	std::unique_ptr<int> a(new int(10));
	cout << *a << endl;
}

const int g_const_a = 10;
void test_const_ptr() {
	const int a = 10;
	int* p = (int*) &a;
	*p = 20;
	cout << "a=" << a << " p=" << *p << endl;

//	p = (int*)&g_const_a;
//	*p = 40;    //write violation error!

	cout << "a=" << a << " p=" << *p << endl;
	cout << "Address of a = " << &a << " , Pointer of p = " << p << endl;

}
//#ifdef TEST_VFORK
int glob = 10;
//int main()
void test_vfork(void) {
	int var;
	var = 88;
	pid_t pid = 0;
	if ((pid = vfork()) < 0) {
		printf("vfork error");
		exit(-1);
	} else if (pid == 0) { /* 子进程 */
		var = 99;
		glob++;
		//return 0;
		exit(0);
	}
	printf("pid=%d, glob=%d, var=%d\n", getpid(), glob, var);
	return;
}

void test_read(void){  
    char buf[10];  
    int n;  
    n=read(STDIN_FILENO,buf,10);  
    if(n<0){ 
        perror("read STDIN_FILENO");  
        exit(1);  
    }  
    write(STDOUT_FILENO,buf,n);  
}

//#endif  //end of TEST_VFORK

