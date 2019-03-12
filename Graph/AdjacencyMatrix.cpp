// AdjacencyMatrix.cpp
// 邻接矩阵表示图的类Graphm的实现

#include "AdjacencyMatrix.h"
#include <iostream>
#include <queue>
using namespace std;

Graphm::Graphm(int numVert):Graph(numVert)   //构造函数
{
    int i, j;			//i, j作为for循环中的计数器
    matrix = (int **)new int*[numVertex]; /*申请matrix数组,该数组有numVertex个元素,每个元素是整型指针类型*/
    ValueMatrix=(double **)new double *[numVertex];
    for (i = 0; i < numVertex; i ++)		/*matrix数组的每个元素,都指向一个具有numVertex个元素的数组*/
        {
            matrix[i] = new int[numVertex];
            ValueMatrix[i]=new double [numVertex];
        }

    for (i = 0; i < numVertex; i++)       /*相邻矩阵的所有元素都初始化为0,如果矩阵元素matrix[i][j]不为0,则表明顶点i与顶点j之间有一条边,边的权即为matrix[i][j]的值*/
        for (j = 0; j < numVertex; j ++)
            {
                matrix[i][j] = 0;
                ValueMatrix[i][j]=0;
            }
}

Graphm::~Graphm()  							//析构函数
{
    for (int i = 0; i < numVertex; i ++)
        delete [] matrix[i];			//释放每个matrix[i]申请的空间
    delete [] matrix;				//释放matrix指针指向的空间
}

Edge Graphm::FirstEdge(int oneVertex)   	//返回顶点oneVertex的第一条边
{
    Edge myEdge;						//边myEdge将作为函数的返回值
    myEdge.from = oneVertex;			//将顶点oneVertex作为边myEdge的始点

    for (int i = 0; i < numVertex; i ++)
    {
        /*
          下面寻找第一个使得matrix[oneVertex][i]
          不为0的i值，那么边(oneVertex,i)或者
          弧<oneVertex,i>即为顶点oneVertex
          的第一条边，将顶点i作为边myEdge的终点边myEdge
          的权为矩阵元素matrix[oneVertex][i]的值
        */
        if (matrix[oneVertex][i] != 0&&matrix[oneVertex][i]<INFINITE)
        {
            myEdge.to = i;
            myEdge.weight = matrix[oneVertex][i];
            break;
        }
    }
    return myEdge;
    /*如果找到了顶点oneVertex的第一条边,则返回的myEdge确实是一条边；
      如果没有找到顶点oneVertex的第一条边,则myEdge的成员变量to为-1，
      根据IsEdge函数判断可知myEdge不是一条边
    */
}

Edge Graphm::NextEdge(Edge preEdge)    //返回与边PreEdge有相同关联顶点的下一条边
{
    Edge myEdge;
    myEdge.from=preEdge.from; /*将边myEdge的始点置为与上一条边preEdge的始点相同*/
    if(preEdge.to<numVertex)
    {
        //如果preEdge.to+1>=numVertex,那么就不存在下一条边了
        for(int i=preEdge.to+1; i<numVertex; i++)
        {
            /*寻找下一个使得//matrix[preEdge.from][i]不为0的i值,那么
            (preEdge.from,i)或者<preEdge.from,i>即为顶点preEdge.from的下一条边*/
            if(matrix[preEdge.from][i]!=0)
            {
                myEdge.to=i;
                myEdge.weight=matrix[preEdge.from][i];
                break;
            }
        }
    }
    return myEdge;
    /*如果找到了顶点preEdge.from的下一条边，则返回的myEdge确实是一条边；
    如果没有找到顶点preEdge.from的下一条边，则myEdge的成员变量to为-1，
    根据IsEdge函数判断可知myEdge不是一条边*/
}

void Graphm::setEdge(int from, int to, int weight)  //为图设定一条边
{
    if (matrix[from][to] <= 0)
    {
        /*如果matrix[from][to]<=0，则边(from,to) 或者<from,to>
        将是新增的一条边，否则该边已经存在（现在只是对该边进行修改）*/
        numEdge ++;
        Indegree[to] ++;
    }
    matrix[from][to] = weight;
}

void Graphm::delEdge(int from,int to)  //删除图的一条边
{
    if(matrix[from][to]>0)
    {
        /*如果matrix[from][to]>0，则边(from,to)或者<from,to>确实存在，
        否则该边实际上并不存在（从而不必对图的边数和顶点to的入度进行修改）*/
        numEdge--;
        Indegree[to]--;
    }
    matrix[from][to]=0;
}


// 函数功能：初始化图
void Graphm::IniGraphm(Graphm * Graphm, int * adj)
{
    int n = Graphm->numVertex;
    for (int i = 0; i < n; i ++)
    {
        for (int j = 0; j < n; j ++)
        {
            if (*(adj+i*n+j) > 0) //保证权重>=0，缺省为0。
                Graphm->setEdge(i, j, *(adj+i*n+j));
        }
    }
}

//函数功能：深度优先搜索算法实现
void Graphm::DFS(Graph& G, int v)       //深度优先搜索算法实现
{
    G.Mark[v] = VISITED;       //访问顶点v，并标记其标志位
    Visit(G,v);
    //访问V邻接到的未被访问过的顶点，并递归地按照深度优先的方式进行周游
    for(Edge e=G.FirstEdge(v); G.IsEdge(e) ; e=G.NextEdge(e))
    {
        if(G.Mark[G.ToVertex(e)]== UNVISITED)
        {
            DFS(G, G.ToVertex(e));
        }
    }
}


// 函数功能：广度优先搜索
void Graphm::BFS(Graph& G, int v)     // 广度优先搜索算法的实现
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
void Graphm::Visit(Graph &G, int v)
{
    cout << 'V' << v <<" ";
}
void Graphm::TransposeMatrix()
{
    int temp;
    for (int i=0; i<numVertex; i++)
    {
        for (int j=i+1; j<numVertex; j++)
        {
            temp=matrix[j][i];
            matrix[j][i]=matrix[i][j];
            matrix[i][j]=temp;
        }
    }
}
//无向图的连通分量
void Graphm::ConnecComponent1(Graphm & aGraph)
{
    int k=0;
    cout<<"第"<<++k<<"连通分量:";
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
        {
            cout<<"第"<<++k<<"连通分量:";
            aGraph.DFS(aGraph,i);
            cout<<endl;
        }
        else    break;
    }
}

//判断图上两点是否连通
bool Graphm::isconnected(int m,int n)
{
    queue<int>q;
    q.push(m);
    for (int i=0;i<numVertex;i++)
        Mark[i]=UNVISITED;
    while (!q.empty())
    {
        int tmp=q.front();
        q.pop();
        Mark[tmp]=VISITED;
        if (tmp==n) return true;//temp=n 表明m到n可达
        for (Edge e=FirstEdge(tmp);IsEdge(e);e=NextEdge(e))//把e的所有相邻的没被标记的顶点加入队列
        {
            if (Mark[ToVertex(e)]==UNVISITED)
                q.push(ToVertex(e));
        }
    }
    return false;
}
//有向图的连通分量
void Graphm::ConnecComponent2()
{
    int k=0;
    int mark[numVertex];
    for (int i=0;i<numVertex;i++)
        mark[i]=UNVISITED;
    for (int i=0;i<numVertex-1;i++)
    {
        if (mark[i]==VISITED)   continue;
        cout<<"第"<<++k<<"连通分量:";
        cout<<"V"<<i<<" ";
        for (int j=i+1;j<numVertex;j++)
        {

            if (mark[j]==VISITED)  continue;
            if (isconnected(i,j)&&isconnected(j,i))
            {
                cout<<"V"<<j<<" ";
                mark[j]=VISITED;
            }
        }
    }
    cout<<endl;
}
bool Graphm::isHaveL()
{
    int n=numVertex;
    int x[n];//入度数组
    int y[n];//出度数组
    //初始化入度出度数组
    for (int i=0;i<n;i++)
    {
        x[i]=0;
        y[i]=0;
    }
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            if (matrix[i][j]<INFINITE&&matrix[i][j]>0)
                x[i]++;
            if (matrix[j][i]<INFINITE&&matrix[j][i]>0)
                y[i]++;
        }
        if (x[i]==0&&y[i]==n-1)
                return true;
    }
    return false;
}
//----------------------------------------------------------------

// 测试Graphm的函数
void testGraphm()
{
    const int N = 5; //图7.2中G1表示的无向图

int A[N][N] =
    {
        //        V0 V1 V2 V3 V4
	/*V0*/    {0, 0, 1, 1, 0},
	/*V1*/    {0, 0, 0, 1, 1},
	/*V2*/    {1, 0, 0, 1, 1},
	/*V3*/    {1, 1, 1, 0, 0},
	/*V4*/    {0, 1, 1, 0, 0}
    };
    Graphm aGraph(N);              // 建立图
    aGraph.IniGraphm(&aGraph, (int *)A); // 初始化图
    cout << "DFS: ";
    aGraph.DFS(aGraph, 0);
    cout << endl;

    for (int i = 0; i < aGraph.VerticesNum(); i ++) //把Mark改回UNVISITED
        aGraph.Mark[i] = UNVISITED;

    cout << "BFS: ";
    aGraph.BFS(aGraph, 0);
    cout << endl;

}
