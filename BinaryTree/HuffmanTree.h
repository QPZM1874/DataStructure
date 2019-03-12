// -------- HuffmanTree.h

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "MinHeap.h"
#include "lnkQueue.h"

template <class T> class HuffmanTree;

template <class T>
class HuffmanTreeNode
{
    friend class HuffmanTree<T>;
private:
    T info;
    HuffmanTreeNode<T> *parent;
    HuffmanTreeNode<T> *left;
    HuffmanTreeNode<T> *right;
public:
    HuffmanTreeNode() {};
    HuffmanTreeNode<T> *leftchild()
    {
        return left;
    }
    HuffmanTreeNode<T> *rightchild()
    {
        return right;
    }
    bool operator > (HuffmanTreeNode<T> &HN)
    {
        return info > HN.info;
    } // ע��Ҫ���������
    bool operator < (HuffmanTreeNode<T> &HN)
    {
        return info < HN.info;
    };
    bool operator == (HuffmanTreeNode<T> &HN)
    {
        return info == HN.info;
    };
};


template <class T>
class HuffmanTree
{
private:
    HuffmanTreeNode<T>* root;			//Huffman��������

    //��ht1��ht2Ϊ����Huffman�����ϲ���һ����parentΪ���Ķ�����
    void MergeTree ( HuffmanTreeNode<T> &ht1, HuffmanTreeNode<T> &ht2,  HuffmanTreeNode<T>* parent);

    void DeleteTree(HuffmanTreeNode<T> * & root); //ɾ��Huffman����������
public:
    //����Huffman����weight�Ǵ洢Ȩֵ�����飬n�����鳤��
    HuffmanTree(T weight[], int n);
    virtual ~HuffmanTree()
    {
        DeleteTree(root);
    } 	//��������

    HuffmanTreeNode<T> * & GetRoot()
    {
        return root;
    }

    void InOrder(HuffmanTreeNode<T> * root);          //��������

    void LevelOrder(HuffmanTreeNode<T> * root);       //�������
};

template<class T>
HuffmanTree<T>::HuffmanTree(T weight[], int n)
{
    MinHeap< HuffmanTreeNode<T> > heap(n);		//������Сֵ��
    HuffmanTreeNode<T> *parent, firstchild, secondchild;
    HuffmanTreeNode<T>* NodeList = new HuffmanTreeNode<T>[n];
    for(int i = 0; i < n; i++)       				//��ʼ��
    {
        NodeList[i].info = weight[i];
        NodeList[i].parent = NodeList[i].left = NodeList[i].right = NULL;
        heap.Insert(NodeList[i]);				//��������Ԫ��
    }

    for(int i = 0; i < n-1; i++)                  		//ͨ��n-1�κϲ�����Huffman��
    {
        parent = new HuffmanTreeNode<T>;
        firstchild = heap.RemoveMin();				//ѡ��Ȩֵ��С�Ľ��
        secondchild = heap.RemoveMin();				//ѡ��Ȩֵ��С�Ľ��
        MergeTree(firstchild,secondchild,parent);	//�ϲ�Ȩֵ��С��������
        heap.Insert(*parent);					//��parent���뵽����ȥ
        root = parent;							//���������
    }
    delete []NodeList;
}

template <class T>
void HuffmanTree<T>::DeleteTree(HuffmanTreeNode<T> * & root)
{
    if (root)
    {
        DeleteTree(root->left);
        DeleteTree(root->right);
        delete root;
        root = NULL;
    }
}


template <class T>
void HuffmanTree<T>::InOrder(HuffmanTreeNode<T> *root)    //��������
{
    if (root)
    {
        InOrder(root->left);
        cout << root->info << " ";
        InOrder(root->right);
    }
}

template <class T>
void HuffmanTree<T>::LevelOrder(HuffmanTreeNode<T> * root)  //�������
{
    if (root == NULL) return;
    //������������0���⣬ÿ�������ڵ㣬
    //�����м���NULLָ����һ����������ڻ��У�
    //ʹ�õ�3��ʵ�ֵĶ���
    lnkQueue< HuffmanTreeNode<T> * > ptrQueue;
    HuffmanTreeNode<T> * parent, * child;
    ptrQueue.enQueue(root);
    ptrQueue.enQueue(NULL);
    while (!ptrQueue.isEmpty())
    {
        ptrQueue.deQueue(parent);
        if (parent == NULL)
        {
            cout << endl;
            continue;
        }
        cout << parent->info << "  ";

        child = parent->leftchild();
        if ( child ) ptrQueue.enQueue(child);
        child = parent->rightchild();
        if ( child )
        {
            ptrQueue.enQueue(child);
            ptrQueue.enQueue(NULL);
        }
    }
}


template <class T>
void HuffmanTree<T>::MergeTree(HuffmanTreeNode<T> &ht1, HuffmanTreeNode<T> &ht2, HuffmanTreeNode<T> *parent)
{
    HuffmanTreeNode<T> *l = new HuffmanTreeNode<T>();
    HuffmanTreeNode<T> *r = new HuffmanTreeNode<T>();

    *l = ht1; // ����дΪl = &ht1��ע���ַ���ã����ٵ����¿ռ䣬����Ӧ�ÿ������캯����ֻ����Щ�鷳
    *r = ht2;

    parent->parent = NULL;
    parent->left = l;
    parent->right = r;
    parent->info = ht1.info + ht2.info;
    ht1.parent = ht2.parent = parent; // ָ�򸸽ڵ�
}

#endif // HUFFMANTREE_H
