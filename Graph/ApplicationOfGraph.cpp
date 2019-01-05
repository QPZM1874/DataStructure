// ApplicaitonOfGraph.cpp
// ͼ��Ӧ��ApplicationOfGraph.h�к��������ʵ��

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

#include "ApplicationOfGraph.h"
#include "AdjacencyMatrix.h"
#include "MinHeap.h"
#include "ParTree.h"


// �������ܣ���ʾ����������
void Visit(Graph &G, int v)
{
    cout << "C" << v << " ";
}

// �ö���ʵ�ֵ�ͼ��������
void TopsortbyQueue(Graph& G)
{
    //���з�ʽʵ�ֵ���������
    for(int i=0; i<G.VerticesNum(); i++)  //��ʼ��Mark����
        G.Mark[i]=UNVISITED;
    using std::queue;
    queue<int> Q;                     //��ʼ������
    for(int i=0; i<G.VerticesNum(); i++)
        if(G.Indegree[i]==0)
            Q.push(i);                //ͼ�����Ϊ0�Ķ������
    while(!Q.empty())                 //��������л���ͼ�Ķ���
    {
        int V=Q.front();
        Q.pop();                     //һ���������
        Visit(G,V);
        G.Mark[V]=VISITED;
        for(Edge e= G.FirstEdge(V); G.IsEdge(e); e=G.NextEdge(e))
        {
            G.Indegree[G.ToVertex(e)]--;  //������֮���ڵĶ������-1
            if(G.Indegree[G.ToVertex(e)]==0)
                Q.push(G.ToVertex(e));   //���Ϊ0�Ķ������
        }
    }
    for(int i=0; i<G.VerticesNum(); i++)
        if(G.Mark[i]==UNVISITED)
        {
            cout<<" ��ͼ�л���";        //ͼ�л�
            break;
        }
}

// ������������
void testTopologicalSort()
{
    const int N = 9;

    //ͼ7.18��ʾ�γ����ȹ�ϵ�������޻�ͼ���ڽӾ���
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

    Graphm aGraph(N);     // ����ͼ����
    aGraph.IniGraphm(&aGraph, (int *)A); // ��A[N][N]��ʼ��ͼ����
    cout << "Topological sort by Queue is : " << endl;
    TopsortbyQueue(aGraph);
}

//-----------------------------------------------------------------------

// Dijkstra�㷨��
// ����G��ͼ������s��Դ���㣬D�Ǳ�����̾��뼰��·��������
// �����ڲ��������飬�����ⲿʹ�ã���̫Ѱ��������!!!
void Dijkstra(Graph& G, int s, Dist* &D)
{

    D = new Dist[G. VerticesNum()];          	// D����
    for (int i = 0; i < G.VerticesNum(); i++)   // ��ʼ��Mark���顢D����
    {
        G.Mark[i] = UNVISITED;
        D[i].index = i;
        D[i].length = INFINITE;
        D[i].pre = s;
    }
    D[s].length = 0;
    MinHeap<Dist> H(G.EdgesNum());   // ��Сֵ�ѣ�minheap��������������������
    H.Insert(D[s]);
    for (int i = 0; i < G.VerticesNum(); i++)  //ÿ��һ�����룬���ж�������
    {
        bool FOUND = false;
        Dist d;
        while (!H.isEmpty())
        {
            d = H.RemoveMin();
            if (G.Mark[d.index] == UNVISITED)   //�ҵ�����s����Ķ���
            {
                FOUND = true;
                break;
            }
        }
        if (!FOUND) break;      // �ɴ������꣬����·������ѭ������������
        int v = d.index;
        G.Mark[v] = VISITED;           		// ��־�õ�·�������
        // v�����·�����(����U����)��ɨ��v�������ڽ��u��
        // ��d(s,v)+w(v,u)<d(s,u)�����޸�D[u]������D[u]���Ƽ���ѡ�
        // ���Ƕ��п��ܴ���s��ͬһ����Ķ��������󣬺���������̡�
        //��v�������ڽӵ�ѭ�������ڽӵ�洢˳����м���ַ��ڽӵ㣬
        //ѭ��������ֹ�������©��������ڽӵ㡣
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

// ���Dijkstra�㷨��·����Ϣ
// D-������飬n-�������
void pathInfoOfDijkstra(Dist * D, int n)
{

    for (int i=0; i<n; i++) //��·������ѭ��
        cout << "(" << D[i].length << "," << D[i].index << ")";
    cout << endl;
}

// ���Dijkstra�õ���·��
// D-������飬s-Դ���㣬n-�������
void pathOfDijkstra(Dist * D, int s, int n)
{
    stack<int> stk; // ����ѹ��·��������
    for (int i=1; i<n; i++) //��·������ѭ��
    {
        // ����ȷ��·���ϵĽ��
        int k = i;
        while (k!=s)     //��ʼ��δ��ջ
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

// ����Dijkstra�㷨
void testDijkstra()
{

        const int N = 5;  //ͼ7.19  ��Դ���·����ʾ��
        int A[N][N] =
        {
            //v0  v1  v2  v3  v4
            {0, 10,  INFINITE, 30, 100},
            {0,  0, 50,  INFINITE,  INFINITE},
            {INFINITE,  INFINITE,  0,  INFINITE, 10},
            {INFINITE, 10, 20,  0, 60},
            {INFINITE,  INFINITE,  INFINITE, INFINITE,  0}
        };

/*    const int N = 3; // ͼ7.20��Ӧ�Ĵ�Ȩ����
    int A[N][N] =
    {
        //	V0    V1    V2
        {0, INFINITE, 2},
        {5,    0,     8},
        {INFINITE, 3, 0}
    };
*/
    Graphm aGraph(N); // ����ͼ
    aGraph.IniGraphm(&aGraph, (int *)A); // ��ʼ��ͼ
    Dist *D;

    Dijkstra(aGraph, 0, D);

    cout << "����õ���Dist���飺" << endl;
    pathInfoOfDijkstra(D, N);

    cout << "��Dist���������·����" << endl;
    pathOfDijkstra(D, 0, N);

    delete []D;
}

//-----------------------------------------------------------------------

//Floyd�㷨
//D�Ƕ���ָ�룬����ָ����̬����Ľ���������
void Floyd(Graph& G, Dist** &D)
{
    int i,j,v; // i,j,vѭ�����Ʊ���

    // Ϊ����D����ռ�
    D = new Dist*[G.VerticesNum()];
    for (i = 0; i < G.VerticesNum(); i++)
        D[i] = new Dist[G.VerticesNum()];

    // ��ʼ������D
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
    //��v�������ڽӵ�ѭ�������ڽӵ�洢˳����м���ַ��ڽӵ㣬
    //ѭ��������ֹ�������©��������ڽӵ㡣
    for (v = 0; v < G.VerticesNum(); v++)
        for (Edge e = G.FirstEdge(v); G.IsEdgeForShortestPath(e); e = G.NextEdge(e))
        {
            D[v][G.ToVertex(e)].length = G.Weight(e);
            D[v][G.ToVertex(e)].pre = v;
        }

    // ����������������·����������v���������̾���
    for (v = 0; v < G.VerticesNum(); v++)
        for (i = 0; i < G.VerticesNum(); i++)
            for (j = 0; j < G.VerticesNum(); j++)
                if (D[i][j].length > (D[i][v].length+D[v][j].length))
                {
                    D[i][j].length = D[i][v].length+D[v][j].length;
                    D[i][j].pre = D[v][j].pre;
                }
}

// ���Floyd�㷨��õ����ж����֮��ľ���
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

//��˳�����Floyd�㷨��õ�һ��·���ϵ����ж���
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

// ���Floyd�㷨��Dist����
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

//����Floyd�㷨
void testFloyd()
{
    /*
        const int N = 5;  //ͼ7.19  ��Դ���·����ʾ��
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
    const int N = 3; // ͼ7.20��Ӧ�Ĵ�Ȩ����
    int A[N][N] =
    {
        //	V0    V1    V2
        {0, INFINITE, 2},
        {5,    0,     8},
        {INFINITE, 3, 0}
    };

    Graphm aGraph(N); // ����ͼ
    aGraph.IniGraphm(&aGraph, (int*)A); // ��ʼ��ͼ

    Dist ** D;
    Floyd(aGraph, D);

    cout << "·����Ϣ����" << endl;
    pathInfoOfFloyd(D, N);


    cout << "����·����" << endl;
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            printOnePath(D, N, i, j);

    // �ͷ�ΪD����Ŀռ�
    for (int i = 0; i < N; i++)
        delete []D[i];
    delete [] D;
}

//-----------------------------------------------------------------------

//��С��������Prim�㷨��
//����G��ͼ������s�ǿ�ʼ���㣬����MST�Ǳ�����С֧���������бߵ�����
//����true��ʾ����С������
bool Prim(Graph& G, int s, Edge * &MST)
{
    int MSTtag = 0;       // ��С�������ߵļ���
    MST = new Edge[G.VerticesNum()-1];  // MST�ܵ�n-1���ߵ�����
    Dist *D;
    D = new Dist[G. VerticesNum()]; // V-U�ж��㵽U����С������
    for (int i = 0; i < G.VerticesNum(); i++) // ��ʼ��Mark���顢D����
    {
        G.Mark[i] = UNVISITED;
        D[i].index = i;
        D[i].length = INFINITE;
        D[i].pre = s;
    }

    D[s].length = 0;
    G.Mark[s]= VISITED;  // s����U����

    int v = s;
    for (int i = 0; i < G.VerticesNum()-1; i++)
    {
        if (D[v].length == INFINITE)
        {
            // ����ͨ������MST���ʵı�Ϊ�����
            cout << "return";
            delete [] D; // �ͷ�ΪD����Ŀռ�
            return false;
        }

        // ��Ϊv�ļ��룬��Ҫˢ��v�ڽӵ㵽U�ľ���
        for (Edge e = G.FirstEdge(v); G.IsEdgeForShortestPath(e); e = G.NextEdge(e))
            if (G.Mark[G.ToVertex(e)]!=VISITED && (D[G.ToVertex(e)].length > e.weight))
            {
                D[G.ToVertex(e)].length = e.weight;
                D[G.ToVertex(e)].pre = v;
            }

        v = minVertex(G, D);

        G.Mark[v] = VISITED;
        Edge edge(D[v].pre, D[v].index, D[v].length);
        MST[MSTtag] = edge; // ��MST�м���һ����
        MSTtag++;
    }

    delete [] D; // �ͷ�ΪD����Ŀռ�
    return true;
}

// ��Dist����������С��
// ������С�ߵ��±ꡣ
int minVertex(Graph& G, Dist* & D)
{
    int i, v;
    for (i=0; i<G.VerticesNum(); i++)
        if (G.Mark[i] == UNVISITED)
        {
            v = i; 						// ��vΪ����һ��δ���ʵĶ���
            break;
        }
    for (i=0; i<G.VerticesNum(); i++)
        if ((G.Mark[i] == UNVISITED) && (D[i] < D[v]))
            v = i;						// ����Ŀǰ���ֵľ�����С����Ķ���
    return v;
}

// �����С������
void outputMST(Edge * mst, int n)
{
    for (int i = 0; i < n - 1; i ++)
    {
        cout << "��" << i+1 << " : ";
        cout << "V" << mst[i].from << "->V" << mst[i].to << "   Weight is : " << mst[i].weight << endl;
    }
}

// ����Prim�㷨
void testPrim()
{
    const int N = 7; // ͼ7.24 ��Ȩͼ

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

    Graphm aGraph(N); // ����ͼ
    aGraph.IniGraphm(&aGraph, (int *)A); // ��ʼ��ͼ
    for (int k=0; k<7; k++)
    {
        Edge * mst;
        if (Prim(aGraph, k, mst))
        {
            cout <<"��" << k <<" ��ʼ���ɵ���С��������" << endl;
            outputMST(mst, N);

            // �ͷ�Ϊmst����Ŀռ�
            delete []mst;
        }
    }
}

//-----------------------------------------------------------------------

//��С��������Prim�㷨��
//����G��ͼ������MST�Ǳ�����С֧���������бߵ�����
//����false��ʾ��������С������
bool Kruskal(Graph& G, Edge* &MST)
{
    ParTree<int> A(G.VerticesNum());      //n����ͨ���������ɲ��鼯
    MinHeap<Edge> H(G.EdgesNum());        //��Сֵ�ѣ��洢�ߣ���Ч����С��

    MST=new Edge[G.VerticesNum()-1];      //��С������

    int MSTtag=0;                         //��С֧�����ߵļ���
    for(int i=0; i<G.VerticesNum(); i++)  //��ͼ�����б߲�����Сֵ��H��
        for(Edge e= G. FirstEdge(i); G.IsEdgeForShortestPath(e); e=G.NextEdge(e))
            if (G.FromVertex(e) < G.ToVertex(e)  //��Ϊ������ͼ������Ӧ��ֹ�ظ�����
                    && e.weight < INFINITE ) // ȨΪ������Ǳ�
                H.Insert(e);
    int EquNum=G.VerticesNum();              //��ʼʱ��|V|���ȼ���
    while(EquNum>1)                        //�ϲ��ȼ���
    {
        Edge e=H.RemoveMin();               //�����һ��Ȩ��С�ı�
        if(e.weight == INFINITE)
        {
            //��С�ߵ�ȨΪ�����ͼ����ͨ������������С������
            return false;
        }
        int from=G.FromVertex(e);            //��¼�����ߵ���Ϣ
        int to= G.ToVertex(e);
        if(A.Different(from,to))               //�����e���������㲻��һ���ȼ���
        {
            A.Union(from,to);     //����e�������������ڵ������ȼ���ϲ�Ϊһ��
            EquNum--;             //���ȼ���ĸ�����1
            MST[MSTtag] = e;      //����e�ӵ�MST
            MSTtag++;
        }
    }
    return true;
}

// ����testKruskal�㷨
void testKruskal()
{
    const int N = 7; // ͼ7.24 ��Ȩͼ

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

    Graphm aGraph(N); // ����ͼ
    aGraph.IniGraphm(&aGraph, (int *)A); // ��ʼ��ͼ

    Edge * mst;
    if (Kruskal(aGraph, mst))
    {
        cout <<"��С��������" << endl;
        outputMST(mst, N);

        // �ͷ�Ϊmst����Ŀռ�
        delete []mst;
    }
}
