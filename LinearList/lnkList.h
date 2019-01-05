#ifndef LINKLIST_H_INCLUDE
#define LINKLIST_H_INCLUDE
#include <cstdlib>
#include <iostream>

#include "myList.h"

using namespace std;

// 设元素的类型为T，定义单链表的结点类型Link
// 原则上属性应为private，此处声明为public，偷懒而已！
// 受限于编译器对模板的支持，将模板类的实现放在头文件中
//
template <class T> class Link
{
public:
    T  		data;						// 用于保存结点元素的内容
    Link<T>	* next;						// 指向后继结点的指针
public:
    Link(const T & info, Link * nextValue = NULL)   	// 具有两个参数的Link构造函数
    {
        data = info;
        next = nextValue;
    }
    Link(Link* nextValue = NULL)    	// 具有一个参数的Link构造函数
    {
        next = nextValue;
    }
};

// 单链表的类型定义。有头结点，有表尾指针
template <class T>
class lnkList : public List<T>
{
protected:
    Link<T>*  head, * tail;    				// 单链表的头、尾指针
public:
    lnkList();						// 构造函数
    ~lnkList();						// 析构函数

    // 继承自基类的方法
    virtual void clear(); 				 	// 置空线性表
    virtual bool isEmpty();				 	// 线性表为空时，返回True
    virtual bool app(const T & value);	    // 在表尾添加一个元素value，表的长度增1
    virtual bool ins(int pos, const T & value);	 	// 在位置pos上插入一个元素value，指定pos无对应位置，则插入到头或尾
    virtual bool del(int pos); 			 	        // 删除位置pos上的元素，表的长度减 1
    virtual bool getValue(int pos, T & value);		    // 返回位置pos的元素值
    virtual bool setValue(int pos, const T & value);	// 用value修改位置pos的元素值
    virtual bool getPos(int & pos, const T & value);    // 将表中值为value的元素的位置返回到pos中

    // 新增方法
    int length();                   // 返回此顺序表的当前实际长度
    void print();
    void creat();//建表
    void mysort();
    void myreverse();  //上机1题 链表逆置
    bool getValue1(int m,T & value); //上机2题 获取倒数第m个元素
    void del1(T &,T &);  //上机3题 删除min—max的元素
    lnkList<T> Hebing(lnkList<T> &);
};


template <class T>
lnkList<T> :: lnkList()
{
    head = tail = new Link<T>;//分配头结点

}
template <class T>
void lnkList<T>::creat()
{
    int n;
    T val;
    Link<T> *p=new Link<T>;
    cout<<"输入待建表节点数:";
    cin>>n;
    int cnt=0;
    p=head;
    cout<<"输入节点值:";
    while (cin>>val)
    {
        Link<T> *q=new Link<T>;
        q->data=val;
        p->next=q;
        p=p->next;
        cnt++;
        if (cnt==n)
            break;
    }
    tail=p;
    tail->next=NULL;

}
template <class T>
lnkList<T>:: ~lnkList()
{
    // 释放所有结点，含头结点，
    Link<T> * tmp = head->next;
    while (tmp != NULL)
    {
        tail = tmp->next;
        delete tmp;
        tmp = tail;
    }
    delete head;
}

template <class T>
void lnkList<T> :: clear()
{
    // 除头结点，释放其它结点
    Link<T> * tmp = head->next;
    while (tmp != NULL)
    {
        delete tmp;
        tmp = head->next;
    }
    tail = head;  //只剩一个头结点
};

template <class T>
bool lnkList<T> :: isEmpty()				 	// 线性表为空时，返回True
{
    return (head == tail);
}

template  <class T>
bool lnkList<T> :: app(const T & value)	    // 在表尾添加一个元素value，表的长度增1
{
    Link<T> *p=new Link<T>(value,NULL);
    tail->next=p;
    tail=p;
    return true;
}

template  <class T>   // 指定pos无对应位置，则插入到头或尾
bool lnkList<T> :: ins(int pos, const T & value)
{
    Link<T> *p, *q;

    // 定位pos位置的前驱结点，由p指向
    p = head;
    int cnt = 0;
    while (p != NULL && cnt < pos)  //头结点 + pos-1个数据结点
    {
        cnt++;
        p = p->next;
    }

    if (p)
    {
        q = new Link<T>(value, p->next); // 构造插入结点
        p->next = q;
    }
    else   // 插入结点成为新的链尾
    {
        q = new Link<T>(value, NULL);
        tail->next = q;
        tail = q;
    }
    return true;
}

// delete a node from singly linked list
template  <class T>  			// 假定线性表的元素类型为T
bool lnkList<T> :: del(int i)
{
    Link<T>*p,*q;
    int cnt=0;
    p=head;
    while (p!=NULL&&cnt<i)
    {
        cnt++;
        p=p->next;
    }
    if (p!=NULL&&p!=tail)
    {
        q=p->next;
        if (q==tail)
        {
            tail=p;
            p->next=NULL;
            delete q;
        }
        else if(q!=NULL)
        {
            p->next=q->next;
            delete q;
        }
        return true;
    }
    else
    {
        cout<<"该节点不在表中"<<endl;
        return false;
    }
}
template  <class T>
bool lnkList<T> :: getValue(int pos, T & value)		// 返回位置pos的元素值
{
    Link<T> *p;
    p=head;
    int cnt=0;
    while (p!=NULL&&cnt<=pos)
    {
        cnt++;
        p=p->next;
    }
    if (p)
    {
        value=p->data;
        return true;
    }
    else
    {
        return false;
    }
}

template  <class T>
bool lnkList<T> :: setValue(int pos, const T & value)	// 用value修改位置pos的元素值
{
    Link<T> *p,*q;
    p=head;
    int cnt=0;
    while (p!=NULL&&cnt<=pos)
    {
        cnt++;
        p=p->next;
    }
    if (p)
    {
        p->data=value;
        return true;
    }
    else
    {
        /*q=new Link<T>(value,NULL);
        tail->next=q;
        tail=q;*/
        return false;
    }
}

template  <class T>
bool lnkList<T> :: getPos(int & pos, const T & value)   // 将表中值为value的元素的位置返回到pos中
{
    Link<T> *p=new Link<T>;
    p=head->next;
    int cnt=0;
    while (p!=NULL&&p->data!=value)
    {
        p=p->next;
        cnt++;
    }
    if (p)
    {
        pos=cnt;
        return true;
    }
    else
    {
        return false;
    }

}

template <class T>  			    // 假定单链表的元素类型为T
int lnkList<T> :: length()
{
    int cnt=0;
    Link<T> *p;
    p=head;
    while (p!=NULL)
    {
        p=p->next;
        cnt++;
    }
    return cnt-1;

}

template <class T>  			    // 假定单链表的元素类型为T
void lnkList<T> :: print()
{
    Link<T> * cur = head->next;
    while (cur != NULL)
    {
        cout << cur->data << "  ";
        cur = cur->next;
    }
}
template <class T>
void lnkList<T>::mysort()
{
    Link<T> *q=new Link<T>;
    T temp;
    while(true)
    {
        int flag=1;
        q=head->next;
        while (q->next!=NULL)
        {
            if (q->data>q->next->data)
            {
                temp=q->next->data;
                q->next->data=q->data;
                q->data=temp;
                flag=0;
            }
            q=q->next;
        }
        if (flag) break;
    }
}
//上机1题 链表逆置
template <class T>
void lnkList<T>::myreverse()
{
    Link<T> *p,*q,*pp;
    p=head->next;
    q=new Link<T>;
    pp=new Link<T>;
    q=NULL;
    while (p)
    {
        //q为前pp为后
        pp=p->next;
        p->next=q;
        q=p;
        p=pp;
    }
    head->next=q;
}

//上机2题 获取倒数第m个元素
template <class T>
bool lnkList<T>::getValue1(int m,T & value)
{
    Link<T> *p=new Link<T>;
    if (m>(*this).length()||m<0)
    {
        return false;
    }
    int n;
    if (m==0)
        n=this->length()-m;
    else
        n=this->length()-m+1;
    int cnt=0;
    p=head;
    while (cnt<n)
    {
        p=p->next;
        cnt++;
    }
    value=p->data;
    return true;
}

//上机3题 删除min—max的元素
template <class T>
void lnkList<T>::del1(T &a,T &b)
{
    Link<T> *p=new Link<T>;
    Link<T> *q=new Link<T>;
    q=head->next;
    while (q!=NULL)
    {
        if (q->data>=b)
            break;
        q=q->next;
    }
    Link<T> *pq=new Link<T>;
    p=head->next;
    pq=p;
    int flag=1;
    while (p!=NULL&&p->data<=a)
    {
        pq=p;
        p=p->next;
        flag=0;
    }
    Link<T> *pp=new Link<T>;
    if (p)
    {
        while (p!=q)
        {
            pp=p->next;
            delete p;
            p=pp;
        }
        if (flag)
            head->next=q;
        else
            pq->next=q;
    }
}


#endif // LINKLIST_H_INCLUDE
