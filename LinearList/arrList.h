#ifndef ARRLIST_H_INCLUDE
#define ARRLIST_H_INCLUDE

#include <iostream>
#include <string>
#include "myList.h"

using namespace std;

// ��Ԫ�ص�����ΪT���ö�̬���������洢Ԫ�أ�maxSize������󳤶ȡ�
// �����ڱ�������ģ���֧�֣���ģ�����ʵ�ַ���ͷ�ļ���

template  <class T>  			    // �ٶ�˳����Ԫ������ΪT
class arrList : public List<T>   	// ˳�������
{
private:    					// ���Ա��ȡֵ���ͺ�ȡֵ�ռ�
    int  maxSize;            	// ˽�б�����˳���ʵ������󳤶�
    int  curLen; 		    	// ˽�б�����˳���ʵ���ĵ�ǰ����
    int  position;				// ˽�б�������ǰ����λ�á�������������
    T  * aList ;            	// ˽�б�����ָ��洢�洢�ռ�
public: 						// ˳�������㼯
    arrList(const int size)    		// ����һ���µ�˳�������Ϊ��ʵ������󳤶�
    {
        maxSize = size;
        aList = new T[maxSize];
        curLen = position = 0;
    }
    ~arrList()  					// �������������������ñ�ʵ��
    {
        delete [] aList;
    }
    // �̳��Ի���ķ���
    virtual void clear()        	// ��˳���洢�������������Ϊ�ձ�
    {
        curLen = position = 0;
    }

    virtual bool isEmpty()
    {
        return (curLen == 0);
    }

    virtual bool ins(int pos, const T & value);
    virtual bool del(int pos);
    virtual bool getPos(int & pos, const T & value);

    virtual bool app(const T & value)
    {
        return false;
    }
    virtual bool getValue(int pos, T & value)
    {
        return false;
    }
    virtual bool setValue(int pos, const T & value)
    {
        return false;
    }

    // �����ķ���
    int length()            		// ���ش�˳���ĵ�ǰʵ�ʳ���
    {
        return curLen;
    }
    void print();                   // ��ӡ���Ա�
};

template <class T>  			      		// �ٶ�˳����Ԫ������ΪT
bool arrList<T> :: ins(int p, const T & value)
{
    int i;
    if (curLen >= maxSize)    		  		// ���˳����Ƿ����
    {
        cout << "The list is overflow!"<<endl;
        return false;
    }
    if (p < 0 || p > curLen)   		  		// ������λ���Ƿ�Ϸ�
    {
        cout << "Insertion is illegal!\n" <<endl;
        return false;
    }
    for (i = curLen; i > p; i--)
        aList[i] = aList[i-1];   	 	// �ӱ�βcurLen-1�������ƶ�ֱ��p
    aList[p] = value;          		 	// λ��p��������Ԫ��
    curLen++;               		 	// ���ʵ�ʳ�����1
    return true;
}

template <class T>  			    // �ٶ�˳����Ԫ������ΪT
bool arrList<T> :: del(int p)
{
    int i;
    if (curLen <= 0 )    				// ���˳����Ƿ�Ϊ��
    {
        cout << " No element to delete!\n"<<endl;
        return false ;
    }
    if (p < 0 || p > curLen-1)   			// ���ɾ��λ���Ƿ�Ϸ�
    {
        cout << "deletion is illegal!\n"<<endl;
        return false ;
    }
    for (i = p; i < curLen-1; i++)
        aList[i] = aList[i+1];   	 	// ��λ��p��ʼÿ��Ԫ������ֱ��curLen,
    curLen--;               			// ���ʵ�ʳ��ȼ�1
    return true;
}

template <class T>  					// �ٶ�˳����Ԫ������ΪT
bool arrList<T> :: getPos(int & p, const T & value)
{
    int i;     						// Ԫ���±�
    for (i = 0; i < curLen; i++)   				// ���αȽ�
    {
        if (value == aList[i])		// �±�Ϊi��Ԫ����value���
        {
            p = i;                  // ͨ�����������±�i
            return true;
        }
    }
    return false;						// ˳�����û��ֵΪvalue��Ԫ��
}

template <class T>  			    // �ٶ�˳����Ԫ������ΪT
void arrList<T> :: print()
{
    for (int i = 0; i < curLen; i++)
        cout << aList[i] << "  ";
    cout << endl;  	 		// ��λ��p��ʼÿ��Ԫ������ֱ��curLen,
}

#endif // ARRLIST_H_INCLUDE
