
// abstract data type for List
#ifndef LIST_H_INCLUDE
#define LIST_H_INCLUDE

/*
  1、线性表中存储的对象为T类的对象。
  2、有些操作可能不能完成，返回bool表明是否成功。
  3、List类只规定表类的方法(接口)，尚未确定存储结构，是抽象类。
  4、T的对象可能较大，引用传递避免参数值的复制构造，提高性能。
*/

template <class T>
class List
{
    virtual void clear() = 0; 				 	// 置空线性表
    virtual bool isEmpty() = 0;				 	// 线性表为空时，返回True
    virtual bool app(const T & value) = 0;	// 在表尾添加一个元素value，表的长度增1
    virtual bool ins(int pos, const T & value) = 0;	 	// 在位置pos上插入一个元素value，表的长度增1
    virtual bool del(int pos) = 0; 			 	        // 删除位置pos上的元素，表的长度减 1
    virtual bool getValue(int pos, T & value) = 0;		    // 返回位置pos的元素值
    virtual bool setValue(int pos, const T & value) = 0;	// 用value修改位置pos的元素值
    virtual bool getPos(int & pos, const T & value) = 0;    // 将表中值为value的元素的位置返回到pos中
};


#endif // LIST_H_INCLUDE

