// AdjacencyList.cpp
// 邻表表示图的类Graphm的实现

#include "AdjacencyList.h"
#include <iostream>
#include <queue>
using namespace std;


Edge Graphl::FirstEdge(int oneVertex)      //返回顶点oneVertex的第一条边
{
    Edge myEdge;                   //边myEdge将作为函数的返回值
    myEdge.from = oneVertex;       //将顶点oneVertex作为边myEdge的始点
    /*graList[oneVertex].head保存的是顶点oneVertex的边表，
    temp->next指向顶点oneVertex的第一条边(如果temp->next
    不为null)*/
    Link<listUnit> *temp = graList[oneVertex].head;
    if(temp->next != NULL)           //如果顶点oneVertex的第一条边确实存在
    {
        myEdge.to = temp->next->element.vertex;
        myEdge.weight = temp->next->element.weight;
    }
    /*如果找到了顶点oneVertex的第一条边,则返回的myEdge确实是一条边;如果没有
    找到顶点oneVertex的第一条边,则myEdge的成员变量to为-1,根据IsEdge函数判
    断可知myEdge不是一条边*/
    return myEdge;
}

Edge Graphl::NextEdge(Edge preEdge)     // 返回与边PreEdge有相同关联顶点的下一条边
{
    Edge myEdge;			 		// myEdge的初始成员变量to为-1
    myEdge.from = preEdge.from;  		// 将边的始点置为与上一条边的相同
    Link<listUnit> *temp = graList[preEdge.from].head;		// temp指向边表头一个
    while (temp->next != NULL && temp->next->element.vertex <= preEdge.to)
        temp = temp->next; 			// 确定边preEdge的位置
    if (temp->next != NULL)  		// 边preEdge的下一条边存在
    {
        myEdge.to = temp->next->element.vertex;
        myEdge.weight = temp->next->element.weight;
    }
    return myEdge;					// 如果没有找到第一条边，myEdge.to=-1
}

void Graphl::setEdge(int from,int to,int weight)     //为图设定一条边
{
    if (from==to||weight>=INFINITE)
        return;
    Link<listUnit> *temp = graList[from].head;  /*graList[from].head保存的是顶点from的
													边表，temp->next指向顶点from的第一条边
													(如果temp->next不为null)*/
    while(temp->next != NULL && temp->next->element.vertex < to)
        temp = temp->next;   /*确定边(from,to)或<from,to>在边表中的位置,如果不存在,
									则边(from,to)或<from,to>为新加的一条边*/
    if(temp->next == NULL)
    {
        /*边(from,to)或<from,to>在边表中不存在且在边表中其后
        							已无其它边,则在边表中加入这条边*/
        temp->next = new Link<listUnit>;
        temp->next->element.vertex = to;
        temp->next->element.weight = weight;
        numEdge++;
        Indegree[to]++;
        return;
    }
    if(temp->next->element.vertex == to)
    {
        /*边(from,to)或<from,to>在边表中已存在,
        										故只需要改变边的权值*/
        temp->next->element.weight = weight;
        return;
    }
    if(temp->next->element.vertex>to)
    {
        /*边(from,to)或<from,to>在边表中不存在,但在边表中
        										其后存在其它边,则在边表中插入这条边*/
        Link<listUnit> *other = temp->next;
        temp->next = new Link<listUnit>;
        temp->next->element.vertex = to;
        temp->next->element.weight = weight;
        temp->next->next = other;
        numEdge++;
        Indegree[to]++;
        return;
    }
}

void Graphl::delEdge(int from,int to)             //删掉图的一条边
{
    Link<listUnit> *temp = graList[from].head;  /*graList[from].head保存的是顶点from的边表，temp->next指向顶点from的第一条边(如果temp->next不为null)*/
    while(temp->next != NULL && temp->next->element.vertex<to)
        temp = temp->next;	/*确定边(from,to)或<from,to>在边表中的位置(如果该边存在)*/
    if(temp->next == NULL)
        return;        //边(from,to)或<from,to>在边表中不存在,则不需要做任何操作
    if(temp->next->element.vertex>to)
        return;        //边(from,to)或<from,to>在边表中不存在,则不需要做任何操作
    if(temp->next->element.vertex == to)
    {
        /*边(from,to)或<from,to>在边表中存在且确
        									   定了该边在边表中的位置,则从边表中将其删掉*/
        Link<listUnit> *other = temp->next->next;
        delete temp->next;
        temp->next = other;
        numEdge--;
        Indegree[to]--;
        return;
    }
}

// 函数功能：//用按行存储的邻接矩阵初始化邻接表
void Graphl::IniGraphl(Graphl * Graphl, int * adj)
{
    int n = Graphl->numVertex;
    for (int i = 0; i < n; i ++)
    {
        for (int j = 0; j < n; j ++)
        {
            if (*(adj+i*n+j) > 0)
                Graphl->setEdge(i, j, *(adj+i*n+j));
        }
    }
}

//函数功能：深度优先搜索算法实现
void Graphl::DFS(Graph& G, int v)       //深度优先搜索算法实现
{
    G.Mark[v] = VISITED;       //访问顶点v，并标记其标志位
    Visit(G,v);
    //访问V邻接到的未被访问过的顶点，并递归地按照深度优先的方式进行周游
    for(Edge e=G.FirstEdge(v); G.IsEdge(e); e=G.NextEdge(e))
        if(G.Mark[G.ToVertex(e)]== UNVISITED)
            DFS(G, G.ToVertex(e));
}


// 函数功能：广度优先搜索
void Graphl::BFS(Graph& G, int v)              // 广度优先搜索算法的实现
{
    using std::queue;
    queue<int> Q;                    // 初始化广度优先周游要用到的队列
    Visit(G,v);                       // 问顶点v，并标记其标志位
    G.Mark[v] = VISITED;
    Q.push(v);                       // v入队
    while (!Q.empty())                 // 如果队列仍然有元素
    {
        int u = Q.front ();              // 队列顶部元素
        Q.pop();                     // 队列顶部元素出队
        // 该顶点邻接到的每一个未访问顶点都入队
        for (Edge e = G.FirstEdge(u); G.IsEdge(e); e = G.NextEdge(e))
            if (G.Mark[G.ToVertex(e)] == UNVISITED)
            {
                Visit(G, G.ToVertex(e));
                G.Mark[G.ToVertex(e)] = VISITED;
                Q.push(G.ToVertex(e));  // 入队
            }
    }
}

// 函数功能：显示顶点
void Graphl::Visit(Graph &G, int v)
{
    cout << 'V' << v <<" ";
}

void Graphl::TransposeList()
{
    int n=numVertex;
    for (int i=n-1;i>=0;i--)
    {
         Link<listUnit> *temp = graList[i].head;
         temp=temp->next;
         while (temp!=NULL)
         {
             int from=i;
             int to=temp->element.vertex;
             int weight=temp->element.weight;
             this->delEdge(from,to);
             this->setEdge(to,from,weight);
             temp=temp->next;
         }
    }
}
//----------------------------------------------------------------

// 测试Graphl的函数
void testGraphl()
{
    const int N = 4;  //图7.2中G1表示的无向图
  //  int A[N][N] =
    {
	//        V0 V1 V2 V3 V4
//	/*V0*/    {0, 0, 1, 1, 0},
//	/*V1*/    {0, 0, 0, 1, 1},
//	/*V2*/    {1, 0, 0, 1, 1},
//	/*V3*/    {1, 1, 1, 0, 0},
//	/*V4*/    {0, 1, 1, 0, 0}
	};
 /*   int A[N][N]=
	{
	    {0,1,1,0},
	    {0,0,0,0},
	    {0,0,0,1},
	    {1,0,0,0}
	};*/
	int A[N][N]=
	{
	    {0,5,3, INFINITE},
        {INFINITE,0, INFINITE, INFINITE},
        {INFINITE, INFINITE,0,2},
        {1, INFINITE, INFINITE,0}
	};
    Graphl aGraph(N);              // 建立图
	aGraph.IniGraphl(&aGraph, (int *)A); // 初始化图

	cout << "DFS: ";
	aGraph.DFS(aGraph, 0);
	cout << endl;

	for (int i = 0; i < aGraph.VerticesNum(); i ++) //把Mark改回UNVISITED
		aGraph.Mark[i] = UNVISITED;

	cout << "BFS: ";
	aGraph.BFS(aGraph, 0);
	cout << endl;

}

