#include <iostream>
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "MinHeap.h"
#include "HuffmanTree.h"
#include "PriorityQueue.h"
using namespace std;

void testBinaryTree();
void testCreateBinaryTree();
void testBinarySearchTree();
void testMinHeap();
void testHuffmanTree();
void testPriorityQueue();

int main()
{
    //testBinaryTree();

    //testCreateBinaryTree();

    //testBinarySearchTree();

    testMinHeap();
    cout<<"-------------------------------------"<<endl;
    //testHuffmanTree();
    testPriorityQueue();
    return 0;
}
void testPriorityQueue()
{
    PriorityQueue<int> pq(8);
    int i;
    int temp,elem;
    int Key[] = {19,8,35,65,40,3,7,45} ;    //图例5.17所示的数组

    cout << "建优先队列：" << endl;    //此处为依次插入建堆。
    for(i = 0; i < 8; i++)
    {
        pq.Insert(Key[i]);
        cout<< Key[i] << " added." <<endl;
    }

    cout << "不断从队列删除最小值:" << endl;
    while (!pq.isEmpty())
    {
        temp = pq.RemoveMin();
        cout << temp << " ";
    }
    cout << endl;

    cout << "重建队列：" << endl;    //此处为依次插入建堆。
    for(i = 0; i < 8; i++)
    {
        pq.Insert(Key[i]);
        cout<< Key[i] << " added." <<endl;
    }

    cout<< "删除给定下标(3)的元素:" <<endl;
    pq.Remove(3,elem);
    cout<<  elem << " deleted." <<endl;

    cout<< "插入元素45:" <<endl;
   pq.Insert(45);

    cout << "不断从队列删除最小值:" << endl;
    while (!pq.isEmpty())
    {
        temp = pq.RemoveMin();
        cout << temp << " ";
    }
    cout << endl;
}
void testBinaryTree()
{
    //建一棵树(如图5.5所示)
    BinaryTree<char> a, b, c, d, e, f, g, h, i,nulltree;
    d.CreateTree('D', nulltree, nulltree);
    g.CreateTree('G', nulltree, nulltree);
    h.CreateTree('H', nulltree, nulltree);
    i.CreateTree('I', nulltree, nulltree);
    f.CreateTree('F', h, i);
    e.CreateTree('E', g, nulltree);
    b.CreateTree('B', d, e);
    c.CreateTree('C', nulltree, f);
    a.CreateTree('A', b, c);

    //前序周游二叉树
    cout << "Preorder sequence is: "<<endl;
    a.PreOrder(a.Root());				//递归
    cout << endl;
    cout << "Preorder sequence Without Recursion is: " <<endl;
    a.PreOrderWithoutRecursion(a.Root());//非递归
    cout << endl;

    //中序周游二叉树
    cout << "Inorder sequence is: "<<endl;
    a.InOrder(a.Root());			//递归
    cout << endl;
    cout << "Inorder sequence Without Recursion is: " <<endl;
    a.InOrderWithoutRecursion(a.Root());//非递归
    cout << endl;

    //后序周游二叉树
    cout << "Postorder sequence is: "<<endl;
    a.PostOrder(a.Root());			//递归
    cout << endl;
    cout << "Postorder sequence Without Recursion is: " <<endl;
    a.PostOrderWithoutRecursion(a.Root());//非递归
    cout << endl;

    //root
    cout << "Root is: " << a.Root()->value() <<endl;

    //delete tree
    a.DeleteBinaryTree(a.Root());
    cout<<"Tree is deleted."<<endl;        //没有问题，在析构函数中调用
}

void testCreateBinaryTree()
{
    BinaryTree<char> bt;  // 创建空树


    // 扩充前序序列
    char preList[] = {'A','B','D','*','*','E','G','*','*','*','C','*','F','H','*','*','I','*','*'};

    // 用数组提供结点
    bt.createWithNodesInArray(preList,'*');
    cout << "前序周游二叉树: "<<endl;
    bt.PreOrder(bt.Root());
    cout << endl;

    cout << "中序周游二叉树: "<<endl;
    bt.InOrder(bt.Root());
    cout << endl;

    cout << "后序周游二叉树: "<<endl;
    bt.PostOrder(bt.Root());
    cout << endl;

    // 控制台输入结点
    bt.createWithNodesInputed();
    bt.createWithNodesInArray(preList,'*');
    cout << "前序周游二叉树: "<<endl;
    bt.PreOrder(bt.Root());
    cout << endl;

    cout << "中序周游二叉树: "<<endl;
    bt.InOrder(bt.Root());
    cout << endl;

    cout << "后序周游二叉树: "<<endl;
    bt.PostOrder(bt.Root());
    cout << endl;
}



void testBinarySearchTree()
{
    const int N = 11;
    int K[N] = {50,19,35,55,20,5,100,52,88,53,92};        //建一棵图5.11所示的树
    BinarySearchTree<int> aBST;
    BinaryTreeNode<int > *newpointer, *node1, *node2;

    for (int i = 0; i < N; i ++) // 循环插入结点
    {
        newpointer = new BinaryTreeNode<int>();
        newpointer->setValue(K[i]);
        aBST.InsertNode(aBST.Root(), newpointer);      //依次插入结点

        if (K[i] == 52)                                 //记录待删除结点的指针node1
        {
            node1 = newpointer;
        }
        if (K[i] == 55)                                 //记录待删除结点的指针node2
            node2 = newpointer;
    }

    // 遍历结点
    cout << "中序周游二叉搜索树：" << endl;
    aBST.InOrder(aBST.Root());
    cout << endl;

    // 删除两个结点的改进算法
    cout << "删除结点52, 55." << endl;
    aBST.DeleteNodeEx(node1);
    aBST.DeleteNodeEx(node2);

    // 遍历节点
    cout << "删除结点之后中序周游二叉搜索树：" << endl;
    aBST.InOrder(aBST.Root());
    cout << endl;
}


void testMinHeap()
{
    MinHeap<int> minheap(8);
    int i;
    int temp,elem;
    int Key[] = {19,8,35,65,40,3,7,45} ;    //图例5.17所示的数组

    cout << "建堆：" << endl;    //此处为依次插入建堆。
    for(i = 0; i < 8; i++)
    {
        minheap.Insert(Key[i]);
        cout<< Key[i] << " added." <<endl;
    }

    cout << "不断从堆顶删除最小值:" << endl;
    while (!minheap.isEmpty())
    {
        temp = minheap.RemoveMin();
        cout << temp << " ";
    }
    cout << endl;

    cout << "重建堆：" << endl;    //此处为依次插入建堆。
    for(i = 0; i < 8; i++)
    {
        minheap.Insert(Key[i]);
        cout<< Key[i] << " added." <<endl;
    }

    cout<< "删除给定下标(3)的元素:" <<endl;
    minheap.Remove(3,elem);
    cout<<  elem << " deleted." <<endl;

    cout<< "插入元素45:" <<endl;
    minheap.Insert(45);

    cout << "不断从堆顶删除最小值:" << endl;
    while (!minheap.isEmpty())
    {
        temp = minheap.RemoveMin();
        cout << temp << " ";
    }
    cout << endl;
}


void testHuffmanTree()
{
	int weight[] = {6,2,3,4};       //权值

	HuffmanTree<int> a(weight,4);   //图5.19 Huffman树
	cout<< "HuffmanTree is constructed. " << endl;

	cout<< "层次周游Huffman树：" << endl;
	a.LevelOrder(a.GetRoot());
	cout << endl;

	cout<< "中序周游：" << endl;
	a.InOrder(a.GetRoot());
	cout << endl;



	//a.DeleteTree(a.GetRoot());
	cout << "********";

}
