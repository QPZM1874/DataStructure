#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H
#include "Graph.h"

// 图的相邻矩阵表示法

class Graphm : public Graph   //派生于抽象类Graph
{
private:
    int **matrix;				//指向相邻矩阵的指针

public:
    // 初始化。要求邻接矩阵按行顺序存储在adj开始内存中！
    void IniGraphm(Graphm * Graphm, int * adj);
    void DFS(Graph &G, int v);			// 深度优先搜索
    void BFS(Graph &G, int v);			// 广度优先搜索
    void Visit(Graph &G, int v);		// 访问
public:
    Graphm(int numVert);   //构造函数
    ~Graphm();  							//析构函数
    Edge FirstEdge(int oneVertex);   	//返回顶点oneVertex的第一条边
    Edge NextEdge(Edge preEdge);    //返回与边PreEdge有相同关联顶点的下一条边
    void setEdge(int from, int to, int weight);   	//为图设定一条边
    void delEdge(int from,int to);        //删除图的一条边
    void TransposeMatrix();                    //返回图的转置
    void ConnecComponent1(Graphm&);   //求连通分量（无向图）
    void ConnecComponent2();   //求连通分量（有向图）
    bool isconnected(int m,int n);//判断图中m,n两点是否连通
    bool isHaveL();//判断图中是否含有漏
    double **ValueMatrix;//汇率矩阵
};

//---------------------------------------------------------

// 测试Graphm的函数
void testGraphm();


#endif // ADJACENCYMATRIX_H
