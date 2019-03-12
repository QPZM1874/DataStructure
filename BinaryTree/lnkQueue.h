#ifndef LINKQUEUE_H_INCLUDE
#define LINKQUEUE_H_INCLUDE

#include <cstdlib>
#include <iostream>
#include "Link.h"
#include "myQueue.h"

using namespace std;

template <class T>
class lnkQueue: public Queue <T>
{
private:
    int 	size; 				// �����е�ǰԪ�صĸ���
    Link<T>* front;				// ��ʾ��ͷ��ָ��
    Link<T>* rear;				// ��ʾ��β��ָ��
public: 						// ���е����㼯
    lnkQueue()       			// �������е�ʵ��
    {
        size = 0;
        front = rear = NULL;
    }
    ~lnkQueue()     			// ������ʵ�������ͷ���ռ�
    {
        clear();
    }

    bool isEmpty()
    {
        return (size == 0);
    }

    bool isFull()
    {
        return false;
    }

    void clear()  				// ��ն���
    {
        while (front != NULL)
        {
            rear = front;
            front = front->next;
            delete rear;
        }
        rear = NULL;
        size = 0;
    }

    bool enQueue(const T & item)   	//  item��ӣ������β
    {
        if (rear == NULL) 	 		// �ն���
        {
            front = rear = new Link<T> (item, NULL);
        }
        else   							// ����µ�Ԫ��
        {
            rear-> next = new Link<T> (item, NULL);
            rear = rear ->next;
        }
        size++;
        return true;
    }
    bool deQueue(T & item)     // ���ض�ͷԪ�ز��Ӷ�����ɾ��
    {

        if (size == 0)   	// ����Ϊ�գ�û��Ԫ�ؿɳ���
        {
            cout << "����Ϊ��" << endl;
            return false;
        }
        item = front->data;
        Link<T> * tmp = front;
        front = front -> next;
        delete tmp;
        if (front == NULL) rear = NULL;
        size--;
        return true;
    }
    bool getFront(T & item)   	       			// ���ض�ͷԪ�أ�����ɾ��
    {
        if (size == 0)   						// ����Ϊ�գ�û��Ԫ�ؿɳ���
        {
            cout << "����Ϊ��" << endl;
            return false;
        }
        item = front->data;
        return true;
    }

    void print()
    {
        if (front == NULL)
        {
            cout << "����Ϊ��" << endl;
        }
        Link<T>*p = front;
        while(p != NULL)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
};

#endif


