//*************** AdjacencyList.h **************//
// ͼ����ӱ�ʾ��
#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H
#include <iostream>
#include "Graph.h"
using namespace std;

/*
#define UNVISITED 0
#define VISITED 1
#define INFINITE 0xffffffff
#define N 5 // ����ͼ�Ķ�����
*/


struct listUnit       //�ڽӱ��Ŀ�����ݲ��ֵĽṹ����
{
    int vertex;      //�ߵ��յ�
    int weight;      //�ߵ�Ȩ
};

template<class Elem>   //������Ԫ��
class Link
{
public:
    Elem element;      //��Ŀ������
    Link *next;        //��Ŀָ�룬ָ����һ����Ŀ
    Link(const Elem& elemval,Link *nextval = NULL)    //���캯��
    {
        element = elemval;
        next = nextval;
    }
    Link(Link *nextval = NULL)   //���캯��������Ϣδ֪��
    {
        next = nextval;
    }
};

template<class Elem>   //������
class LList
{
public:
    Link<Elem>* head;  //headָ�벢�������κ�ʵ��Ԫ�أ������ֻ��Ϊ�˲�������
    LList()            //���캯��
    {
        head = new Link<Elem>();
    }
    void removeall()     //�ͷű߱����б�Ŀռ�ݵĿռ�
    {
        Link<Elem> *fence;
        while(head != NULL)    //���ͷ�ÿ����Ŀռ�ݵĿռ�
        {
            fence = head;
            head = head->next;
            delete fence;
        }
    }
    ~LList()  				//��������
    {
        removeall();
    }
};


class Graphl: public Graph
{
private:
    LList<listUnit> *graList;  //graList�Ǳ������б߱������
public:
    Graphl(int numVert):Graph(numVert)    //���캯��
    {
        graList = new LList<listUnit>[numVertex]; /*ΪgraList��������ռ䣬ͼ��
										  numVertex�����㣬����numVertex���߱�*/
    }
    ~Graphl()                           //��������
    {
        delete [] graList;			//�ͷſռ�
    }

    Edge FirstEdge(int oneVertex);      //���ض���oneVertex�ĵ�һ����
    Edge NextEdge(Edge preEdge);     // �������PreEdge����ͬ�����������һ����
    void setEdge(int from,int to,int weight);     //Ϊͼ�趨һ����
    void delEdge(int from,int to);             //ɾ��ͼ��һ����
    void IniGraphl(Graphl *Graphl, int * adj); //�ð��д洢���ڽӾ����ʼ���ڽӱ�
    void DFS(Graph& G, int v);
    void BFS(Graph& G, int v);
    void Visit(Graph &G, int v);
    void TransposeList();

};

//---------------------------------------------------------

// ����Graphl�ĺ���
void testGraphl();

#endif // ADJACENCYLIST_H
