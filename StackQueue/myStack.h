// abstract data type for stack

#ifndef STACK_H_INLUCDE
#define STACK_H_INLUCDE

/*
  1��ջ�д洢�Ķ���ΪT��Ķ���
  2����Щ�������ܲ�����ɣ�����bool�����Ƿ�ɹ���
  3��Stack��ֻ�涨ջ�ķ���(�ӿ�)����δȷ���洢�ṹ���ǳ����ࡣ
  4��T�Ķ�����ܽϴ����ô��ݱ������ֵ�ĸ��ƹ��죬������ܡ�
*/

template <class T> 					// ջ��Ԫ������Ϊ T
class Stack {
public: 	            			// ջ�����㼯
	virtual void clear() = 0;	   			    // ��Ϊ��ջ
   	virtual bool push(const T & item) = 0; 		// item��ջ���ɹ��򷵻��棬���򷵻ؼ�
 	virtual bool pop(T & item) = 0;				// ����ջ�����ݲ��������ɹ������棬���򷵻ؼ�,
 	virtual bool getTop(T & item) = 0;	  		// ����ջ�����ݵ��������ɹ������棬���򷵻ؼ�,
   	virtual bool isEmpty() = 0; 	   			// ��ջ�ѿշ�����
   	virtual bool isFull() = 0;        			// ��ջ����������
};

#endif // STACK_H_INLUCDE



