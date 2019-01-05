#ifndef ARRLIST_H_INCLUDE
#define ARRLIST_H_INCLUDE

#include <iostream>
#include <string>
#include "myList.h"

using namespace std;

// 设元素的类型为T，用动态分配的数组存储元素，maxSize是其最大长度。
// 受限于编译器对模板的支持，将模板类的实现放在头文件中

template  <class T>  			    // 假定顺序表的元素类型为T
class arrList : public List<T>   	// 顺序表，向量
{
private:    					// 线性表的取值类型和取值空间
    int  maxSize;            	// 私有变量，顺序表实例的最大长度
    int  curLen; 		    	// 私有变量，顺序表实例的当前长度
    int  position;				// 私有变量，当前处理位置。辅助遍历操作
    T  * aList ;            	// 私有变量，指向存储存储空间
public: 						// 顺序表的运算集
    arrList(const int size)    		// 创建一个新的顺序表，参数为表实例的最大长度
    {
        maxSize = size;
        aList = new T[maxSize];
        curLen = position = 0;
    }
    ~arrList()  					// 析构函数，用于消除该表实例
    {
        delete [] aList;
    }
    // 继承自基类的方法
    virtual void clear()        	// 将顺序表存储的内容清除，成为空表
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

    // 新增的方法
    int length()            		// 返回此顺序表的当前实际长度
    {
        return curLen;
    }
    void print();                   // 打印线性表
};

template <class T>  			      		// 假定顺序表的元素类型为T
bool arrList<T> :: ins(int p, const T & value)
{
    int i;
    if (curLen >= maxSize)    		  		// 检查顺序表是否溢出
    {
        cout << "The list is overflow!"<<endl;
        return false;
    }
    if (p < 0 || p > curLen)   		  		// 检查插入位置是否合法
    {
        cout << "Insertion is illegal!\n" <<endl;
        return false;
    }
    for (i = curLen; i > p; i--)
        aList[i] = aList[i-1];   	 	// 从表尾curLen-1起往右移动直到p
    aList[p] = value;          		 	// 位置p处插入新元素
    curLen++;               		 	// 表的实际长度增1
    return true;
}

template <class T>  			    // 假定顺序表的元素类型为T
bool arrList<T> :: del(int p)
{
    int i;
    if (curLen <= 0 )    				// 检查顺序表是否为空
    {
        cout << " No element to delete!\n"<<endl;
        return false ;
    }
    if (p < 0 || p > curLen-1)   			// 检查删除位置是否合法
    {
        cout << "deletion is illegal!\n"<<endl;
        return false ;
    }
    for (i = p; i < curLen-1; i++)
        aList[i] = aList[i+1];   	 	// 从位置p开始每个元素左移直到curLen,
    curLen--;               			// 表的实际长度减1
    return true;
}

template <class T>  					// 假定顺序表的元素类型为T
bool arrList<T> :: getPos(int & p, const T & value)
{
    int i;     						// 元素下标
    for (i = 0; i < curLen; i++)   				// 依次比较
    {
        if (value == aList[i])		// 下标为i的元素与value相等
        {
            p = i;                  // 通过参数返回下标i
            return true;
        }
    }
    return false;						// 顺序表中没有值为value的元素
}

template <class T>  			    // 假定顺序表的元素类型为T
void arrList<T> :: print()
{
    for (int i = 0; i < curLen; i++)
        cout << aList[i] << "  ";
    cout << endl;  	 		// 从位置p开始每个元素左移直到curLen,
}

#endif // ARRLIST_H_INCLUDE
