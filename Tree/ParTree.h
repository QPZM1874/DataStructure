// 树的父指针表示和并查集(union_findSet)
// 结点类的定义与实现
#ifndef PARTREE_H
#define PARTREE_H
#include "ParTreeNode.h"

//类ParTree描述了树的定义
template<class T>
class ParTree   								//树定义
{
public:
    ParTreeNode<T>* array;						//存储树结点的数组
    int	Size;									//数组大小
    ParTree(const int size);					//构造函数
    virtual ~ParTree();							//析构函数
    ParTreeNode<T> *Find(ParTreeNode<T>* node) const; //查找node结点的根结点
    ParTreeNode<T> *FindPC(ParTreeNode<T> *node) const; // 带压缩

    void Union(int i,int j);					//把下标为i，j的结点合并成一棵子树
    void UnionPC(int i, int j);                 //带压缩
    bool Different(int i,int j);				//判定下标为i，j的结点是否在一棵树中
};


//树的成员函数的实现
template <class T>
ParTree<T>::ParTree(const int size)   			//构造函数
{
    Size = size;
    array = new ParTreeNode<T>[size];
}

template <class T>
ParTree<T>::~ParTree()   						//构造函数
{
    delete []array;
}

// 函数功能：找到目标结点的根结点
template <class T>
ParTreeNode<T>*	ParTree<T>::Find(ParTreeNode<T>* node) const
{
    ParTreeNode<T>* pointer = node;
    while(pointer->getParent() != NULL)
        pointer = pointer->getParent();
    return pointer;
}

//函数功能：带路径压缩的Find算法
//将结点的父结点设置为结点所在树的根，即路径压缩，
//使树变得扁平，目的在于提高查找根结点的效率。
template <class T>
ParTreeNode<T> *ParTree<T>::FindPC(ParTreeNode<T> *node) const
{
    if (node->getParent() == NULL)
        return node;

    node->setParent(FindPC(node->getParent()));
    return node->getParent();
}

//函数功能：判定下标为i，j的结点是否在一棵树中
template<class T>
bool ParTree<T>::Different(int i,int j)
{
    ParTreeNode<T>* pointeri = Find(&array[i]);		//找到结点i的根
    ParTreeNode<T>* pointerj = Find(&array[j]);		//找到结点j的根
    return pointeri != pointerj;
}

//把下标为i，j的结点合并成一棵子树
//使用"重量权衡合并规则"
template<class T>
void ParTree<T>::Union(int i,int j)
{
    ParTreeNode<T>* pointeri = Find(&array[i]);		//找到结点i的根
    ParTreeNode<T>* pointerj = Find(&array[j]);		//找到结点j的根
    if(pointeri != pointerj)
    {
        if(pointeri->getCount()>=pointerj->getCount())
        {
            pointerj->setParent(pointeri);
            pointeri->setCount(pointeri->getCount()+pointerj->getCount());
        }
        else
        {
            pointeri->setParent(pointerj);
            pointerj->setCount(pointeri->getCount()+pointerj->getCount());
        }
    }
}

// 函数功能：归并两个集合， 带压缩
template <class T>
void ParTree<T>::UnionPC(int i, int j)
{
    ParTreeNode<T> *pointeri = FindPC(&array[i]);  //i提升到根的孩子
    ParTreeNode<T> *pointerj = FindPC(&array[j]);  //j提升到根的孩子

    if (pointeri != pointerj)
    {
        if (pointeri->getCount() >= pointerj->getCount())
        {
            pointerj->setParent(pointeri);
            pointeri->setCount(pointeri->getCount() + pointerj->getCount());
        }
        else
        {
            pointeri->setParent(pointerj);
            pointerj->setCount(pointeri->getCount() + pointerj->getCount());
        }
    }
}

#endif // PARTREE_H
