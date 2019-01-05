// ˫����ȸ��������б�ʾ��������-�ֵܱ�ʾ��ת����
// ˫��ǲ���������б�ʾ��������-�ֵܱ�ʾ��ת��
#ifndef DUALTAGTREE_H
#define DUALTAGTREE_H

#include <iostream>
#include <stack>
#include "Tree.h"

using namespace std;

// ��"˫���"��˳��洢�����
template <class T>
class DualTagTreeNode
{
public:              //����Ϊ�˼�
    T info;          //�������Ϣ
    int ltag;		 //����
    int rtag;        //�ұ��

    DualTagTreeNode(){};               //���캯��
    virtual ~DualTagTreeNode(){};      //��������
};

// ��ɭ�ֵ�˫����ȸ����д�����Ӧ�ĳ���-�ֵܶ�����
template <class T>
void createTreeWithTagedRootFirstSquence(DualTagTreeNode<T> *nodeArray, int count, Tree<T> & aTree)
{
    using std::stack;  //ʹ��STL�е�stack
    stack< TreeNode<T>* > aStack;

    aTree.DeleteSubTree(aTree.getRoot());  // ��������

    //���������
    TreeNode<T> * pointer = new TreeNode<T>;
    aTree.getRoot() = pointer;
    //����һ�����
    for(int i = 0; i < count-1; i++)
    {
        pointer->setValue(nodeArray[i].info);
        if(nodeArray[i].rtag == 0)
            aStack.push(pointer);						//�����ѹջ
        else
            pointer->setSibling(NULL);					//���ֵ���Ϊ��
        TreeNode<T>* temppointer = new TreeNode<T>;
        if(nodeArray[i].ltag == 0)
            pointer->setChild(temppointer);
        else
        {
            pointer->setChild(NULL);					//������Ϊ��
            pointer = aStack.top();
            aStack.pop();
            pointer->setSibling(temppointer);
        }
        pointer = temppointer;
    }
    //�������һ�����
    pointer->setValue(nodeArray[count-1].info);
    pointer->setChild(NULL);
    pointer->setSibling(NULL);
}


// ��ɭ�ֵ�˫��ǲ�����д�����Ӧ�ĳ���-�ֵܶ�����
template <class T>
void createTreeWithTagedWidthFirstSquence(DualTagTreeNode<T> *nodeArray, int count, Tree<T> & aTree)
  {
	//�ɴ�˫���λ�Ĳ�δ����ʾ�����������ֵܷ�ʽ��ʾ����
	using std::queue;          //ʹ��STL����
	queue<TreeNode<T>*> aQueue;
	//׼�����������
	TreeNode<T>* pointer=new TreeNode<T>;
    aTree.getRoot() = pointer;
	//����һ�����
	for(int i=0;i<count-1;i++) {
		pointer->setValue(nodeArray[i].info);
		if(nodeArray[i].ltag==0)
			aQueue.push(pointer);					   //��������
		else
			pointer->setChild(NULL);				   //������Ϊ��
		TreeNode<T>* temppointer=new TreeNode<T>;
		if(nodeArray[i].rtag == 0)
			pointer->setSibling(temppointer);
		else {
			pointer->setSibling(NULL);					//���ֵ���Ϊ��
			pointer=aQueue.front();                     //ȡ�����׽��ָ��
			aQueue.pop();                            //����Ԫ�س�����
			pointer->setChild(temppointer);
		}
		pointer=temppointer;
	}
	//�������һ�����
	pointer->setValue(nodeArray[count-1].info);
	pointer->setChild(NULL);
	pointer->setSibling(NULL);
}


#define N 10  //�������

// �������ܣ���ʾʾ��ɭ�ֽṹ
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

// �������ܣ���ʾɭ�ֽṹ�Ĵ�˫����ȸ������ʾ
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

// �������ܣ���ʾɭ�ֽṹ�Ĵ�˫��ǲ��˳���ʾ
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
    // ��ʾɭ�ֽṹ
    DisplayTree();

    // ʾ��ɭ�ֽ����Ϣ
    char strInfo[N] = {'A', 'B', 'C', 'E', 'F', 'D', 'G', 'H', 'J', 'I'};
    int nRtag[N] = {0, 0, 0, 0, 1, 1, 1, 0, 1, 1};
    int nLtag[N] = {0, 1, 0, 1, 1, 1, 0, 0, 1, 1};

    // ����˫����ȸ�˳��������
    DualTagTreeNode<char> *nodeArray = new DualTagTreeNode<char>[N];
    for (int i = 0; i < N; i ++)                   //���ô�˫���λ���ȸ���������
    {
        nodeArray[i].info = strInfo[i];
        nodeArray[i].ltag = nLtag[i];
        nodeArray[i].rtag = nRtag[i];
    }
    displayRootFirstNode<char>(nodeArray, N);

    Tree<char> aTree;  // ��������-�ֵܱ�ʾ�Ŀ���
    createTreeWithTagedRootFirstSquence<char>(nodeArray, N, aTree);
    delete []nodeArray;

    cout << endl;
    cout << "�ȸ����Σ�";
    aTree.RootFirstTraverse(aTree.getRoot());
    cout << endl;

    cout << "������Σ�";
    aTree.RootLastTraverse(aTree.getRoot());
    cout << endl;

    cout << "������Σ�";
    aTree.WidthTraverse(aTree.getRoot());
    cout << endl;
}


void testWidthFirstSequenceTree()
{
    // ��ʾɭ�ֽṹ
    DisplayTree();

    // ʾ��ɭ�ֽ����Ϣ
    char strInfo[N] = {'A', 'G', 'B', 'C', 'D', 'H', 'I', 'E', 'F', 'J'};
	int nRtag[N] = {0, 1, 0, 0, 1, 0, 1, 0, 1, 1};
	int nLtag[N] = {0, 0, 1, 0, 1, 0, 1, 1, 1, 1};

    // ����˫��ǲ��˳��������
    DualTagTreeNode<char> *nodeArray = new DualTagTreeNode<char>[N];
    for (int i = 0; i < N; i ++)                   //���ô�˫���λ���ȸ���������
    {
        nodeArray[i].info = strInfo[i];
        nodeArray[i].rtag = nRtag[i];
        nodeArray[i].ltag = nLtag[i];
    }
    displayWidthFirstNode<char>(nodeArray, N);

    Tree<char> aTree;  // ��������-�ֵܱ�ʾ�Ŀ���
    createTreeWithTagedWidthFirstSquence<char>(nodeArray, N, aTree);
    delete []nodeArray;

    cout << endl;
    cout << "�ȸ����Σ�";
    aTree.RootFirstTraverse(aTree.getRoot());
    cout << endl;

    cout << "������Σ�";
    aTree.RootLastTraverse(aTree.getRoot());
    cout << endl;

    cout << "������Σ�";
    aTree.WidthTraverse(aTree.getRoot());
    cout << endl;
}
#endif // DUALTAGTREE_H
