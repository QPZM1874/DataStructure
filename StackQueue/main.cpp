#include <cstdlib>
#include <iostream>
#include "lnkStack.h"
#include "arrStack.h"
#include "calc.h"
#include "lnkQueue.h"
#include "arrQueue.h"

using namespace std;

// 测试链接栈
void testLinkStack();

// 利用栈实现的非递归阶乘函数
long factorialNonrecursive(long n);

// 测试后缀表达是计算
void testPostfixExpr();

// 测试链接队列
void testQueue();
//队列排序
void sortQueue1();  //使用一个辅助队列
void sortQueue2();  //使用两个辅助队列

//栈排序
void transStack1();  //使用一个辅助栈
void transStack2();  //只使用一些辅助的非数组变量

int main(int argc, char *argv[])
{

    testLinkStack();

    //cout << factorialNonrecursive(x) << endl;

   // testPostfixExpr();

    testQueue();

}
//使用一个辅助栈
void transStack1(lnkStack<int> &s1,lnkStack<int> &s2)
{
    //先存到栈s里，再从s里转到s2里
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
//只使用一些辅助的非数组变量
void transStack2(lnkStack<int>& s1,lnkStack<int>& s2)
{
    int a,len=0;
    //获取s1的长度，并转移到s2里面（逆序）
    while (!s1.isEmpty())
    {
        s1.pop(a);
        s2.push(a);
        len++;
    }
    for (int i=0;i<len;i++)
    {//外循环每循环一次，s2的栈底加入一个元素
        s2.pop(a);
        int b;
        //除s2里依次加入栈底的元素外，其它先转移到s1里，再转到s2里
        for (int j=0;j<len-i-1;j++)
        {
            s2.pop(b);
            s1.push(b);
        }
        s2.push(a);//加入元素
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
    cout<<"输入元素个数:";
    cin>>n;
    cout<<"输入栈的元素：";
    for (int i=0; i<n; i++)
    {
        cin>>m;
        s.push(m);
    }
    cout<<"s: ";
    s.print();

    cout<<"转移到栈s2里面\n"<<"s2:";
    lnkStack<int> s2(0);
    transStack1(s,s2);
    s2.print();


    cout<<"转移到s3里面\n"<<"s3:";
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

    while (n > 1)      // 不满足递归出口
    {
        s.push(n);     // 按递归规则把相应数据压栈
        n--;
    }

    while(!s.isEmpty())     // 递归出口满足，开始进行返回处理
    {
        s.pop(tmp);
        m *= tmp;
    }
    return m ;
}



// 测试后缀表达是计算
void testPostfixExpr()
{
    Calculator a;

    cout << "23+(34.0*45.0)/(5+6+7)=" << 23+(34.0*45)/(5+6+7) << endl;

    a.clear();
    a.Run("23 34 45 * 5 6 + 7 + / +");
}

//使用一个辅助队列
void sortQueue1(arrQueue<int> &que)
{
    arrQueue<int> que1(50);
    int fr,minn,len=0,i=0;
    //获取队列长度，并把que的元素转到que1里面
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

        if (i%(len-1)==0) //if条件为真代表minn跟队列中剩余元素比较了一遍
        {                           //minn存的是最小值
            que.enQueue(minn);//minn进入que中
            len--;  //下一轮需与minn比较的元素个数减少一
            que1.deQueue(minn);//弹出一个元素做为最小值，等下一轮与其它值比较
            i=0;
        }
    }
    que.enQueue(minn);
}

//使用两个辅助队列
void sortQueue2(arrQueue<int>&que)
{
    //先把排序后的队列放在que1中，再转到que中
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
        que1.enQueue(minn);//每次循环que1里加入一个最小的元素
    }
    while (!que1.isEmpty())
    {
        que1.deQueue(fr);
        que.enQueue(fr);
    }
}


// 测试队列
void testQueue()
{
    arrQueue<int> que(50);
    //lnkQueue<int> que;
    int m,n;
    cout<<"输入元素个数:";
    cin>>n;
    cout<<"输入队列的元素：";
    for (int i=0; i<n; i++)
    {
        cin>>m;
        que.enQueue(m);
    }
    sortQueue1(que);
    cout<<"排序后的队列: ";
    que.print();

    que.clear();
    cout<<"输入元素个数:";
    cin>>n;
    cout<<"输入队列的元素：";
    for (int i=0; i<n; i++)
    {
        cin>>m;
        que.enQueue(m);
    }
    sortQueue2(que);
    cout<<"排序后的队列: ";
    que.print();



  /*  int tmp;
    que.deQueue(tmp);
    cout << tmp << ",";
    cout << endl;
    que.print();
    cout<<endl;*/

}
