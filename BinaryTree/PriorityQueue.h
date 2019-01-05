#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED

#include"MinHeap.h"
template <class T>
class PriorityQueue
{
private:
	MinHeap<T> mhp;
public:
    PriorityQueue(const int n);
     ~PriorityQueue()
    {

    };
    bool isEmpty( );							// 如果队列空，则返回真
    bool isLeaf(int pos) const;		 	    //如果是叶结点，返回TRUE
    int leftchild(int pos) const;		   	//返回左孩子位置
    int rightchild(int pos) const;			//返回右孩子位置
    int parent(int pos) const;				//返回父结点位置
    bool Remove(int pos, T& node);			//删除给定下标的元素
    bool Insert(const T& newNode);			//向队列中插入新元素newNode
    T& RemoveMin();				        	//从队列删除最小值
    void SiftUp(int position);			 //从position向上开始调整，使序列成为优先队列
    void SiftDown(int left);             //筛选法函数，参数left表示开始处理的数组下标
};
template<class T>
PriorityQueue<T>::PriorityQueue(const int n)
{
    if (n<=0)
        return;
    mhp.MaxSize=n;
    mhp.CurrentSize=0;
    mhp.heapArray=new T[n];
}
template<class T>
bool PriorityQueue<T>::isEmpty()
{
    return mhp.isEmpty();
}

template<class T>
bool PriorityQueue<T>::isLeaf(int pos) const
{
    return mhp.isLeaf(pos);
}

template<class T>
int PriorityQueue<T>::leftchild(int pos) const
{
    return mhp.leftchild(pos);					//返回左孩子位置
}

template<class T>
int PriorityQueue<T>::rightchild(int pos) const
{
    return mhp.rightchild(pos);				  //返回右孩子位置
}

template<class T>
int PriorityQueue<T>::parent(int pos) const
{
    return mhp.parent(pos);					   //返回父结点位置
}

template <class T>
bool PriorityQueue<T>::Insert(const T& newNode)
{
  // mhp.Insert(newNode);
   return mhp.Insert(newNode);
}

template<class T>
void PriorityQueue<T>::SiftUp(int position)
{
    mhp.SiftUp(position);
}


template<class T>
T& PriorityQueue<T>::RemoveMin()
{
	//mhp.RemoveMin();
	return mhp.RemoveMin();
}

template<class T>
bool PriorityQueue<T>::Remove(int pos, T& node)      	// 删除给定下标的元素
{
  return  mhp.Remove(pos,node);
}


template <class T>
void PriorityQueue<T>::SiftDown(int left)
{
  mhp.SiftDown();
}


#endif // PRIORITYQUEUE_H_INCLUDED
