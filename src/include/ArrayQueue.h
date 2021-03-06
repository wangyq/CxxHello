/*
 * ArrayQueue.h
 *
 *  Created on: 2016年1月12日
 *      Author: wang
 */

#ifndef SRC_INCLUDE_ARRAYQUEUE_H_
#define SRC_INCLUDE_ARRAYQUEUE_H_

template<class T>
class ArrayQueue {

protected:
    enum {
        INIT_SIZE = 16, INC_SIZE = 16, ENUM_NULL
    };

    static T NulVal;

    unsigned int m_iCapacity;
    unsigned int m_iIncSize;  //every time the increment size.
    unsigned int m_iHead; // header pointer of the position in which is the first element to be dequeue.
    unsigned int m_iTail; // tail pointer of the position in which is the latest element to be enqueue.
    T* m_pData;

    bool IncCapacity(unsigned int incSize);
public:
    ArrayQueue();
    ArrayQueue(unsigned int iInitialSize);
    ArrayQueue(unsigned int iInitialSize, int iIncSize);
    virtual ~ArrayQueue();

public:
    unsigned int Size();  //current size of arrayqueue
    bool isEmpty();
    bool isFull();
    T Dequeue();
    bool EnQueue(const T&);
    T& Head();
    T& Tail();
};

template<class T> T ArrayQueue<T>::NulVal = (T) 0;

template<class T>
ArrayQueue<T>::ArrayQueue() {
    // TODO Auto-generated constructor stub
    //Stack<T>(INIT_SIZE,INC_SIZE);
    m_iCapacity = INIT_SIZE;
    m_iIncSize = INC_SIZE;
    m_iHead = m_iTail = 0;
    m_pData = new T[m_iCapacity];
    if (m_pData == 0) {
        m_iCapacity = 0;
    }
}

template<class T>
ArrayQueue<T>::ArrayQueue(unsigned int iInitialSize) {
    // TODO Auto-generated constructor stub
    //Stack<T>(iInitialSize,INC_SIZE);
    m_iCapacity = iInitialSize>0? iInitialSize:INIT_SIZE;
    m_iIncSize = INC_SIZE;
    m_iHead = m_iTail = 0;
    m_pData = new T[m_iCapacity];
    if (m_pData == 0) {
        m_iCapacity = 0;
    }
}
template<class T>
ArrayQueue<T>::ArrayQueue(unsigned int iInitialSize, int iIncSize) {
    // TODO Auto-generated constructor stub
    m_iCapacity = iInitialSize>0? iInitialSize:INIT_SIZE;
    m_iIncSize = iIncSize>0?iIncSize:INC_SIZE;
    m_iHead = m_iTail = 0;
    m_pData = new T[m_iCapacity];
    if (m_pData == 0) {
        m_iCapacity = 0;
    }
}
template<class T>
ArrayQueue<T>::~ArrayQueue() {
    // TODO Auto-generated destructor stub
    delete[] m_pData;
}

template<class T>
unsigned int ArrayQueue<T>::Size() {
    // TODO Auto-generated destructor stub
    int c = 0;
    if (m_iHead <= m_iTail) {
        c = m_iTail - m_iHead;
    } else {
        c = m_iTail + (m_iCapacity - m_iHead);
    }
    return c;
}

template<class T>
bool ArrayQueue<T>::isEmpty() {
    // TODO Auto-generated destructor stub
    return m_iTail == m_iHead;
}

template<class T>
bool ArrayQueue<T>::isFull() {
    // TODO Auto-generated destructor stub
    //return ((m_iTail +1) % m_iCapacity) == m_iHead;
    return ((m_iTail + 1) == m_iHead)
            || ((m_iHead == 0) && ((m_iTail + 1) == m_iCapacity));  //run fast!
}

//===================
/**
 * The element that Dequeue first!
 */
template<class T>
T& ArrayQueue<T>::Head() {
    // TODO Auto-generated destructor stub
    if (isEmpty())
        return NulVal;
    return m_pData[m_iHead];
}

/**
 * The element that Dequeue last!
 */
template<class T>
T& ArrayQueue<T>::Tail() {
    // TODO Auto-generated destructor stub
    if (isEmpty())
        return NulVal;
    if (m_iTail == 0) {
        return m_pData[m_iCapacity - 1];
    }
    return m_pData[m_iTail - 1];
}

template<class T>
T ArrayQueue<T>::Dequeue() {
    // TODO Auto-generated destructor stub
    if (isEmpty())
        return 0;

    T& ele = m_pData[m_iHead];

    m_iHead++; //move next
    if (m_iHead >= m_iCapacity) {
        m_iHead = 0;
    }
    return ele;
}

template<class T>
bool ArrayQueue<T>::EnQueue(const T& ele) {
    // TODO Auto-generated destructor stub
    if (isFull()) {
        if (!IncCapacity(0))
            return false;
    }

    m_pData[m_iTail] = ele;
    m_iTail++;  //move to next.
    if (m_iTail >= m_iCapacity) {
        m_iTail = 0;
    }

    return true;
}

template<class T>
bool ArrayQueue<T>::IncCapacity(unsigned int incSize) {

    int curSize = Size(); //current size to store.

    if (incSize <= 0) {
        incSize = m_iIncSize;  //default inc size.
    }
    unsigned int iNewCapacity = m_iCapacity + incSize;
    T* pNew = new T[iNewCapacity];
    if (pNew == 0)
        return false;

    unsigned int i = 0;
    unsigned int index = 0;

    if (m_iHead <= m_iTail) {  //Just copy data.
        for (i = m_iHead; i < m_iTail; i++, index++) {
            pNew[index] = m_pData[i];
        }
    } else {  //copy data from two phrases.
        for (i = m_iHead; i < m_iCapacity; i++, index++) {
            pNew[index] = m_pData[i];
        }
        for (i = 0; i < m_iTail; i++, index++) { //here m_iTail == m_iCapacity-1 ?
            pNew[index] = m_pData[i];
        }
    } //end of resize

    //free memory!
    delete[] m_pData;
    m_pData = pNew;

    m_iHead = 0;
    m_iTail = curSize;
    m_iCapacity = iNewCapacity;

    return true;
}

#endif /* SRC_INCLUDE_ARRAYQUEUE_H_ */
