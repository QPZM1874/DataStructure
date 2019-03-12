// abstract data type for queue

#ifndef QUEUE_H_INLUCDE
#define QUEUE_H_INLUCDE

/*
  2�������д洢�Ķ���ΪT��Ķ���
  2����Щ�������ܲ�����ɣ�����bool�����Ƿ�ɹ���
  3��Queue��ֻ�涨���еķ���(�ӿ�)����δȷ���洢�ṹ���ǳ����ࡣ
  4��T�Ķ�����ܽϴ����ô��ݱ������ֵ�ĸ��ƹ��죬������ܡ�
*/
template <class T>
class Queue
{
public:
    virtual void clear() = 0;	// ��Ϊ�ն���
    virtual bool enQueue(const T & item) = 0; 	// item��ӣ��ɹ��򷵻�����򷵻ؼ�
    virtual bool deQueue(T & item) = 0;     	// ���ض�ͷԪ�ز��Ӷ�����ɾ�����ɹ��򷵻���
    virtual bool getFront(T & item) = 0;	    // ���ض�ͷԪ�أ�����ɾ�����ɹ��򷵻���
    virtual bool isEmpty() = 0; 				// �����棬�������ѿ�
    virtual bool isFull() = 0;       			// �����棬����������
    virtual void print() = 0;
};

#endif




