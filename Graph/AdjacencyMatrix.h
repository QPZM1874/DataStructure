#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H
#include "Graph.h"

// ͼ�����ھ����ʾ��

class Graphm : public Graph   //�����ڳ�����Graph
{
private:
    int **matrix;				//ָ�����ھ����ָ��

public:
    // ��ʼ����Ҫ���ڽӾ�����˳��洢��adj��ʼ�ڴ��У�
    void IniGraphm(Graphm * Graphm, int * adj);
    void DFS(Graph &G, int v);			// �����������
    void BFS(Graph &G, int v);			// �����������
    void Visit(Graph &G, int v);		// ����
public:
    Graphm(int numVert);   //���캯��
    ~Graphm();  							//��������
    Edge FirstEdge(int oneVertex);   	//���ض���oneVertex�ĵ�һ����
    Edge NextEdge(Edge preEdge);    //�������PreEdge����ͬ�����������һ����
    void setEdge(int from, int to, int weight);   	//Ϊͼ�趨һ����
    void delEdge(int from,int to);        //ɾ��ͼ��һ����
    void TransposeMatrix();                    //����ͼ��ת��
    void ConnecComponent1(Graphm&);   //����ͨ����������ͼ��
    void ConnecComponent2();   //����ͨ����������ͼ��
    bool isconnected(int m,int n);//�ж�ͼ��m,n�����Ƿ���ͨ
    bool isHaveL();//�ж�ͼ���Ƿ���©
    double **ValueMatrix;//���ʾ���
};

//---------------------------------------------------------

// ����Graphm�ĺ���
void testGraphm();


#endif // ADJACENCYMATRIX_H
