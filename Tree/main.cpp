#include <iostream>
using namespace std;
#include "Tree.h"
#include "DualtagTree.h"
#include "ParTree.h"

void testTree();  //测试长子-兄弟表示的树
void Traverse(Tree<char> *tree);  //测试长子-兄弟表示的树遍历

void testUnionFindSet(); //测试父指针表示树实现的并查集


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
    //建树
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


    //显示树的结构
    cout << "      A           X        \n";
    cout << "   /  |  \\      /   \\     \n";
    cout << "  B   C   D    Y     Z     \n";
    cout << "    /   \\                  \n";
    cout << "   E     F                  \n";
    cout << "\n";

    //周游树
    Traverse(&aTree);

    //e结点插入第一个孩子G
    cout << "e结点插入第一个孩子G的结果：\n";
    TreeNode<char> *g = new TreeNode<char>('G');
    e->InsertFirst(g);
    //周游树
    Traverse(&aTree);

    //e结点以第一个兄弟的身份插入H
    cout << "e结点以第一个兄弟的身份插入H的结果:\n";
    TreeNode<char> *h = new TreeNode<char>('H');
    e->InsertNext(h);
    //周游树
    Traverse(&aTree);

    //获得C的父结点
    cout << "获得C的父结点： ";
    aTree.Visit(aTree.Parent(c)->Value());
    cout << endl;

    //获得H的上一个兄弟结点

    cout << "获得H的上一个兄弟结点： ";
    aTree.Visit(aTree.PrevSibling(h)->Value());
    cout << endl;

    //删除根为E的子树
    cout << "删除E子树：" << endl;
    aTree.DeleteSubTree(e);
    Traverse(&aTree);

    //删除根为C的子树
    cout << "删除C子树：" << endl;
    aTree.DeleteSubTree(c);
    Traverse(&aTree);
}


void Traverse(Tree<char> *tree)
{
    cout << "FirstRoot traverse:  ";
    tree->RootFirstTraverse(tree->getRoot()); // 先根深度优先周游
    cout << endl;

    cout << "LastRoot  traverse:  ";
    tree->RootLastTraverse(tree->getRoot()); // 后根深度
    cout << endl;

    cout << "Width traverse    :  ";
    tree->WidthTraverse(tree->getRoot()); // 广度遍历
    cout << endl << endl;
}

//----------------------------------------------------------

// 测试并查集相关的数据集函数
const int NUM = 10;       // 树结点个数
char strInfo[NUM] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};  //结点信息数组

// 函数功能：根据字符信息获得数字在数组中的位置下标
int GetNum(char ch)
{
    for (int i = 0; i < NUM; i ++)
        if (ch == strInfo[i]) return i;
    return -1;
}

// 函数功能：显示数据在父指针表示法中的父结点下标
void Display(ParTree<char> &aParTree)
{
    for (int i = 0; i < N; i ++)
    {
        if (aParTree.array[i].getParent() == NULL)            //如果是没有父结点就用*表示
            cout << "*" << " ";
        else
        {
            char ch = aParTree.array[i].getParent()->getValue(); //如果有父结点就打印数组中的父结点的下标
            cout << GetNum(ch) << " ";
        }
    }
    cout << endl;
}

#define PATHCOMPRESSION   1  // 0-不带压缩, 1-带压缩

void testUnionFindSet() //测试父指针表示树实现的并查集
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
    Display(aParTree);                             //显示数据在父指针表示法中的父结点下标

    cout << "\nUnion: (A,D),(I,H)\n";
    aParTree.Union(GetNum('A'), GetNum('D'));
    aParTree.Union(GetNum('I'), GetNum('H'));
    Display(aParTree);								//显示数据在父指针表示法中的父结点下标

#if !PATHCOMPRESSION
    // 0.不带压缩
    cout << "\nUnion: (F,J)\n" ;
    aParTree.Union(GetNum('F'), GetNum('J'));
    Display(aParTree);								//显示数据在父指针表示法中的父结点下标
    cout << "Union: (D,J)\n";
    aParTree.Union(GetNum('D'), GetNum('J'));
    Display(aParTree);								//显示数据在父指针表示法中的父结点下标
#else
    // 1.带压缩
    cout << "\nUnion: (F,J)\n";
    aParTree.UnionPC(GetNum('F'), GetNum('J'));
    Display(aParTree);								//显示数据在父指针表示法中的父结点下标
    cout << "\nUnion: (D,J)\n";
    aParTree.UnionPC(GetNum('D'), GetNum('J'));
    Display(aParTree);								//显示数据在父指针表示法中的父结点下标
#endif

    if (aParTree.Different(GetNum('D'), GetNum('E')))
        cout << "D and E are in different sets!!!" << endl;
    else
        cout << "D and E are in a common set!!!" << endl;
    cout << endl;
}
