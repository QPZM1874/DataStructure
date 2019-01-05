//*************** AdjacencyList.h **************//
// 图的相接表示法
#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H
#include <iostream>
#include "Graph.h"
using namespace std;

/*
#define UNVISITED 0
#define VISITED 1
#define INFINITE 0xffffffff
#define N 5 // 定义图的顶点数
*/


struct listUnit       //邻接表表目中数据部分的结构定义
{
    int vertex;      //边的终点
    int weight;      //边的权
};

template<class Elem>   //边链表元素
class Link
{
public:
    Elem element;      //表目的数据
    Link *next;        //表目指针，指向下一个表目
    Link(const Elem& elemval,Link *nextval = NULL)    //构造函数
    {
        element = elemval;
        next = nextval;
    }
    Link(Link *nextval = NULL)   //构造函数，边信息未知！
    {
        next = nextval;
    }
};

template<class Elem>   //边链表
class LList
{
public:
    Link<Elem>* head;  //head指针并不储存任何实际元素，其存在只是为了操作方便
    LList()            //构造函数
    {
        head = new Link<Elem>();
    }
    void removeall()     //释放边表所有表目占据的空间
    {
        Link<Elem> *fence;
        while(head != NULL)    //逐步释放每个表目占据的空间
        {
            fence = head;
            head = head->next;
            delete fence;
        }
    }
    ~LList()  				//析构函数
    {
        removeall();
    }
};


class Graphl: public Graph
{
private:
    LList<listUnit> *graList;  //graList是保存所有边表的数组
public:
    Graphl(int numVert):Graph(numVert)    //构造函数
    {
        graList = new LList<listUnit>[numVertex]; /*为graList数组申请空间，图有
										  numVertex个顶点，则有numVertex个边表*/
    }
    ~Graphl()                           //析构函数
    {
        delete [] graList;			//释放空间
    }

    Edge FirstEdge(int oneVertex);      //返回顶点oneVertex的第一条边
    Edge NextEdge(Edge preEdge);     // 返回与边PreEdge有相同关联顶点的下一条边
    void setEdge(int from,int to,int weight);     //为图设定一条边
    void delEdge(int from,int to);             //删掉图的一条边
    void IniGraphl(Graphl *Graphl, int * adj); //用按行存储的邻接矩阵初始化邻接表
    void DFS(Graph& G, int v);
    void BFS(Graph& G, int v);
    void Visit(Graph &G, int v);
    void TransposeList();

};

//---------------------------------------------------------

// 测试Graphl的函数
void testGraphl();

#endif // ADJACENCYLIST_H
