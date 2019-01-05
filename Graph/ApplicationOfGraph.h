// ApplicationOfGraph.h
// ͼ��Ӧ�ã������������·������С������

#ifndef APPLICATIONOFGRAPH_H_INCLUDED
#define APPLICATIONOFGRAPH_H_INCLUDED
#include "Graph.h"

// �ö���ʵ�ֵ�ͼ��������
void TopsortbyQueue(Graph& G);

// �������ܣ���ʾ����������
void Visit(Graph &G, int v);

// ������������
void testTopologicalSort();

//-----------------------------------------------------------------------

// Dijkstra�㷨�е�·������Ԫ����
class Dist         //����Dist�࣬�����Dijkstra�㷨��Floyd�㷨Ҫ�õ�
{
public:
    int index;      //���������ֵ����Dijkstra�㷨���õ�
    int length;     //����֮��ľ���
    int pre;        //·����󾭹��Ķ���
    Dist() {};
    ~Dist() {};

    bool operator < (const Dist & arg)
    {
        return (length < arg.length);
    }
    bool operator == (const Dist &arg)
    {
        return (length==arg.length);
    }
    bool operator > (const Dist &arg)
    {
        return (length>arg.length);
    }
    bool operator <=(const Dist &arg)
    {
        return (length<=arg.length);
    }
    bool operator >= (const Dist &arg)
    {
        return (length>=arg.length);
    }
};

// Dijkstra�㷨
// ����G��ͼ������s��Դ���㣬D�Ǳ�����̾��뼰��·��������
// �����ڲ��������飬�����ⲿʹ�ã���̫Ѱ��������!!!
void Dijkstra(Graph& G, int s, Dist * & D);

// ���Dijkstra�㷨��·����Ϣ
// D-������飬n-�������
void pathInfoOfDijkstra(Dist * D, int n);

// ���Dijkstra�õ���·��
// D-������飬s-Դ���㣬n-�������
void pathOfDijkstra(Dist * D, int s, int n);

// ����Dijkstra�㷨
void testDijkstra();

//-----------------------------------------------------------------------

//Floyd�㷨
//D�Ƕ���ָ�룬����ָ����̬����Ľ���������
void Floyd(Graph& G, Dist** &D);

// ���Floyd�㷨��õ����ж����֮��ľ���
void pathLengthOfFloyd(Dist ** D, int vertexesNum);

//��˳�����Floyd�㷨��õ�һ��·���ϵ����ж���
void printOnePath(Dist ** D, int vertexesNum, int start, int end);

// ���Floyd�㷨��Dist����
void pathInfoOfFloyd(Dist ** D, int vertexesNum);

//����Floyd�㷨
void testFloyd();

//-----------------------------------------------------------------------

//��С��������Prim�㷨��
//����G��ͼ������s�ǿ�ʼ���㣬����MST�Ǳ�����С֧���������бߵ�����
//����true��ʾ����С������
bool Prim(Graph& G, int s, Edge* &MST);

// ��Dist����������С��
// ������С�ߵ��±ꡣ
int minVertex(Graph& G, Dist* & D);

// �����С������
void outputMST(Edge * mst, int n);

// ����Prim�㷨
void testPrim();

//-----------------------------------------------------------------------

//��С��������Prim�㷨��
//����G��ͼ������MST�Ǳ�����С֧���������бߵ�����
//����false��ʾ��������С������
bool Kruskal(Graph& G, Edge* &MST);


// ����testKruskal�㷨
void testKruskal();

#endif // APPLICATIONOFGRAPH_H_INCLUDED
