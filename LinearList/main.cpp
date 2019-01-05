#include <cstdlib>
#include <iostream>

#include "arrList.h"
#include "lnkList.h"

using namespace std;

void testArrList(); // 顺序表的测试
void testLnkList(); // 单链表的测试


int main(int argc, char *argv[])
{
    //testArrList();

    testLnkList();

    return 0;
}

void testArrList() // 顺序表的测试
{
    arrList<int> a(10);

    int val, p, n;

    cout << "输入待建表的结点数（<=10）:";
    cin >> n;

    cout << "输入" << n << "对插入结点的位置和结点整数值:";

    for (int i=0; i < n; i++)
    {
        cin >> p;
        cin >> val;
        a.ins(p,val);
    }
    cout << "表中的结点:";
    a.print();

    cout << "输入查找结点值:";
    cin >> val;
    if (a.getPos(p,val))
        cout << "位于:" << p << endl;
    else
        cout << "不在表中！" << endl;
    cout << "输入删除结点位置:";
    cin >> p;
    a.del(p);

    cout << "表中的结点:";
    a.print();
}

void testLnkList() // 单链表的测试
{
    lnkList<int> a;
    lnkList<int> b;
    int val, p, n;
    int min,max;


    a.creat();
    cout << "表中的结点:";
    a.print();
    cout<<endl<<"排序后的表:";
    a.mysort();
    a.print();

    b.creat();
    cout << "表中的结点:";
    b.print();
    cout<<endl<<"排序后的表:";
    b.mysort();
    b.print();



    cout<<endl<<"输入两个数:";
    cin>>min>>max;
    cout<<endl<<"删除后的表中的节点:";
    a.del1(min,max);
    a.print();

 /*   cout<<"输入要插入的节点的位置和值";
    cin>>p>>val;
    a.ins(p,val);
    cout<<"表中的结点：";
    a.print();



    cout << "输入查找结点值:";
    cin >> val;
    if (a.getPos(p,val))
        cout << "位于:" << p << endl;
    else
        cout << "不在表中！" << endl;
    cout<<"输入查找节点位置：";
    cin>>p;
    if (a.getValue(p,val))
        cout<<"值为："<<val<<endl;
    else
        cout<<"位置输入不正确"<<endl;

    cout<<"输入要设置的节点位置和值";
    cin>>p>>val;
    if (a.setValue(p,val))
        a.print();
    else
        cout<<"位置不在表中"<<endl;



    cout << "输入删除结点位置:";
    cin >> p;
    a.del(p);

    cout << "表中的结点:";
    a.print();

    cout<<"输入要插在表尾的元素：";
    cin>>val;
    a.app(val);
    cout<<"表中结点：";
    a.print();

    int m=a.length();
    cout<<endl<<"表的长度："<<m<<endl;*/

    cout<<"输入倒数的位置：";
    cin>>p;
    if (a.getValue1(p,val))
        cout<<"倒数第"<<p<<"个元素值为:"<<val<<endl;
    else
        cout<<"输入位置不在表中"<<endl;


    cout<<"输出逆转链表："<<endl;
    a.myreverse();
    a.print();


}
