#include <iostream>
#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"
#include "ApplicationOfGraph.h"
#include"Taohui.h"

using namespace std;
void testTranspose1();//����ͼ��ת��(�ڽӾ���
void testTranspose2();//����ͼ��ת��(�ڽӱ�)
void testConnected1();//����ͼ����ͨ����(����ͼ��
void testConnected2();//����ͼ����ͨ����(����ͼ��
void testisHaveL();//����ͼ���Ƿ���©

int main()
{
/*
    cout<<"����ͼ��ת��(�ڽӾ���)"<<endl;
    testTranspose1();
    cout<<"---------------------------"<<endl;
    cout<<"����ͼ��ת��(�ڽӱ�)"<<endl;
    testTranspose2();
    cout<<"---------------------------"<<endl;
    cout<<"����ͼ����ͨ����"<<endl;
    testConnected1();
    cout<<"---------------------------"<<endl;
    testConnected2();
    cout<<"---------------------------"<<endl;
    cout<<"����ͼ���Ƿ���©"<<endl;
    testisHaveL();
    */
    cout<<"�����׻�"<<endl;
    testTaohui();
/*
    cout << "���� \"�ڽӾ���\" ��ʾ��ͼ" << endl;
    testGraphm();
    cout << endl;

    cout << "���� \"�ڽӱ�\" ��ʾ��ͼ" << endl;
    testGraphl();
    cout << endl;

    cout << "���� \"��������\"" << endl;
    testTopologicalSort();
    cout << endl << endl;

    cout <<"���� \"Dijkstra�㷨\"" << endl;
    testDijkstra();
    cout << endl;

    cout <<"���� \"Floyd�㷨\"" << endl;
    testFloyd();
    cout << endl;


    cout <<"���� \"Prim�㷨\"" << endl;
    testPrim();
    cout << endl;

    cout <<"���� \"Kruskal�㷨\"" << endl;
    testKruskal();
    cout << endl;
*/

    return 0;
}
void testTranspose1()//����ͼ��ת��(�ڽӾ���
{
    const int N = 4;
    cout<<"�ڽӾ����ʾ"<<endl;
    int A[N][N]=
    {
        {0,5,3,INFINITE},
        {INFINITE,0,INFINITE,INFINITE},
        {INFINITE,INFINITE,0,2},
        {1,INFINITE,INFINITE,0}
    };
    Graphm aGraph(N);              // ����ͼ
    aGraph.IniGraphm(&aGraph, (int *)A); // ��ʼ��ͼ
    cout << "DFS: ";
    aGraph.DFS(aGraph, 0);
    cout << endl;
    for (int i = 0; i < aGraph.VerticesNum(); i ++) //��Mark�Ļ�UNVISITED
        aGraph.Mark[i] = UNVISITED;

    aGraph.TransposeMatrix();
    cout<<"ת�ú��ͼ������:"<<endl;
    for (int i = 0; i < aGraph.VerticesNum(); i ++) //��Mark�Ļ�UNVISITED
        aGraph.Mark[i] = UNVISITED;
    cout << "DFS: ";
    aGraph.DFS(aGraph, 0);
    while (true)
    {
        int i,flag=1;
        for (i=0; i<aGraph.VerticesNum(); i++)
        {
            if (aGraph.Mark[i]==UNVISITED)
            {
                flag=0;
                break;
            }
        }
        if (flag==0)
            aGraph.DFS(aGraph,i);
        else    break;
    }
    cout << endl;


}
void testTranspose2()//����ͼ��ת��(�ڽӱ�
{
    const int N = 4;
    int A[N][N]=
    {
        {0,5,3,INFINITE},
        {INFINITE,0,INFINITE,INFINITE},
        {INFINITE,INFINITE,0,2},
        {1,INFINITE,INFINITE,0}
    };
    cout<<"�ڽӱ��ʾ"<<endl;
    Graphl aGraph(N);              // ����ͼ
    aGraph.IniGraphl(&aGraph, (int *)A); // ��ʼ��ͼ
    for (int i = 0; i < aGraph.VerticesNum(); i ++) //��Mark�Ļ�UNVISITED
        aGraph.Mark[i] = UNVISITED;
    cout << "DFS: ";
    aGraph.DFS(aGraph, 0);
    cout << endl;
    aGraph.TransposeList();
    cout<<"ת�ú��ͼ������:"<<endl;
    for (int i = 0; i < aGraph.VerticesNum(); i ++) //��Mark�Ļ�UNVISITED
        aGraph.Mark[i] = UNVISITED;
    cout << "DFS: ";
    aGraph.DFS(aGraph, 0);
    while (true)
    {
        int i,flag=1;
        for (i=0; i<aGraph.VerticesNum(); i++)
        {
            if (aGraph.Mark[i]==UNVISITED)
            {
                flag=0;
                break;
            }
        }
        if (flag==0)
            aGraph.DFS(aGraph,i);
        else    break;
    }
    cout << endl;
}
void testConnected1()//����ͼ����ͨ����(����ͼ��
{
    cout<<"����ͼ����ͨ����"<<endl;
    const int N=9;//ͼ7.5��a��
    int A[N][N]=
    {
        {0,1,1,0,0,0,0,0,0},
        {1,0,0,1,0,0,0,0,0},
        {1,0,0,1,1,0,0,0,0},
        {0,1,1,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1},
        {0,0,0,0,0,1,0,1,0},
        {0,0,0,0,0,1,1,0,0},
        {0,0,0,0,0,1,0,0,0}
    };
    Graphm aGraph(N);              // ����ͼ
    aGraph.IniGraphm(&aGraph, (int *)A); // ��ʼ��ͼ
    aGraph.ConnecComponent1(aGraph);
}
void testConnected2()//����ͼ����ͨ����(����ͼ��
{
    cout<<"����ͼ����ͨ����"<<endl;
    const int N = 4;//ͼ7.2(b)
    int A[N][N]=
    {
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,2},
        {1,0,0,0}
    };
    Graphm aGraph(N);              // ����ͼ
    aGraph.IniGraphm(&aGraph, (int *)A); // ��ʼ��ͼ
    aGraph.ConnecComponent2();

}
void testisHaveL()
{
    const int N = 4;
    /*   int A[N][N]=
       {
           {0,1,1,0},
           {0,0,0,0},
           {0,0,0,2},
           {1,0,0,0}
       };   //��ͼû��©
    */
    int A[N][N]=
    {
        {0,1,1,0},
        {0,0,0,0},
        {0,1,0,2},
        {1,1,0,0}
    };   //��ͼ��©(�ڶ�������)

    Graphm aGraph(N);              // ����ͼ
    aGraph.IniGraphm(&aGraph, (int *)A); // ��ʼ��ͼ
    if (aGraph.isHaveL())
        cout<<"��ͼ����©"<<endl;
    else
        cout<<"��ͼ����©"<<endl;
}
