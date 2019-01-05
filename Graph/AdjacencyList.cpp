// AdjacencyList.cpp
// �ڱ��ʾͼ����Graphm��ʵ��

#include "AdjacencyList.h"
#include <iostream>
#include <queue>
using namespace std;


Edge Graphl::FirstEdge(int oneVertex)      //���ض���oneVertex�ĵ�һ����
{
    Edge myEdge;                   //��myEdge����Ϊ�����ķ���ֵ
    myEdge.from = oneVertex;       //������oneVertex��Ϊ��myEdge��ʼ��
    /*graList[oneVertex].head������Ƕ���oneVertex�ı߱�
    temp->nextָ�򶥵�oneVertex�ĵ�һ����(���temp->next
    ��Ϊnull)*/
    Link<listUnit> *temp = graList[oneVertex].head;
    if(temp->next != NULL)           //�������oneVertex�ĵ�һ����ȷʵ����
    {
        myEdge.to = temp->next->element.vertex;
        myEdge.weight = temp->next->element.weight;
    }
    /*����ҵ��˶���oneVertex�ĵ�һ����,�򷵻ص�myEdgeȷʵ��һ����;���û��
    �ҵ�����oneVertex�ĵ�һ����,��myEdge�ĳ�Ա����toΪ-1,����IsEdge������
    �Ͽ�֪myEdge����һ����*/
    return myEdge;
}

Edge Graphl::NextEdge(Edge preEdge)     // �������PreEdge����ͬ�����������һ����
{
    Edge myEdge;			 		// myEdge�ĳ�ʼ��Ա����toΪ-1
    myEdge.from = preEdge.from;  		// ���ߵ�ʼ����Ϊ����һ���ߵ���ͬ
    Link<listUnit> *temp = graList[preEdge.from].head;		// tempָ��߱�ͷһ��
    while (temp->next != NULL && temp->next->element.vertex <= preEdge.to)
        temp = temp->next; 			// ȷ����preEdge��λ��
    if (temp->next != NULL)  		// ��preEdge����һ���ߴ���
    {
        myEdge.to = temp->next->element.vertex;
        myEdge.weight = temp->next->element.weight;
    }
    return myEdge;					// ���û���ҵ���һ���ߣ�myEdge.to=-1
}

void Graphl::setEdge(int from,int to,int weight)     //Ϊͼ�趨һ����
{
    if (from==to||weight>=INFINITE)
        return;
    Link<listUnit> *temp = graList[from].head;  /*graList[from].head������Ƕ���from��
													�߱�temp->nextָ�򶥵�from�ĵ�һ����
													(���temp->next��Ϊnull)*/
    while(temp->next != NULL && temp->next->element.vertex < to)
        temp = temp->next;   /*ȷ����(from,to)��<from,to>�ڱ߱��е�λ��,���������,
									���(from,to)��<from,to>Ϊ�¼ӵ�һ����*/
    if(temp->next == NULL)
    {
        /*��(from,to)��<from,to>�ڱ߱��в��������ڱ߱������
        							����������,���ڱ߱��м���������*/
        temp->next = new Link<listUnit>;
        temp->next->element.vertex = to;
        temp->next->element.weight = weight;
        numEdge++;
        Indegree[to]++;
        return;
    }
    if(temp->next->element.vertex == to)
    {
        /*��(from,to)��<from,to>�ڱ߱����Ѵ���,
        										��ֻ��Ҫ�ı�ߵ�Ȩֵ*/
        temp->next->element.weight = weight;
        return;
    }
    if(temp->next->element.vertex>to)
    {
        /*��(from,to)��<from,to>�ڱ߱��в�����,���ڱ߱���
        										������������,���ڱ߱��в���������*/
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

void Graphl::delEdge(int from,int to)             //ɾ��ͼ��һ����
{
    Link<listUnit> *temp = graList[from].head;  /*graList[from].head������Ƕ���from�ı߱�temp->nextָ�򶥵�from�ĵ�һ����(���temp->next��Ϊnull)*/
    while(temp->next != NULL && temp->next->element.vertex<to)
        temp = temp->next;	/*ȷ����(from,to)��<from,to>�ڱ߱��е�λ��(����ñߴ���)*/
    if(temp->next == NULL)
        return;        //��(from,to)��<from,to>�ڱ߱��в�����,����Ҫ���κβ���
    if(temp->next->element.vertex>to)
        return;        //��(from,to)��<from,to>�ڱ߱��в�����,����Ҫ���κβ���
    if(temp->next->element.vertex == to)
    {
        /*��(from,to)��<from,to>�ڱ߱��д�����ȷ
        									   ���˸ñ��ڱ߱��е�λ��,��ӱ߱��н���ɾ��*/
        Link<listUnit> *other = temp->next->next;
        delete temp->next;
        temp->next = other;
        numEdge--;
        Indegree[to]--;
        return;
    }
}

// �������ܣ�//�ð��д洢���ڽӾ����ʼ���ڽӱ�
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

//�������ܣ�������������㷨ʵ��
void Graphl::DFS(Graph& G, int v)       //������������㷨ʵ��
{
    G.Mark[v] = VISITED;       //���ʶ���v����������־λ
    Visit(G,v);
    //����V�ڽӵ���δ�����ʹ��Ķ��㣬���ݹ�ذ���������ȵķ�ʽ��������
    for(Edge e=G.FirstEdge(v); G.IsEdge(e); e=G.NextEdge(e))
        if(G.Mark[G.ToVertex(e)]== UNVISITED)
            DFS(G, G.ToVertex(e));
}


// �������ܣ������������
void Graphl::BFS(Graph& G, int v)              // ������������㷨��ʵ��
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

// ����Graphl�ĺ���
void testGraphl()
{
    const int N = 4;  //ͼ7.2��G1��ʾ������ͼ
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
    Graphl aGraph(N);              // ����ͼ
	aGraph.IniGraphl(&aGraph, (int *)A); // ��ʼ��ͼ

	cout << "DFS: ";
	aGraph.DFS(aGraph, 0);
	cout << endl;

	for (int i = 0; i < aGraph.VerticesNum(); i ++) //��Mark�Ļ�UNVISITED
		aGraph.Mark[i] = UNVISITED;

	cout << "BFS: ";
	aGraph.BFS(aGraph, 0);
	cout << endl;

}

