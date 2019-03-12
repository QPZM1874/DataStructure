// 双标记先根周游序列表示、到长子-兄弟表示的转换。
// 双标记层次周游序列表示、到长子-兄弟表示的转换
#ifndef DUALTAGTREE_H
#define DUALTAGTREE_H

#include <iostream>
#include <stack>
#include "Tree.h"

using namespace std;

// 带"双标记"的顺序存储结点类
template <class T>
class DualTagTreeNode
{
public:              //公有为了简单
    T info;          //树结点信息
    int ltag;		 //左标记
    int rtag;        //右标记

    DualTagTreeNode(){};               //构造函数
    virtual ~DualTagTreeNode(){};      //析构函数
};

// 用森林的双标记先根序列创建对应的长子-兄弟二叉树
template <class T>
void createTreeWithTagedRootFirstSquence(DualTagTreeNode<T> *nodeArray, int count, Tree<T> & aTree)
{
    using std::stack;  //使用STL中的stack
    stack< TreeNode<T>* > aStack;

    aTree.DeleteSubTree(aTree.getRoot());  // 清空树结点

    //建立根结点
    TreeNode<T> * pointer = new TreeNode<T>;
    aTree.getRoot() = pointer;
    //处理一个结点
    for(int i = 0; i < count-1; i++)
    {
        pointer->setValue(nodeArray[i].info);
        if(nodeArray[i].rtag == 0)
            aStack.push(pointer);						//将结点压栈
        else
            pointer->setSibling(NULL);					//右兄弟设为空
        TreeNode<T>* temppointer = new TreeNode<T>;
        if(nodeArray[i].ltag == 0)
            pointer->setChild(temppointer);
        else
        {
            pointer->setChild(NULL);					//左孩子设为空
            pointer = aStack.top();
            aStack.pop();
            pointer->setSibling(temppointer);
        }
        pointer = temppointer;
    }
    //处理最后一个结点
    pointer->setValue(nodeArray[count-1].info);
    pointer->setChild(NULL);
    pointer->setSibling(NULL);
}


// 用森林的双标记层次序列创建对应的长子-兄弟二叉树
template <class T>
void createTreeWithTagedWidthFirstSquence(DualTagTreeNode<T> *nodeArray, int count, Tree<T> & aTree)
  {
	//由带双标记位的层次次序表示构造左孩子右兄弟方式表示的树
	using std::queue;          //使用STL队列
	queue<TreeNode<T>*> aQueue;
	//准备建立根结点
	TreeNode<T>* pointer=new TreeNode<T>;
    aTree.getRoot() = pointer;
	//处理一个结点
	for(int i=0;i<count-1;i++) {
		pointer->setValue(nodeArray[i].info);
		if(nodeArray[i].ltag==0)
			aQueue.push(pointer);					   //将结点入队
		else
			pointer->setChild(NULL);				   //左孩子设为空
		TreeNode<T>* temppointer=new TreeNode<T>;
		if(nodeArray[i].rtag == 0)
			pointer->setSibling(temppointer);
		else {
			pointer->setSibling(NULL);					//右兄弟设为空
			pointer=aQueue.front();                     //取队列首结点指针
			aQueue.pop();                            //队首元素出队列
			pointer->setChild(temppointer);
		}
		pointer=temppointer;
	}
	//处理最后一个结点
	pointer->setValue(nodeArray[count-1].info);
	pointer->setChild(NULL);
	pointer->setSibling(NULL);
}


#define N 10  //结点数量

// 函数功能：显示示例森林结构
void DisplayTree()
{
    cout << endl;
    cout << "      A              G      \n";
    cout << "   /  |  \\         /   \\   \n";
    cout << "  B   C    D      H     I   \n";
    cout << "     / \\          |         \n";
    cout << "    E   F         J         \n";
    cout << endl;
}

// 函数功能：显示森林结构的带双标记先根次序表示
template <class T>
void displayRootFirstNode(DualTagTreeNode<char> * nodeArray, int count)
{
    if (count<0) return;

    cout << "ltag == 0 , there is    a left child" << endl;
    cout << "ltag == 1 , there isn't a left child" << endl;
    cout << "rtag == 0 , there is    a right sibling" << endl;
    cout << "rtag == 1 , there isn't a right sibling" << endl << endl;

    cout << "info   ";
    for (int i = 0; i < N; i ++)
        cout << (nodeArray+i)->info << " ";
    cout << endl;

    cout << "ltag   ";
    for (int i = 0; i < N; i ++)
        cout << (nodeArray+i)-> ltag << " ";
    cout << endl;

    cout << "rtag   ";
    for (int i = 0; i < N; i ++)
        cout << (nodeArray+i)-> rtag << " ";
    cout << endl;
}

// 函数功能：显示森林结构的带双标记层次顺序表示
template <class T>
void displayWidthFirstNode(DualTagTreeNode<char> * nodeArray, int count)
{
    if (count<0) return;

	cout << "ltag =  0  have left child" << endl;
	cout << "ltag =  1  havn't left child" << endl;
	cout << "rtag =  0  have right sibling" << endl;
	cout << "rtag =  1  havn't right sibling" << endl << endl;

    cout << "info   ";
    for (int i = 0; i < N; i ++)
        cout << (nodeArray+i)->info << " ";
    cout << endl;

    cout << "ltag   ";
    for (int i = 0; i < N; i ++)
        cout << (nodeArray+i)-> ltag << " ";
    cout << endl;

    cout << "rtag   ";
    for (int i = 0; i < N; i ++)
        cout << (nodeArray+i)-> rtag << " ";
    cout << endl;
}



void testRootFirstSequenceTree()
{
    // 显示森林结构
    DisplayTree();

    // 示例森林结点信息
    char strInfo[N] = {'A', 'B', 'C', 'E', 'F', 'D', 'G', 'H', 'J', 'I'};
    int nRtag[N] = {0, 0, 0, 0, 1, 1, 1, 0, 1, 1};
    int nLtag[N] = {0, 1, 0, 1, 1, 1, 0, 0, 1, 1};

    // 创建双标记先根顺序结点序列
    DualTagTreeNode<char> *nodeArray = new DualTagTreeNode<char>[N];
    for (int i = 0; i < N; i ++)                   //设置带双标记位的先根次序结点类
    {
        nodeArray[i].info = strInfo[i];
        nodeArray[i].ltag = nLtag[i];
        nodeArray[i].rtag = nRtag[i];
    }
    displayRootFirstNode<char>(nodeArray, N);

    Tree<char> aTree;  // 创建长子-兄弟表示的空树
    createTreeWithTagedRootFirstSquence<char>(nodeArray, N, aTree);
    delete []nodeArray;

    cout << endl;
    cout << "先根周游：";
    aTree.RootFirstTraverse(aTree.getRoot());
    cout << endl;

    cout << "后根周游：";
    aTree.RootLastTraverse(aTree.getRoot());
    cout << endl;

    cout << "层次周游：";
    aTree.WidthTraverse(aTree.getRoot());
    cout << endl;
}


void testWidthFirstSequenceTree()
{
    // 显示森林结构
    DisplayTree();

    // 示例森林结点信息
    char strInfo[N] = {'A', 'G', 'B', 'C', 'D', 'H', 'I', 'E', 'F', 'J'};
	int nRtag[N] = {0, 1, 0, 0, 1, 0, 1, 0, 1, 1};
	int nLtag[N] = {0, 0, 1, 0, 1, 0, 1, 1, 1, 1};

    // 创建双标记层次顺序结点序列
    DualTagTreeNode<char> *nodeArray = new DualTagTreeNode<char>[N];
    for (int i = 0; i < N; i ++)                   //设置带双标记位的先根次序结点类
    {
        nodeArray[i].info = strInfo[i];
        nodeArray[i].rtag = nRtag[i];
        nodeArray[i].ltag = nLtag[i];
    }
    displayWidthFirstNode<char>(nodeArray, N);

    Tree<char> aTree;  // 创建长子-兄弟表示的空树
    createTreeWithTagedWidthFirstSquence<char>(nodeArray, N, aTree);
    delete []nodeArray;

    cout << endl;
    cout << "先根周游：";
    aTree.RootFirstTraverse(aTree.getRoot());
    cout << endl;

    cout << "后根周游：";
    aTree.RootLastTraverse(aTree.getRoot());
    cout << endl;

    cout << "层次周游：";
    aTree.WidthTraverse(aTree.getRoot());
    cout << endl;
}
#endif // DUALTAGTREE_H
