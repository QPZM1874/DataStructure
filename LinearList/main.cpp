#include <cstdlib>
#include <iostream>

#include "arrList.h"
#include "lnkList.h"

using namespace std;

void testArrList(); // ˳���Ĳ���
void testLnkList(); // ������Ĳ���


int main(int argc, char *argv[])
{
    //testArrList();

    testLnkList();

    return 0;
}

void testArrList() // ˳���Ĳ���
{
    arrList<int> a(10);

    int val, p, n;

    cout << "���������Ľ������<=10��:";
    cin >> n;

    cout << "����" << n << "�Բ������λ�úͽ������ֵ:";

    for (int i=0; i < n; i++)
    {
        cin >> p;
        cin >> val;
        a.ins(p,val);
    }
    cout << "���еĽ��:";
    a.print();

    cout << "������ҽ��ֵ:";
    cin >> val;
    if (a.getPos(p,val))
        cout << "λ��:" << p << endl;
    else
        cout << "���ڱ��У�" << endl;
    cout << "����ɾ�����λ��:";
    cin >> p;
    a.del(p);

    cout << "���еĽ��:";
    a.print();
}

void testLnkList() // ������Ĳ���
{
    lnkList<int> a;
    lnkList<int> b;
    int val, p, n;
    int min,max;


    a.creat();
    cout << "���еĽ��:";
    a.print();
    cout<<endl<<"�����ı�:";
    a.mysort();
    a.print();

    b.creat();
    cout << "���еĽ��:";
    b.print();
    cout<<endl<<"�����ı�:";
    b.mysort();
    b.print();



    cout<<endl<<"����������:";
    cin>>min>>max;
    cout<<endl<<"ɾ����ı��еĽڵ�:";
    a.del1(min,max);
    a.print();

 /*   cout<<"����Ҫ����Ľڵ��λ�ú�ֵ";
    cin>>p>>val;
    a.ins(p,val);
    cout<<"���еĽ�㣺";
    a.print();



    cout << "������ҽ��ֵ:";
    cin >> val;
    if (a.getPos(p,val))
        cout << "λ��:" << p << endl;
    else
        cout << "���ڱ��У�" << endl;
    cout<<"������ҽڵ�λ�ã�";
    cin>>p;
    if (a.getValue(p,val))
        cout<<"ֵΪ��"<<val<<endl;
    else
        cout<<"λ�����벻��ȷ"<<endl;

    cout<<"����Ҫ���õĽڵ�λ�ú�ֵ";
    cin>>p>>val;
    if (a.setValue(p,val))
        a.print();
    else
        cout<<"λ�ò��ڱ���"<<endl;



    cout << "����ɾ�����λ��:";
    cin >> p;
    a.del(p);

    cout << "���еĽ��:";
    a.print();

    cout<<"����Ҫ���ڱ�β��Ԫ�أ�";
    cin>>val;
    a.app(val);
    cout<<"���н�㣺";
    a.print();

    int m=a.length();
    cout<<endl<<"��ĳ��ȣ�"<<m<<endl;*/

    cout<<"���뵹����λ�ã�";
    cin>>p;
    if (a.getValue1(p,val))
        cout<<"������"<<p<<"��Ԫ��ֵΪ:"<<val<<endl;
    else
        cout<<"����λ�ò��ڱ���"<<endl;


    cout<<"�����ת����"<<endl;
    a.myreverse();
    a.print();


}
