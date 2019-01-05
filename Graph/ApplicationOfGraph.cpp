// ApplicaitonOfGraph.cpp
// 图的应用ApplicationOfGraph.h中函数及类的实现

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

#include "ApplicationOfGraph.h"
#include "AdjacencyMatrix.h"
#include "MinHeap.h"
#include "ParTree.h"


// 函数功能：显示排序后的序列
void Visit(Graph &G, int v)
{
    cout << "C" << v << " ";
}

// 用队列实现的图拓扑排序
void TopsortbyQueue(Graph& G)
{
    //队列方式实现的拓扑排序
    for(int i=0; i<G.VerticesNum(); i++)  //初始化Mark数组
        G.Mark[i]=UNVISITED;
    using std::queue;
    queue<int> Q;                     //初始化队列
    for(int i=0; i<G.VerticesNum(); i++)
        if(G.Indegree[i]==0)
            Q.push(i);                //图中入度为0的顶点入队
    while(!Q.empty())                 //如果队列中还有图的顶点
    {
        int V=Q.front();
        Q.pop();                     //一个顶点出队
        Visit(G,V);
        G.Mark[V]=VISITED;
        for(Edge e= G.FirstEdge(V); G.IsEdge(e); e=G.NextEdge(e))
        {
            G.Indegree[G.ToVertex(e)]--;  //所有与之相邻的顶点入度-1
            if(G.Indegree[G.ToVertex(e)]==0)
                Q.push(G.ToVertex(e));   //入度为0的顶点入队
        }
    }
    for(int i=0; i<G.VerticesNum(); i++)
        if(G.Mark[i]==UNVISITED)
        {
            cout<<" 此图有环！";        //图有环
            break;
        }
}

// 测试拓扑排序
void testTopologicalSort()
{
    const int N = 9;

    //图7.18表示课程优先关系的有向无环图的邻接矩阵
    int A[N][N] =
    {
        //C0  C1  C2  C3  C4  C5  C6  C7  C8
        {0,  0,  1,  0,  0,  0,  0,  1,  0},
        {0,  0,  1,  1,  1,  0,  0,  0,  0},
        {0,  0,  0,  1,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  1,  1,  0,  0},
        {0,  0,  0,  0,  0,  1,  0,  0,  0},
        {0,  0,  0,  0,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  0,  0,  0,  1},
        {0,  0,  0,  0,  0,  0,  1,  0,  0}
    };

    Graphm aGraph(N);     // 建立图对象
    aGraph.IniGraphm(&aGraph, (int *)A); // 用A[N][N]初始化图对象
    cout << "Topological sort by Queue is : " << endl;
    TopsortbyQueue(aGraph);
}

//-----------------------------------------------------------------------

// Dijkstra算法。
// 参数G是图，参数s是源顶点，D是保存最短距离及其路径的数组
// 函数内部申请数组，函数外部使用，不太寻常的做法!!!
void Dijkstra(Graph& G, int s, Dist* &D)
{

    D = new Dist[G. VerticesNum()];          	// D数组
    for (int i = 0; i < G.VerticesNum(); i++)   // 初始化Mark数组、D数组
    {
        G.Mark[i] = UNVISITED;
        D[i].index = i;
        D[i].length = INFINITE;
        D[i].pre = s;
    }
    D[s].length = 0;
    MinHeap<Dist> H(G.EdgesNum());   // 最小值堆（minheap），最大个数不超过边数
    H.Insert(D[s]);
    for (int i = 0; i < G.VerticesNum(); i++)  //每次一个距离，共有顶点数个
    {
        bool FOUND = false;
        Dist d;
        while (!H.isEmpty())
        {
            d = H.RemoveMin();
            if (G.Mark[d.index] == UNVISITED)   //找到距离s最近的顶点
            {
                FOUND = true;
                break;
            }
        }
        if (!FOUND) break;      // 可达结点已完，跳出路径条数循环，函数结束
        int v = d.index;
        G.Mark[v] = VISITED;           		// 标志该点路径以求得
        // v的最短路径求得(进入U集合)，扫描v的所有邻结点u，
        // 若d(s,v)+w(v,u)<d(s,u)，则修改D[u]，并将D[u]复制加入堆。
        // 于是堆中可能存在s到同一顶点的多个距离对象，后加入距离更短。
        //对v的所有邻接点循环，若邻接点存储顺序的中间出现非邻接点，
        //循环不能终止，否则会漏掉后面的邻接点。
        for (Edge e = G.FirstEdge(v); G.IsEdgeForShortestPath(e); e = G.NextEdge(e))
        {
            if (D[G.ToVertex(e)].length > (D[v].length+G.Weight(e)))
            {
                D[G.ToVertex(e)].length = D[v].length+G.Weight(e);
                D[G.ToVertex(e)].pre = v;
                H.Insert(D[G.ToVertex(e)]);
            }
        }
    }
}

// 输出Dijkstra算法中路径信息
// D-结果数组，n-顶点个数
void pathInfoOfDijkstra(Dist * D, int n)
{

    for (int i=0; i<n; i++) //对路径个数循环
        cout << "(" << D[i].length << "," << D[i].index << ")";
    cout << endl;
}

// 输出Dijkstra得到的路径
// D-结果数组，s-源顶点，n-顶点个数
void pathOfDijkstra(Dist * D, int s, int n)
{
    stack<int> stk; // 逆向压入路径结点序号
    for (int i=1; i<n; i++) //对路径个数循环
    {
        // 逆向确定路径上的结点
        int k = i;
        while (k!=s)     //起始点未进栈
        {
            stk.push(k);
            k = D[k].pre;
        }

        cout << s;
        while (!stk.empty())
        {
            cout << "->" << stk.top();
            stk.pop();
        }
        cout << " : " << D[i].length << endl;
    }
}

// 测试Dijkstra算法
void testDijkstra()
{

        const int N = 5;  //图7.19  单源最短路径的示例
        int A[N][N] =
        {
            //v0  v1  v2  v3  v4
            {0, 10,  INFINITE, 30, 100},
            {0,  0, 50,  INFINITE,  INFINITE},
            {INFINITE,  INFINITE,  0,  INFINITE, 10},
            {INFINITE, 10, 20,  0, 60},
            {INFINITE,  INFINITE,  INFINITE, INFINITE,  0}
        };

/*    const int N = 3; // 图7.20对应的带权矩阵
    int A[N][N] =
    {
        //	V0    V1    V2
        {0, INFINITE, 2},
        {5,    0,     8},
        {INFINITE, 3, 0}
    };
*/
    Graphm aGraph(N); // 建立图
    aGraph.IniGraphm(&aGraph, (int *)A); // 初始化图
    Dist *D;

    Dijkstra(aGraph, 0, D);

    cout << "计算得到的Dist数组：" << endl;
    pathInfoOfDijkstra(D, N);

    cout << "从Dist数组产生的路径：" << endl;
    pathOfDijkstra(D, 0, N);

    delete []D;
}

//-----------------------------------------------------------------------

//Floyd算法
//D是二重指针，用于指代动态分配的结果对象矩阵
void Floyd(Graph& G, Dist** &D)
{
    int i,j,v; // i,j,v循环控制变量

    // 为数组D申请空间
    D = new Dist*[G.VerticesNum()];
    for (i = 0; i < G.VerticesNum(); i++)
        D[i] = new Dist[G.VerticesNum()];

    // 初始化数组D
    for (i = 0; i < G.VerticesNum(); i++)
        for (j = 0; j < G.VerticesNum(); j++)
        {
            if (i == j)
            {
                D[i][j].length = 0;
                D[i][j].pre = i;
            }
            else
            {
                D[i][j].length = INFINITE;
                D[i][j].pre = -1;
            }
        }
    //对v的所有邻接点循环，若邻接点存储顺序的中间出现非邻接点，
    //循环不能终止，否则会漏掉后面的邻接点。
    for (v = 0; v < G.VerticesNum(); v++)
        for (Edge e = G.FirstEdge(v); G.IsEdgeForShortestPath(e); e = G.NextEdge(e))
        {
            D[v][G.ToVertex(e)].length = G.Weight(e);
            D[v][G.ToVertex(e)].pre = v;
        }

    // 如果两个顶点间的最短路径经过顶点v，则更新最短距离
    for (v = 0; v < G.VerticesNum(); v++)
        for (i = 0; i < G.VerticesNum(); i++)
            for (j = 0; j < G.VerticesNum(); j++)
                if (D[i][j].length > (D[i][v].length+D[v][j].length))
                {
                    D[i][j].length = D[i][v].length+D[v][j].length;
                    D[i][j].pre = D[v][j].pre;
                }
}

// 输出Floyd算法求得的所有顶点对之间的距离
void pathLengthOfFloyd(Dist ** D, int vertexesNum)
{
    for (int i = 0; i < vertexesNum; i++)
    {
        for (int j = 0; j < vertexesNum; j++)
        {
            cout << D[i][j].length << "  ";
        }
        cout << endl;
    }
}

//按顺序输出Floyd算法求得的一条路径上的所有顶点
void printOnePath(Dist ** D, int vertexesNum, int start, int end)
{
    if (D[start][end].length == INFINITE) return;

    int * path = new int[vertexesNum];
    int vertexCount = 0;
    int tail = end;

    //path[vertexCount++] = tail;
    while (tail != start)
    {
        path[vertexCount++] = D[start][tail].pre;
        tail = D[start][tail].pre;
    }

    cout << "v" << start << "->" << "v" << end << " : ";
    for (int i = vertexCount-1; i >= 0; i--)
        cout << "v" << path[i] << "->";
    cout << "v" << end << endl;

    delete []path;
}

// 输出Floyd算法中Dist矩阵
void pathInfoOfFloyd(Dist ** D, int vertexesNum)
{
    for (int i = 0; i < vertexesNum; i++)
    {
        for (int j = 0; j < vertexesNum; j++)
        {
            cout << "(" << D[i][j].length << "," << D[i][j].pre <<")";
        }
        cout << endl;
    }
}

//测试Floyd算法
void testFloyd()
{
    /*
        const int N = 5;  //图7.19  单源最短路径的示例
        int A[N][N] =
        {
            //v0  v1  v2  v3  v4
            {0, 10,  INFINITE, 30, 100},
            {0,  0, 50,  INFINITE,  INFINITE},
            {INFINITE,  INFINITE,  0,  INFINITE, 10},
            {INFINITE, 10, 20,  0, 60},
            {INFINITE,  INFINITE,  INFINITE, INFINITE,  0}
        };
    */
    const int N = 3; // 图7.20对应的带权矩阵
    int A[N][N] =
    {
        //	V0    V1    V2
        {0, INFINITE, 2},
        {5,    0,     8},
        {INFINITE, 3, 0}
    };

    Graphm aGraph(N); // 建立图
    aGraph.IniGraphm(&aGraph, (int*)A); // 初始化图

    Dist ** D;
    Floyd(aGraph, D);

    cout << "路径信息矩阵：" << endl;
    pathInfoOfFloyd(D, N);


    cout << "所有路径：" << endl;
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            printOnePath(D, N, i, j);

    // 释放为D分配的空间
    for (int i = 0; i < N; i++)
        delete []D[i];
    delete [] D;
}

//-----------------------------------------------------------------------

//最小生成树的Prim算法，
//参数G是图，参数s是开始顶点，参数MST是保存最小支撑树中所有边的数组
//返回true表示求到最小生成树
bool Prim(Graph& G, int s, Edge * &MST)
{
    int MSTtag = 0;       // 最小生成树边的计数
    MST = new Edge[G.VerticesNum()-1];  // MST总的n-1条边的数组
    Dist *D;
    D = new Dist[G. VerticesNum()]; // V-U中顶点到U的最小边数组
    for (int i = 0; i < G.VerticesNum(); i++) // 初始化Mark数组、D数组
    {
        G.Mark[i] = UNVISITED;
        D[i].index = i;
        D[i].length = INFINITE;
        D[i].pre = s;
    }

    D[s].length = 0;
    G.Mark[s]= VISITED;  // s进入U集合

    int v = s;
    for (int i = 0; i < G.VerticesNum()-1; i++)
    {
        if (D[v].length == INFINITE)
        {
            // 非连通，遇到MST性质的边为无穷大
            cout << "return";
            delete [] D; // 释放为D分配的空间
            return false;
        }

        // 因为v的加入，需要刷新v邻接点到U的距离
        for (Edge e = G.FirstEdge(v); G.IsEdgeForShortestPath(e); e = G.NextEdge(e))
            if (G.Mark[G.ToVertex(e)]!=VISITED && (D[G.ToVertex(e)].length > e.weight))
            {
                D[G.ToVertex(e)].length = e.weight;
                D[G.ToVertex(e)].pre = v;
            }

        v = minVertex(G, D);

        G.Mark[v] = VISITED;
        Edge edge(D[v].pre, D[v].index, D[v].length);
        MST[MSTtag] = edge; // 在MST中加入一条边
        MSTtag++;
    }

    delete [] D; // 释放为D分配的空间
    return true;
}

// 在Dist数组中找最小边
// 返回最小边的下标。
int minVertex(Graph& G, Dist* & D)
{
    int i, v;
    for (i=0; i<G.VerticesNum(); i++)
        if (G.Mark[i] == UNVISITED)
        {
            v = i; 						// 让v为随意一个未访问的定义
            break;
        }
    for (i=0; i<G.VerticesNum(); i++)
        if ((G.Mark[i] == UNVISITED) && (D[i] < D[v]))
            v = i;						// 保存目前发现的具有最小距离的顶点
    return v;
}

// 输出最小生成树
void outputMST(Edge * mst, int n)
{
    for (int i = 0; i < n - 1; i ++)
    {
        cout << "边" << i+1 << " : ";
        cout << "V" << mst[i].from << "->V" << mst[i].to << "   Weight is : " << mst[i].weight << endl;
    }
}

// 测试Prim算法
void testPrim()
{
    const int N = 7; // 图7.24 带权图

    int A[N][N] =
    {
        //v0  v1  v2  v3  v4  v5  v6
        {0, 20,  INFINITE,  INFINITE,  1,  INFINITE,  INFINITE},
        {20, 0,  6,  4,  INFINITE,  INFINITE,  INFINITE},
        {INFINITE,  6,  0,  INFINITE,  INFINITE,  INFINITE,  2},
        {INFINITE,  4,  INFINITE,  0,  INFINITE, 12,  8},
        {1,  INFINITE,  INFINITE,  INFINITE,  0, 15,  0},
        {INFINITE,  INFINITE,  INFINITE, 12, 15,  0, 10},
        {INFINITE,  INFINITE,  2,  8,  INFINITE, 10,  0}
    };

    Graphm aGraph(N); // 建立图
    aGraph.IniGraphm(&aGraph, (int *)A); // 初始化图
    for (int k=0; k<7; k++)
    {
        Edge * mst;
        if (Prim(aGraph, k, mst))
        {
            cout <<"从" << k <<" 开始生成的最小生成树：" << endl;
            outputMST(mst, N);

            // 释放为mst分配的空间
            delete []mst;
        }
    }
}

//-----------------------------------------------------------------------

//最小生成树的Prim算法，
//参数G是图，参数MST是保存最小支撑树中所有边的数组
//返回false表示不存在最小生成树
bool Kruskal(Graph& G, Edge* &MST)
{
    ParTree<int> A(G.VerticesNum());      //n个连通分量，构成并查集
    MinHeap<Edge> H(G.EdgesNum());        //最小值堆，存储边，高效求最小边

    MST=new Edge[G.VerticesNum()-1];      //最小生成树

    int MSTtag=0;                         //最小支撑树边的计数
    for(int i=0; i<G.VerticesNum(); i++)  //将图的所有边插入最小值堆H中
        for(Edge e= G. FirstEdge(i); G.IsEdgeForShortestPath(e); e=G.NextEdge(e))
            if (G.FromVertex(e) < G.ToVertex(e)  //因为是无向图，所以应防止重复插入
                    && e.weight < INFINITE ) // 权为无穷大不是边
                H.Insert(e);
    int EquNum=G.VerticesNum();              //开始时有|V|个等价类
    while(EquNum>1)                        //合并等价类
    {
        Edge e=H.RemoveMin();               //获得下一条权最小的边
        if(e.weight == INFINITE)
        {
            //最小边的权为无穷大，图不连通，不存在在最小生成树
            return false;
        }
        int from=G.FromVertex(e);            //记录该条边的信息
        int to= G.ToVertex(e);
        if(A.Different(from,to))               //如果边e的两个顶点不在一个等价类
        {
            A.Union(from,to);     //将边e的两个顶点所在的两个等价类合并为一个
            EquNum--;             //将等价类的个数减1
            MST[MSTtag] = e;      //将边e加到MST
            MSTtag++;
        }
    }
    return true;
}

// 测试testKruskal算法
void testKruskal()
{
    const int N = 7; // 图7.24 带权图

    int A[N][N] =
    {
        //v0  v1  v2  v3  v4  v5  v6
        {0, 20,  INFINITE,  INFINITE,  1,  INFINITE,  INFINITE},
        {20, 0,  6,  4,  INFINITE,  INFINITE,  INFINITE},
        {INFINITE,  6,  0,  INFINITE,  INFINITE,  INFINITE,  2},
        {INFINITE,  4,  INFINITE,  0,  INFINITE, 12,  8},
        {1,  INFINITE,  INFINITE,  INFINITE,  0, 15,  0},
        {INFINITE,  INFINITE,  INFINITE, 12, 15,  0, 10},
        {INFINITE,  INFINITE,  2,  8,  INFINITE, 10,  0}
    };

    Graphm aGraph(N); // 建立图
    aGraph.IniGraphm(&aGraph, (int *)A); // 初始化图

    Edge * mst;
    if (Kruskal(aGraph, mst))
    {
        cout <<"最小生成树：" << endl;
        outputMST(mst, N);

        // 释放为mst分配的空间
        delete []mst;
    }
}
