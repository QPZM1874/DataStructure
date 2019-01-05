#include <cstdlib>
#include <iostream>
#include "lnkStack.h"
#include "arrStack.h"
#include "calc.h"
#include "lnkQueue.h"
#include "arrQueue.h"

using namespace std;

// ��������ջ
void testLinkStack();

// ����ջʵ�ֵķǵݹ�׳˺���
long factorialNonrecursive(long n);

// ���Ժ�׺����Ǽ���
void testPostfixExpr();

// �������Ӷ���
void testQueue();
//��������
void sortQueue1();  //ʹ��һ����������
void sortQueue2();  //ʹ��������������

//ջ����
void transStack1();  //ʹ��һ������ջ
void transStack2();  //ֻʹ��һЩ�����ķ��������

int main(int argc, char *argv[])
{

    testLinkStack();

    //cout << factorialNonrecursive(x) << endl;

   // testPostfixExpr();

    testQueue();

}
//ʹ��һ������ջ
void transStack1(lnkStack<int> &s1,lnkStack<int> &s2)
{
    //�ȴ浽ջs��ٴ�s��ת��s2��
    lnkStack<int>s(0);
    int a;
    while (!s1.isEmpty())
    {
        s1.pop(a);
        s.push(a);
    }
    while (!s.isEmpty())
    {
        s.pop(a);
        s2.push(a);
    }
}
//ֻʹ��һЩ�����ķ��������
void transStack2(lnkStack<int>& s1,lnkStack<int>& s2)
{
    int a,len=0;
    //��ȡs1�ĳ��ȣ���ת�Ƶ�s2���棨����
    while (!s1.isEmpty())
    {
        s1.pop(a);
        s2.push(a);
        len++;
    }
    for (int i=0;i<len;i++)
    {//��ѭ��ÿѭ��һ�Σ�s2��ջ�׼���һ��Ԫ��
        s2.pop(a);
        int b;
        //��s2�����μ���ջ�׵�Ԫ���⣬������ת�Ƶ�s1���ת��s2��
        for (int j=0;j<len-i-1;j++)
        {
            s2.pop(b);
            s1.push(b);
        }
        s2.push(a);//����Ԫ��
        while (!s1.isEmpty())
        {
            s1.pop(b);
            s2.push(b);
        }
    }
}

void testLinkStack()
{
    lnkStack<int> s(0);
    int m,n;
    cout<<"����Ԫ�ظ���:";
    cin>>n;
    cout<<"����ջ��Ԫ�أ�";
    for (int i=0; i<n; i++)
    {
        cin>>m;
        s.push(m);
    }
    cout<<"s: ";
    s.print();

    cout<<"ת�Ƶ�ջs2����\n"<<"s2:";
    lnkStack<int> s2(0);
    transStack1(s,s2);
    s2.print();


    cout<<"ת�Ƶ�s3����\n"<<"s3:";
    lnkStack<int>s3(0);
    transStack2(s2,s3);
    s3.print();


}

// nonrevursive with stack
long factorialNonrecursive(long n)
{
    lnkStack<long> s(10);

    long tmp;
    long m = 1;

    while (n > 1)      // ������ݹ����
    {
        s.push(n);     // ���ݹ�������Ӧ����ѹջ
        n--;
    }

    while(!s.isEmpty())     // �ݹ�������㣬��ʼ���з��ش���
    {
        s.pop(tmp);
        m *= tmp;
    }
    return m ;
}



// ���Ժ�׺����Ǽ���
void testPostfixExpr()
{
    Calculator a;

    cout << "23+(34.0*45.0)/(5+6+7)=" << 23+(34.0*45)/(5+6+7) << endl;

    a.clear();
    a.Run("23 34 45 * 5 6 + 7 + / +");
}

//ʹ��һ����������
void sortQueue1(arrQueue<int> &que)
{
    arrQueue<int> que1(50);
    int fr,minn,len=0,i=0;
    //��ȡ���г��ȣ�����que��Ԫ��ת��que1����
    while (!que.isEmpty())
    {
        que.deQueue(fr);
        que1.enQueue(fr);
        len++;
    }
    que1.deQueue(minn);
    while (!que1.isEmpty())
    {
        que1.deQueue(fr);
        i++;
        if (fr<minn)
        {
            que1.enQueue(minn);
            minn=fr;
        }
        else
            que1.enQueue(fr);

        if (i%(len-1)==0) //if����Ϊ�����minn��������ʣ��Ԫ�رȽ���һ��
        {                           //minn�������Сֵ
            que.enQueue(minn);//minn����que��
            len--;  //��һ������minn�Ƚϵ�Ԫ�ظ�������һ
            que1.deQueue(minn);//����һ��Ԫ����Ϊ��Сֵ������һ��������ֵ�Ƚ�
            i=0;
        }
    }
    que.enQueue(minn);
}

//ʹ��������������
void sortQueue2(arrQueue<int>&que)
{
    //�Ȱ������Ķ��з���que1�У���ת��que��
    arrQueue<int> que1(50),que2(50);
    int fr;
    int minn;
    while (!que.isEmpty())
    {
        que.deQueue(minn);
        while (!que.isEmpty())
        {
            que.deQueue(fr);
            que2.enQueue(fr);
        }
        while (!que2.isEmpty())
        {
            que2.deQueue(fr);
            if (fr<minn)
                {
                que.enQueue(minn);
                minn=fr;
                }
            else
                que.enQueue(fr);
        }
        que1.enQueue(minn);//ÿ��ѭ��que1�����һ����С��Ԫ��
    }
    while (!que1.isEmpty())
    {
        que1.deQueue(fr);
        que.enQueue(fr);
    }
}


// ���Զ���
void testQueue()
{
    arrQueue<int> que(50);
    //lnkQueue<int> que;
    int m,n;
    cout<<"����Ԫ�ظ���:";
    cin>>n;
    cout<<"������е�Ԫ�أ�";
    for (int i=0; i<n; i++)
    {
        cin>>m;
        que.enQueue(m);
    }
    sortQueue1(que);
    cout<<"�����Ķ���: ";
    que.print();

    que.clear();
    cout<<"����Ԫ�ظ���:";
    cin>>n;
    cout<<"������е�Ԫ�أ�";
    for (int i=0; i<n; i++)
    {
        cin>>m;
        que.enQueue(m);
    }
    sortQueue2(que);
    cout<<"�����Ķ���: ";
    que.print();



  /*  int tmp;
    que.deQueue(tmp);
    cout << tmp << ",";
    cout << endl;
    que.print();
    cout<<endl;*/

}
