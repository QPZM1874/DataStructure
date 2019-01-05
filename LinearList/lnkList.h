#ifndef LINKLIST_H_INCLUDE
#define LINKLIST_H_INCLUDE
#include <cstdlib>
#include <iostream>

#include "myList.h"

using namespace std;

// ��Ԫ�ص�����ΪT�����嵥����Ľ������Link
// ԭ��������ӦΪprivate���˴�����Ϊpublic��͵�����ѣ�
// �����ڱ�������ģ���֧�֣���ģ�����ʵ�ַ���ͷ�ļ���
//
template <class T> class Link
{
public:
    T  		data;						// ���ڱ�����Ԫ�ص�����
    Link<T>	* next;						// ָ���̽���ָ��
public:
    Link(const T & info, Link * nextValue = NULL)   	// ��������������Link���캯��
    {
        data = info;
        next = nextValue;
    }
    Link(Link* nextValue = NULL)    	// ����һ��������Link���캯��
    {
        next = nextValue;
    }
};

// ����������Ͷ��塣��ͷ��㣬�б�βָ��
template <class T>
class lnkList : public List<T>
{
protected:
    Link<T>*  head, * tail;    				// �������ͷ��βָ��
public:
    lnkList();						// ���캯��
    ~lnkList();						// ��������

    // �̳��Ի���ķ���
    virtual void clear(); 				 	// �ÿ����Ա�
    virtual bool isEmpty();				 	// ���Ա�Ϊ��ʱ������True
    virtual bool app(const T & value);	    // �ڱ�β���һ��Ԫ��value����ĳ�����1
    virtual bool ins(int pos, const T & value);	 	// ��λ��pos�ϲ���һ��Ԫ��value��ָ��pos�޶�Ӧλ�ã�����뵽ͷ��β
    virtual bool del(int pos); 			 	        // ɾ��λ��pos�ϵ�Ԫ�أ���ĳ��ȼ� 1
    virtual bool getValue(int pos, T & value);		    // ����λ��pos��Ԫ��ֵ
    virtual bool setValue(int pos, const T & value);	// ��value�޸�λ��pos��Ԫ��ֵ
    virtual bool getPos(int & pos, const T & value);    // ������ֵΪvalue��Ԫ�ص�λ�÷��ص�pos��

    // ��������
    int length();                   // ���ش�˳���ĵ�ǰʵ�ʳ���
    void print();
    void creat();//����
    void mysort();
    void myreverse();  //�ϻ�1�� ��������
    bool getValue1(int m,T & value); //�ϻ�2�� ��ȡ������m��Ԫ��
    void del1(T &,T &);  //�ϻ�3�� ɾ��min��max��Ԫ��
    lnkList<T> Hebing(lnkList<T> &);
};


template <class T>
lnkList<T> :: lnkList()
{
    head = tail = new Link<T>;//����ͷ���

}
template <class T>
void lnkList<T>::creat()
{
    int n;
    T val;
    Link<T> *p=new Link<T>;
    cout<<"���������ڵ���:";
    cin>>n;
    int cnt=0;
    p=head;
    cout<<"����ڵ�ֵ:";
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
    // �ͷ����н�㣬��ͷ��㣬
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
    // ��ͷ��㣬�ͷ��������
    Link<T> * tmp = head->next;
    while (tmp != NULL)
    {
        delete tmp;
        tmp = head->next;
    }
    tail = head;  //ֻʣһ��ͷ���
};

template <class T>
bool lnkList<T> :: isEmpty()				 	// ���Ա�Ϊ��ʱ������True
{
    return (head == tail);
}

template  <class T>
bool lnkList<T> :: app(const T & value)	    // �ڱ�β���һ��Ԫ��value����ĳ�����1
{
    Link<T> *p=new Link<T>(value,NULL);
    tail->next=p;
    tail=p;
    return true;
}

template  <class T>   // ָ��pos�޶�Ӧλ�ã�����뵽ͷ��β
bool lnkList<T> :: ins(int pos, const T & value)
{
    Link<T> *p, *q;

    // ��λposλ�õ�ǰ����㣬��pָ��
    p = head;
    int cnt = 0;
    while (p != NULL && cnt < pos)  //ͷ��� + pos-1�����ݽ��
    {
        cnt++;
        p = p->next;
    }

    if (p)
    {
        q = new Link<T>(value, p->next); // ���������
        p->next = q;
    }
    else   // �������Ϊ�µ���β
    {
        q = new Link<T>(value, NULL);
        tail->next = q;
        tail = q;
    }
    return true;
}

// delete a node from singly linked list
template  <class T>  			// �ٶ����Ա��Ԫ������ΪT
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
        cout<<"�ýڵ㲻�ڱ���"<<endl;
        return false;
    }
}
template  <class T>
bool lnkList<T> :: getValue(int pos, T & value)		// ����λ��pos��Ԫ��ֵ
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
bool lnkList<T> :: setValue(int pos, const T & value)	// ��value�޸�λ��pos��Ԫ��ֵ
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
bool lnkList<T> :: getPos(int & pos, const T & value)   // ������ֵΪvalue��Ԫ�ص�λ�÷��ص�pos��
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

template <class T>  			    // �ٶ��������Ԫ������ΪT
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

template <class T>  			    // �ٶ��������Ԫ������ΪT
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
//�ϻ�1�� ��������
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
        //qΪǰppΪ��
        pp=p->next;
        p->next=q;
        q=p;
        p=pp;
    }
    head->next=q;
}

//�ϻ�2�� ��ȡ������m��Ԫ��
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

//�ϻ�3�� ɾ��min��max��Ԫ��
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
