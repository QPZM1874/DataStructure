#ifndef LINKSTACK_H_INCLUDE
#define LINKSTACK_H_INCLUDE

#include <cstdlib>
#include <iostream>
#include "Link.h"
#include "myStack.h"

using namespace std;

// ջ����ʽʵ��
template <class T>
class lnkStack : public Stack <T>
{
private: 	                    		// ջ����ʽ�洢
    Link<T>*	top;					// ָ��ջ����ָ��
    int 		size;					// ջ��Ԫ�صĸ���
public:
    lnkStack(int defSize)  			// ���캯��������Ϊ��˳��ջ����һ�£����ã�
    {
        top = NULL;
        size = 0;
    }

    ~lnkStack()  					// ��������
    {
        clear();
    }

    virtual void clear()  					// ���ջ����
    {
        while (top != NULL)
        {
            Link<T> *tmp = top;
            top = top->next;
            delete tmp;
        }
        size = 0;
    }

    virtual bool push(const T & item)   	    		// ��ջ��������ʽʵ��
    {
        Link<T>* tmp = new Link<T>(item, top);
        top = tmp;
        size++;
        return true;
    }

    virtual bool pop(T & item)   				// ��ջ����ʽʵ��
    {
        Link<T> *tmp;
        if (size == 0)
        {
            cout << "ջΪ�գ����ܳ�ջ����" << endl;
            return false;
        }
        item = top->data;
        tmp = top->next;
        delete top;
        top = tmp;
        size--;
        return true;
    }

    virtual bool getTop(T & item)  				// ����ջ�����ݣ���������
    {
        if (size == 0)
        {
            cout << "ջΪ�գ����ܳ�ջ����"<< endl;
            return false;
        }
        item = top->data;
        return true;
    }

    virtual bool isEmpty()
    {
        return size == 0;
    }

    virtual bool isFull()
    {
        Link<T>* tmp = new Link<T>;
        if (tmp)
            return false;
        return true;
    }
    bool print()
    {
        Link<T>*tmp=new Link<T>;
        tmp=top;
        while (tmp)
        {
            cout<<tmp->data<<" ";
            tmp=tmp->next;
        }
        cout<<endl;
    }
};

#endif // LINKSTACK_H_INCLUDE
