// abstract data type for queue

#ifndef QUEUE_H_INLUCDE
#define QUEUE_H_INLUCDE

/*
  2、队列中存储的对象为T类的对象。
  2、有些操作可能不能完成，返回bool表明是否成功。
  3、Queue类只规定队列的方法(接口)，尚未确定存储结构，是抽象类。
  4、T的对象可能较大，引用传递避免参数值的复制构造，提高性能。
*/
template <class T>
class Queue
{
public:
    virtual void clear() = 0;	// 变为空队列
    virtual bool enQueue(const T & item) = 0; 	// item入队，成功则返回真否则返回假
    virtual bool deQueue(T & item) = 0;     	// 返回队头元素并从队列中删除，成功则返回真
    virtual bool getFront(T & item) = 0;	    // 返回队头元素，但不删除，成功则返回真
    virtual bool isEmpty() = 0; 				// 返回真，若队列已空
    virtual bool isFull() = 0;       			// 返回真，若队列已满
    virtual void print() = 0;
};

#endif




