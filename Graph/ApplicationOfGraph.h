// ApplicationOfGraph.h
// 图的应用：拓扑排序、最短路径、最小生成树

#ifndef APPLICATIONOFGRAPH_H_INCLUDED
#define APPLICATIONOFGRAPH_H_INCLUDED
#include "Graph.h"

// 用队列实现的图拓扑排序
void TopsortbyQueue(Graph& G);

// 函数功能：显示排序后的序列
void Visit(Graph &G, int v);

// 测试拓扑排序
void testTopologicalSort();

//-----------------------------------------------------------------------

// Dijkstra算法中的路径数组元素类
class Dist         //定义Dist类，下面的Dijkstra算法和Floyd算法要用到
{
public:
    int index;      //顶点的索引值，仅Dijkstra算法会用到
    int length;     //顶点之间的距离
    int pre;        //路径最后经过的顶点
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

// Dijkstra算法
// 参数G是图，参数s是源顶点，D是保存最短距离及其路径的数组
// 函数内部申请数组，函数外部使用，不太寻常的做法!!!
void Dijkstra(Graph& G, int s, Dist * & D);

// 输出Dijkstra算法中路径信息
// D-结果数组，n-顶点个数
void pathInfoOfDijkstra(Dist * D, int n);

// 输出Dijkstra得到的路径
// D-结果数组，s-源顶点，n-顶点个数
void pathOfDijkstra(Dist * D, int s, int n);

// 测试Dijkstra算法
void testDijkstra();

//-----------------------------------------------------------------------

//Floyd算法
//D是二重指针，用于指代动态分配的结果对象矩阵
void Floyd(Graph& G, Dist** &D);

// 输出Floyd算法求得的所有顶点对之间的距离
void pathLengthOfFloyd(Dist ** D, int vertexesNum);

//按顺序输出Floyd算法求得的一条路径上的所有顶点
void printOnePath(Dist ** D, int vertexesNum, int start, int end);

// 输出Floyd算法中Dist矩阵
void pathInfoOfFloyd(Dist ** D, int vertexesNum);

//测试Floyd算法
void testFloyd();

//-----------------------------------------------------------------------

//最小生成树的Prim算法，
//参数G是图，参数s是开始顶点，参数MST是保存最小支撑树中所有边的数组
//返回true表示求到最小生成树
bool Prim(Graph& G, int s, Edge* &MST);

// 在Dist数组中找最小边
// 返回最小边的下标。
int minVertex(Graph& G, Dist* & D);

// 输出最小生成树
void outputMST(Edge * mst, int n);

// 测试Prim算法
void testPrim();

//-----------------------------------------------------------------------

//最小生成树的Prim算法，
//参数G是图，参数MST是保存最小支撑树中所有边的数组
//返回false表示不存在最小生成树
bool Kruskal(Graph& G, Edge* &MST);


// 测试testKruskal算法
void testKruskal();

#endif // APPLICATIONOFGRAPH_H_INCLUDED
