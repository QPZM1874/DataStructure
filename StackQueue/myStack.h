// abstract data type for stack

#ifndef STACK_H_INLUCDE
#define STACK_H_INLUCDE

/*
  1、栈中存储的对象为T类的对象。
  2、有些操作可能不能完成，返回bool表明是否成功。
  3、Stack类只规定栈的方法(接口)，尚未确定存储结构，是抽象类。
  4、T的对象可能较大，引用传递避免参数值的复制构造，提高性能。
*/

template <class T> 					// 栈的元素类型为 T
class Stack {
public: 	            			// 栈的运算集
	virtual void clear() = 0;	   			    // 变为空栈
   	virtual bool push(const T & item) = 0; 		// item入栈，成功则返回真，否则返回假
 	virtual bool pop(T & item) = 0;				// 返回栈顶内容并弹出，成功返回真，否则返回假,
 	virtual bool getTop(T & item) = 0;	  		// 返回栈顶内容但不弹出成功返回真，否则返回假,
   	virtual bool isEmpty() = 0; 	   			// 若栈已空返回真
   	virtual bool isFull() = 0;        			// 若栈已满返回真
};

#endif // STACK_H_INLUCDE



