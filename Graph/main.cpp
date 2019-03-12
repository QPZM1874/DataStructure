#include <iostream>
#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"
#include "ApplicationOfGraph.h"
#include"Taohui.h"

using namespace std;
void testTranspose1();//测试图的转置(邻接矩阵）
void testTranspose2();//测试图的转置(邻接表)
void testConnected1();//测试图的连通分量(无向图）
void testConnected2();//测试图的连通分量(有向图）
void testisHaveL();//测试图中是否含有漏

int main()
{
/*
    cout<<"测试图的转置(邻接矩阵)"<<endl;
    testTranspose1();
    cout<<"---------------------------"<<endl;
    cout<<"测试图的转置(邻接表)"<<endl;
    testTranspose2();
    cout<<"---------------------------"<<endl;
    cout<<"测试图的连通分量"<<endl;
    testConnected1();
    cout<<"---------------------------"<<endl;
    testConnected2();
    cout<<"---------------------------"<<endl;
    cout<<"测试图中是否含有漏"<<endl;
    testisHaveL();
    */
    cout<<"测试套汇"<<endl;
    testTaohui();
/*
    cout << "测试 \"邻接矩阵\" 表示的图" << endl;
    testGraphm();
    cout << endl;

    cout << "测试 \"邻接表\" 表示的图" << endl;
    testGraphl();
    cout << endl;

    cout << "测试 \"拓扑排序\"" << endl;
    testTopologicalSort();
    cout << endl << endl;

    cout <<"测试 \"Dijkstra算法\"" << endl;
    testDijkstra();
    cout << endl;

    cout <<"测试 \"Floyd算法\"" << endl;
    testFloyd();
    cout << endl;


    cout <<"测试 \"Prim算法\"" << endl;
    testPrim();
    cout << endl;

    cout <<"测试 \"Kruskal算法\"" << endl;
    testKruskal();
    cout << endl;
*/

    return 0;
}
void testTranspose1()//测试图的转置(邻接矩阵）
{
    const int N = 4;
    cout<<"邻接矩阵表示"<<endl;
    int A[N][N]=
    {
        {0,5,3,INFINITE},
        {INFINITE,0,INFINITE,INFINITE},
        {INFINITE,INFINITE,0,2},
        {1,INFINITE,INFINITE,0}
    };
    Graphm aGraph(N);              // 建立图
    aGraph.IniGraphm(&aGraph, (int *)A); // 初始化图
    cout << "DFS: ";
    aGraph.DFS(aGraph, 0);
    cout << endl;
    for (int i = 0; i < aGraph.VerticesNum(); i ++) //把Mark改回UNVISITED
        aGraph.Mark[i] = UNVISITED;

    aGraph.TransposeMatrix();
    cout<<"转置后的图的周游:"<<endl;
    for (int i = 0; i < aGraph.VerticesNum(); i ++) //把Mark改回UNVISITED
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
void testTranspose2()//测试图的转置(邻接表）
{
    const int N = 4;
    int A[N][N]=
    {
        {0,5,3,INFINITE},
        {INFINITE,0,INFINITE,INFINITE},
        {INFINITE,INFINITE,0,2},
        {1,INFINITE,INFINITE,0}
    };
    cout<<"邻接表表示"<<endl;
    Graphl aGraph(N);              // 建立图
    aGraph.IniGraphl(&aGraph, (int *)A); // 初始化图
    for (int i = 0; i < aGraph.VerticesNum(); i ++) //把Mark改回UNVISITED
        aGraph.Mark[i] = UNVISITED;
    cout << "DFS: ";
    aGraph.DFS(aGraph, 0);
    cout << endl;
    aGraph.TransposeList();
    cout<<"转置后的图的周游:"<<endl;
    for (int i = 0; i < aGraph.VerticesNum(); i ++) //把Mark改回UNVISITED
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
void testConnected1()//测试图的连通分量(无向图）
{
    cout<<"无向图的连通分量"<<endl;
    const int N=9;//图7.5（a）
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
    Graphm aGraph(N);              // 建立图
    aGraph.IniGraphm(&aGraph, (int *)A); // 初始化图
    aGraph.ConnecComponent1(aGraph);
}
void testConnected2()//测试图的连通分量(有向图）
{
    cout<<"有向图的连通分量"<<endl;
    const int N = 4;//图7.2(b)
    int A[N][N]=
    {
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,2},
        {1,0,0,0}
    };
    Graphm aGraph(N);              // 建立图
    aGraph.IniGraphm(&aGraph, (int *)A); // 初始化图
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
       };   //此图没有漏
    */
    int A[N][N]=
    {
        {0,1,1,0},
        {0,0,0,0},
        {0,1,0,2},
        {1,1,0,0}
    };   //此图有漏(第二个顶点)

    Graphm aGraph(N);              // 建立图
    aGraph.IniGraphm(&aGraph, (int *)A); // 初始化图
    if (aGraph.isHaveL())
        cout<<"此图含有漏"<<endl;
    else
        cout<<"此图不含漏"<<endl;
}
