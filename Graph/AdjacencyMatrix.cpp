// AdjacencyMatrix.cpp
// �ڽӾ����ʾͼ����Graphm��ʵ��

#include "AdjacencyMatrix.h"
#include <iostream>
#include <queue>
using namespace std;

Graphm::Graphm(int numVert):Graph(numVert)   //���캯��
{
    int i, j;			//i, j��Ϊforѭ���еļ�����
    matrix = (int **)new int*[numVertex]; /*����matrix����,��������numVertex��Ԫ��,ÿ��Ԫ��������ָ������*/
    ValueMatrix=(double **)new double *[numVertex];
    for (i = 0; i < numVertex; i ++)		/*matrix�����ÿ��Ԫ��,��ָ��һ������numVertex��Ԫ�ص�����*/
        {
            matrix[i] = new int[numVertex];
            ValueMatrix[i]=new double [numVertex];
        }

    for (i = 0; i < numVertex; i++)       /*���ھ��������Ԫ�ض���ʼ��Ϊ0,�������Ԫ��matrix[i][j]��Ϊ0,���������i�붥��j֮����һ����,�ߵ�Ȩ��Ϊmatrix[i][j]��ֵ*/
        for (j = 0; j < numVertex; j ++)
            {
                matrix[i][j] = 0;
                ValueMatrix[i][j]=0;
            }
}

Graphm::~Graphm()  							//��������
{
    for (int i = 0; i < numVertex; i ++)
        delete [] matrix[i];			//�ͷ�ÿ��matrix[i]����Ŀռ�
    delete [] matrix;				//�ͷ�matrixָ��ָ��Ŀռ�
}

Edge Graphm::FirstEdge(int oneVertex)   	//���ض���oneVertex�ĵ�һ����
{
    Edge myEdge;						//��myEdge����Ϊ�����ķ���ֵ
    myEdge.from = oneVertex;			//������oneVertex��Ϊ��myEdge��ʼ��

    for (int i = 0; i < numVertex; i ++)
    {
        /*
          ����Ѱ�ҵ�һ��ʹ��matrix[oneVertex][i]
          ��Ϊ0��iֵ����ô��(oneVertex,i)����
          ��<oneVertex,i>��Ϊ����oneVertex
          �ĵ�һ���ߣ�������i��Ϊ��myEdge���յ��myEdge
          ��ȨΪ����Ԫ��matrix[oneVertex][i]��ֵ
        */
        if (matrix[oneVertex][i] != 0&&matrix[oneVertex][i]<INFINITE)
        {
            myEdge.to = i;
            myEdge.weight = matrix[oneVertex][i];
            break;
        }
    }
    return myEdge;
    /*����ҵ��˶���oneVertex�ĵ�һ����,�򷵻ص�myEdgeȷʵ��һ���ߣ�
      ���û���ҵ�����oneVertex�ĵ�һ����,��myEdge�ĳ�Ա����toΪ-1��
      ����IsEdge�����жϿ�֪myEdge����һ����
    */
}

Edge Graphm::NextEdge(Edge preEdge)    //�������PreEdge����ͬ�����������һ����
{
    Edge myEdge;
    myEdge.from=preEdge.from; /*����myEdge��ʼ����Ϊ����һ����preEdge��ʼ����ͬ*/
    if(preEdge.to<numVertex)
    {
        //���preEdge.to+1>=numVertex,��ô�Ͳ�������һ������
        for(int i=preEdge.to+1; i<numVertex; i++)
        {
            /*Ѱ����һ��ʹ��//matrix[preEdge.from][i]��Ϊ0��iֵ,��ô
            (preEdge.from,i)����<preEdge.from,i>��Ϊ����preEdge.from����һ����*/
            if(matrix[preEdge.from][i]!=0)
            {
                myEdge.to=i;
                myEdge.weight=matrix[preEdge.from][i];
                break;
            }
        }
    }
    return myEdge;
    /*����ҵ��˶���preEdge.from����һ���ߣ��򷵻ص�myEdgeȷʵ��һ���ߣ�
    ���û���ҵ�����preEdge.from����һ���ߣ���myEdge�ĳ�Ա����toΪ-1��
    ����IsEdge�����жϿ�֪myEdge����һ����*/
}

void Graphm::setEdge(int from, int to, int weight)  //Ϊͼ�趨һ����
{
    if (matrix[from][to] <= 0)
    {
        /*���matrix[from][to]<=0�����(from,to) ����<from,to>
        ����������һ���ߣ�����ñ��Ѿ����ڣ�����ֻ�ǶԸñ߽����޸ģ�*/
        numEdge ++;
        Indegree[to] ++;
    }
    matrix[from][to] = weight;
}

void Graphm::delEdge(int from,int to)  //ɾ��ͼ��һ����
{
    if(matrix[from][to]>0)
    {
        /*���matrix[from][to]>0�����(from,to)����<from,to>ȷʵ���ڣ�
        ����ñ�ʵ���ϲ������ڣ��Ӷ����ض�ͼ�ı����Ͷ���to����Ƚ����޸ģ�*/
        numEdge--;
        Indegree[to]--;
    }
    matrix[from][to]=0;
}


// �������ܣ���ʼ��ͼ
void Graphm::IniGraphm(Graphm * Graphm, int * adj)
{
    int n = Graphm->numVertex;
    for (int i = 0; i < n; i ++)
    {
        for (int j = 0; j < n; j ++)
        {
            if (*(adj+i*n+j) > 0) //��֤Ȩ��>=0��ȱʡΪ0��
                Graphm->setEdge(i, j, *(adj+i*n+j));
        }
    }
}

//�������ܣ�������������㷨ʵ��
void Graphm::DFS(Graph& G, int v)       //������������㷨ʵ��
{
    G.Mark[v] = VISITED;       //���ʶ���v����������־λ
    Visit(G,v);
    //����V�ڽӵ���δ�����ʹ��Ķ��㣬���ݹ�ذ���������ȵķ�ʽ��������
    for(Edge e=G.FirstEdge(v); G.IsEdge(e) ; e=G.NextEdge(e))
    {
        if(G.Mark[G.ToVertex(e)]== UNVISITED)
        {
            DFS(G, G.ToVertex(e));
        }
    }
}


// �������ܣ������������
void Graphm::BFS(Graph& G, int v)     // ������������㷨��ʵ��
{
    using std::queue;
    queue<int> Q;                    // ��ʼ�������������Ҫ�õ��Ķ���
    Visit(G,v);                       // �ʶ���v����������־λ
    G.Mark[v] = VISITED;
    Q.push(v);                       // v���
    while (!Q.empty())                 // ���������Ȼ��Ԫ��
    {
        int u = Q.front ();              // ���ж���Ԫ��
        Q.pop();                     // ���ж���Ԫ�س���
        // �ö����ڽӵ���ÿһ��δ���ʶ��㶼���
        for (Edge e = G.FirstEdge(u); G.IsEdge(e); e = G.NextEdge(e))
            if (G.Mark[G.ToVertex(e)] == UNVISITED)
            {
                Visit(G, G.ToVertex(e));
                G.Mark[G.ToVertex(e)] = VISITED;
                Q.push(G.ToVertex(e));  // ���
            }
    }
}


// �������ܣ���ʾ����
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
//����ͼ����ͨ����
void Graphm::ConnecComponent1(Graphm & aGraph)
{
    int k=0;
    cout<<"��"<<++k<<"��ͨ����:";
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
            cout<<"��"<<++k<<"��ͨ����:";
            aGraph.DFS(aGraph,i);
            cout<<endl;
        }
        else    break;
    }
}

//�ж�ͼ�������Ƿ���ͨ
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
        if (tmp==n) return true;//temp=n ����m��n�ɴ�
        for (Edge e=FirstEdge(tmp);IsEdge(e);e=NextEdge(e))//��e���������ڵ�û����ǵĶ���������
        {
            if (Mark[ToVertex(e)]==UNVISITED)
                q.push(ToVertex(e));
        }
    }
    return false;
}
//����ͼ����ͨ����
void Graphm::ConnecComponent2()
{
    int k=0;
    int mark[numVertex];
    for (int i=0;i<numVertex;i++)
        mark[i]=UNVISITED;
    for (int i=0;i<numVertex-1;i++)
    {
        if (mark[i]==VISITED)   continue;
        cout<<"��"<<++k<<"��ͨ����:";
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
    int x[n];//�������
    int y[n];//��������
    //��ʼ����ȳ�������
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

// ����Graphm�ĺ���
void testGraphm()
{
    const int N = 5; //ͼ7.2��G1��ʾ������ͼ

int A[N][N] =
    {
        //        V0 V1 V2 V3 V4
	/*V0*/    {0, 0, 1, 1, 0},
	/*V1*/    {0, 0, 0, 1, 1},
	/*V2*/    {1, 0, 0, 1, 1},
	/*V3*/    {1, 1, 1, 0, 0},
	/*V4*/    {0, 1, 1, 0, 0}
    };
    Graphm aGraph(N);              // ����ͼ
    aGraph.IniGraphm(&aGraph, (int *)A); // ��ʼ��ͼ
    cout << "DFS: ";
    aGraph.DFS(aGraph, 0);
    cout << endl;

    for (int i = 0; i < aGraph.VerticesNum(); i ++) //��Mark�Ļ�UNVISITED
        aGraph.Mark[i] = UNVISITED;

    cout << "BFS: ";
    aGraph.BFS(aGraph, 0);
    cout << endl;

}
