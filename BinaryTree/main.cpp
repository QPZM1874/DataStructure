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
    int Key[] = {19,8,35,65,40,3,7,45} ;    //ͼ��5.17��ʾ������

    cout << "�����ȶ��У�" << endl;    //�˴�Ϊ���β��뽨�ѡ�
    for(i = 0; i < 8; i++)
    {
        pq.Insert(Key[i]);
        cout<< Key[i] << " added." <<endl;
    }

    cout << "���ϴӶ���ɾ����Сֵ:" << endl;
    while (!pq.isEmpty())
    {
        temp = pq.RemoveMin();
        cout << temp << " ";
    }
    cout << endl;

    cout << "�ؽ����У�" << endl;    //�˴�Ϊ���β��뽨�ѡ�
    for(i = 0; i < 8; i++)
    {
        pq.Insert(Key[i]);
        cout<< Key[i] << " added." <<endl;
    }

    cout<< "ɾ�������±�(3)��Ԫ��:" <<endl;
    pq.Remove(3,elem);
    cout<<  elem << " deleted." <<endl;

    cout<< "����Ԫ��45:" <<endl;
   pq.Insert(45);

    cout << "���ϴӶ���ɾ����Сֵ:" << endl;
    while (!pq.isEmpty())
    {
        temp = pq.RemoveMin();
        cout << temp << " ";
    }
    cout << endl;
}
void testBinaryTree()
{
    //��һ����(��ͼ5.5��ʾ)
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

    //ǰ�����ζ�����
    cout << "Preorder sequence is: "<<endl;
    a.PreOrder(a.Root());				//�ݹ�
    cout << endl;
    cout << "Preorder sequence Without Recursion is: " <<endl;
    a.PreOrderWithoutRecursion(a.Root());//�ǵݹ�
    cout << endl;

    //�������ζ�����
    cout << "Inorder sequence is: "<<endl;
    a.InOrder(a.Root());			//�ݹ�
    cout << endl;
    cout << "Inorder sequence Without Recursion is: " <<endl;
    a.InOrderWithoutRecursion(a.Root());//�ǵݹ�
    cout << endl;

    //�������ζ�����
    cout << "Postorder sequence is: "<<endl;
    a.PostOrder(a.Root());			//�ݹ�
    cout << endl;
    cout << "Postorder sequence Without Recursion is: " <<endl;
    a.PostOrderWithoutRecursion(a.Root());//�ǵݹ�
    cout << endl;

    //root
    cout << "Root is: " << a.Root()->value() <<endl;

    //delete tree
    a.DeleteBinaryTree(a.Root());
    cout<<"Tree is deleted."<<endl;        //û�����⣬�����������е���
}

void testCreateBinaryTree()
{
    BinaryTree<char> bt;  // ��������


    // ����ǰ������
    char preList[] = {'A','B','D','*','*','E','G','*','*','*','C','*','F','H','*','*','I','*','*'};

    // �������ṩ���
    bt.createWithNodesInArray(preList,'*');
    cout << "ǰ�����ζ�����: "<<endl;
    bt.PreOrder(bt.Root());
    cout << endl;

    cout << "�������ζ�����: "<<endl;
    bt.InOrder(bt.Root());
    cout << endl;

    cout << "�������ζ�����: "<<endl;
    bt.PostOrder(bt.Root());
    cout << endl;

    // ����̨������
    bt.createWithNodesInputed();
    bt.createWithNodesInArray(preList,'*');
    cout << "ǰ�����ζ�����: "<<endl;
    bt.PreOrder(bt.Root());
    cout << endl;

    cout << "�������ζ�����: "<<endl;
    bt.InOrder(bt.Root());
    cout << endl;

    cout << "�������ζ�����: "<<endl;
    bt.PostOrder(bt.Root());
    cout << endl;
}



void testBinarySearchTree()
{
    const int N = 11;
    int K[N] = {50,19,35,55,20,5,100,52,88,53,92};        //��һ��ͼ5.11��ʾ����
    BinarySearchTree<int> aBST;
    BinaryTreeNode<int > *newpointer, *node1, *node2;

    for (int i = 0; i < N; i ++) // ѭ��������
    {
        newpointer = new BinaryTreeNode<int>();
        newpointer->setValue(K[i]);
        aBST.InsertNode(aBST.Root(), newpointer);      //���β�����

        if (K[i] == 52)                                 //��¼��ɾ������ָ��node1
        {
            node1 = newpointer;
        }
        if (K[i] == 55)                                 //��¼��ɾ������ָ��node2
            node2 = newpointer;
    }

    // �������
    cout << "�������ζ�����������" << endl;
    aBST.InOrder(aBST.Root());
    cout << endl;

    // ɾ���������ĸĽ��㷨
    cout << "ɾ�����52, 55." << endl;
    aBST.DeleteNodeEx(node1);
    aBST.DeleteNodeEx(node2);

    // �����ڵ�
    cout << "ɾ�����֮���������ζ�����������" << endl;
    aBST.InOrder(aBST.Root());
    cout << endl;
}


void testMinHeap()
{
    MinHeap<int> minheap(8);
    int i;
    int temp,elem;
    int Key[] = {19,8,35,65,40,3,7,45} ;    //ͼ��5.17��ʾ������

    cout << "���ѣ�" << endl;    //�˴�Ϊ���β��뽨�ѡ�
    for(i = 0; i < 8; i++)
    {
        minheap.Insert(Key[i]);
        cout<< Key[i] << " added." <<endl;
    }

    cout << "���ϴӶѶ�ɾ����Сֵ:" << endl;
    while (!minheap.isEmpty())
    {
        temp = minheap.RemoveMin();
        cout << temp << " ";
    }
    cout << endl;

    cout << "�ؽ��ѣ�" << endl;    //�˴�Ϊ���β��뽨�ѡ�
    for(i = 0; i < 8; i++)
    {
        minheap.Insert(Key[i]);
        cout<< Key[i] << " added." <<endl;
    }

    cout<< "ɾ�������±�(3)��Ԫ��:" <<endl;
    minheap.Remove(3,elem);
    cout<<  elem << " deleted." <<endl;

    cout<< "����Ԫ��45:" <<endl;
    minheap.Insert(45);

    cout << "���ϴӶѶ�ɾ����Сֵ:" << endl;
    while (!minheap.isEmpty())
    {
        temp = minheap.RemoveMin();
        cout << temp << " ";
    }
    cout << endl;
}


void testHuffmanTree()
{
	int weight[] = {6,2,3,4};       //Ȩֵ

	HuffmanTree<int> a(weight,4);   //ͼ5.19 Huffman��
	cout<< "HuffmanTree is constructed. " << endl;

	cout<< "�������Huffman����" << endl;
	a.LevelOrder(a.GetRoot());
	cout << endl;

	cout<< "�������Σ�" << endl;
	a.InOrder(a.GetRoot());
	cout << endl;



	//a.DeleteTree(a.GetRoot());
	cout << "********";

}
