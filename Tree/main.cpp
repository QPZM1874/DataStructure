#include <iostream>
using namespace std;
#include "Tree.h"
#include "DualtagTree.h"
#include "ParTree.h"

void testTree();  //���Գ���-�ֵܱ�ʾ����
void Traverse(Tree<char> *tree);  //���Գ���-�ֵܱ�ʾ��������

void testUnionFindSet(); //���Ը�ָ���ʾ��ʵ�ֵĲ��鼯


int main()
{

    testTree();

    //testRootFirstSequenceTree();

    //testWidthFirstSequenceTree();

    //testUnionFindSet();

    return 0;
}


void testTree()
{
    //����
    Tree<char> aTree;
    aTree.CreateRoot('A');
    TreeNode<char> *f = new TreeNode<char>('F');
    TreeNode<char> *e = new TreeNode<char>('E');
    TreeNode<char> *d = new TreeNode<char>('D');
    TreeNode<char> *c = new TreeNode<char>('C');
    TreeNode<char> *b = new TreeNode<char>('B');
    e->setSibling(f);
    c->setSibling(d);
    c->setChild(e);
    b->setSibling(c);
    aTree.getRoot()->setChild(b);

    TreeNode<char> *x = new TreeNode<char>('X');
    TreeNode<char> *y = new TreeNode<char>('Y');
    TreeNode<char> *z = new TreeNode<char>('Z');
    aTree.getRoot()->setSibling(x);
    x->setChild(y);
    y->setSibling(z);


    //��ʾ���Ľṹ
    cout << "      A           X        \n";
    cout << "   /  |  \\      /   \\     \n";
    cout << "  B   C   D    Y     Z     \n";
    cout << "    /   \\                  \n";
    cout << "   E     F                  \n";
    cout << "\n";

    //������
    Traverse(&aTree);

    //e�������һ������G
    cout << "e�������һ������G�Ľ����\n";
    TreeNode<char> *g = new TreeNode<char>('G');
    e->InsertFirst(g);
    //������
    Traverse(&aTree);

    //e����Ե�һ���ֵܵ���ݲ���H
    cout << "e����Ե�һ���ֵܵ���ݲ���H�Ľ��:\n";
    TreeNode<char> *h = new TreeNode<char>('H');
    e->InsertNext(h);
    //������
    Traverse(&aTree);

    //���C�ĸ����
    cout << "���C�ĸ���㣺 ";
    aTree.Visit(aTree.Parent(c)->Value());
    cout << endl;

    //���H����һ���ֵܽ��

    cout << "���H����һ���ֵܽ�㣺 ";
    aTree.Visit(aTree.PrevSibling(h)->Value());
    cout << endl;

    //ɾ����ΪE������
    cout << "ɾ��E������" << endl;
    aTree.DeleteSubTree(e);
    Traverse(&aTree);

    //ɾ����ΪC������
    cout << "ɾ��C������" << endl;
    aTree.DeleteSubTree(c);
    Traverse(&aTree);
}


void Traverse(Tree<char> *tree)
{
    cout << "FirstRoot traverse:  ";
    tree->RootFirstTraverse(tree->getRoot()); // �ȸ������������
    cout << endl;

    cout << "LastRoot  traverse:  ";
    tree->RootLastTraverse(tree->getRoot()); // ������
    cout << endl;

    cout << "Width traverse    :  ";
    tree->WidthTraverse(tree->getRoot()); // ��ȱ���
    cout << endl << endl;
}

//----------------------------------------------------------

// ���Բ��鼯��ص����ݼ�����
const int NUM = 10;       // ��������
char strInfo[NUM] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};  //�����Ϣ����

// �������ܣ������ַ���Ϣ��������������е�λ���±�
int GetNum(char ch)
{
    for (int i = 0; i < NUM; i ++)
        if (ch == strInfo[i]) return i;
    return -1;
}

// �������ܣ���ʾ�����ڸ�ָ���ʾ���еĸ�����±�
void Display(ParTree<char> &aParTree)
{
    for (int i = 0; i < N; i ++)
    {
        if (aParTree.array[i].getParent() == NULL)            //�����û�и�������*��ʾ
            cout << "*" << " ";
        else
        {
            char ch = aParTree.array[i].getParent()->getValue(); //����и����ʹ�ӡ�����еĸ������±�
            cout << GetNum(ch) << " ";
        }
    }
    cout << endl;
}

#define PATHCOMPRESSION   1  // 0-����ѹ��, 1-��ѹ��

void testUnionFindSet() //���Ը�ָ���ʾ��ʵ�ֵĲ��鼯
{

    for (int i = 0; i < N; i++) cout << i << " ";
    cout << endl;
    for (int i = 0; i < N; i++) cout << strInfo[i] << " ";
    cout << endl;


    ParTree<char> aParTree(N);
    for (int i = 0; i < N; i++) aParTree.array[i].setValue(strInfo[i]);

    cout << "* means that the node has no parents!\n" ;
    cout << endl;

    cout << "Union: (A,B),(C,D),(E,F),(G,H),(I,J)\n" ;
    aParTree.Union(GetNum('A'), GetNum('B'));
    aParTree.Union(GetNum('C'), GetNum('D'));
    aParTree.Union(GetNum('E'), GetNum('F'));
    aParTree.Union(GetNum('G'), GetNum('H'));
    aParTree.Union(GetNum('I'), GetNum('J'));
    Display(aParTree);                             //��ʾ�����ڸ�ָ���ʾ���еĸ�����±�

    cout << "\nUnion: (A,D),(I,H)\n";
    aParTree.Union(GetNum('A'), GetNum('D'));
    aParTree.Union(GetNum('I'), GetNum('H'));
    Display(aParTree);								//��ʾ�����ڸ�ָ���ʾ���еĸ�����±�

#if !PATHCOMPRESSION
    // 0.����ѹ��
    cout << "\nUnion: (F,J)\n" ;
    aParTree.Union(GetNum('F'), GetNum('J'));
    Display(aParTree);								//��ʾ�����ڸ�ָ���ʾ���еĸ�����±�
    cout << "Union: (D,J)\n";
    aParTree.Union(GetNum('D'), GetNum('J'));
    Display(aParTree);								//��ʾ�����ڸ�ָ���ʾ���еĸ�����±�
#else
    // 1.��ѹ��
    cout << "\nUnion: (F,J)\n";
    aParTree.UnionPC(GetNum('F'), GetNum('J'));
    Display(aParTree);								//��ʾ�����ڸ�ָ���ʾ���еĸ�����±�
    cout << "\nUnion: (D,J)\n";
    aParTree.UnionPC(GetNum('D'), GetNum('J'));
    Display(aParTree);								//��ʾ�����ڸ�ָ���ʾ���еĸ�����±�
#endif

    if (aParTree.Different(GetNum('D'), GetNum('E')))
        cout << "D and E are in different sets!!!" << endl;
    else
        cout << "D and E are in a common set!!!" << endl;
    cout << endl;
}
