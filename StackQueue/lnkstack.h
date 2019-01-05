#ifndef LINKSTACK_H_INCLUDE
#define LINKSTACK_H_INCLUDE

#include <cstdlib>
#include <iostream>
#include "Link.h"
#include "myStack.h"

using namespace std;

// 栈的链式实现
template <class T>
class lnkStack : public Stack <T>
{
private: 	                    		// 栈的链式存储
    Link<T>*	top;					// 指向栈顶的指针
    int 		size;					// 栈中元素的个数
public:
    lnkStack(int defSize)  			// 构造函数，参数为与顺序栈保持一致，无用！
    {
        top = NULL;
        size = 0;
    }

    ~lnkStack()  					// 析构函数
    {
        clear();
    }

    virtual void clear()  					// 清空栈内容
    {
        while (top != NULL)
        {
            Link<T> *tmp = top;
            top = top->next;
            delete tmp;
        }
        size = 0;
    }

    virtual bool push(const T & item)   	    		// 入栈操作的链式实现
    {
        Link<T>* tmp = new Link<T>(item, top);
        top = tmp;
        size++;
        return true;
    }

    virtual bool pop(T & item)   				// 出栈的链式实现
    {
        Link<T> *tmp;
        if (size == 0)
        {
            cout << "栈为空，不能出栈操作" << endl;
            return false;
        }
        item = top->data;
        tmp = top->next;
        delete top;
        top = tmp;
        size--;
        return true;
    }

    virtual bool getTop(T & item)  				// 返回栈顶内容，但不弹出
    {
        if (size == 0)
        {
            cout << "栈为空，不能出栈操作"<< endl;
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
