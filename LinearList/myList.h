
// abstract data type for List
#ifndef LIST_H_INCLUDE
#define LIST_H_INCLUDE

/*
  1�����Ա��д洢�Ķ���ΪT��Ķ���
  2����Щ�������ܲ�����ɣ�����bool�����Ƿ�ɹ���
  3��List��ֻ�涨����ķ���(�ӿ�)����δȷ���洢�ṹ���ǳ����ࡣ
  4��T�Ķ�����ܽϴ����ô��ݱ������ֵ�ĸ��ƹ��죬������ܡ�
*/

template <class T>
class List
{
    virtual void clear() = 0; 				 	// �ÿ����Ա�
    virtual bool isEmpty() = 0;				 	// ���Ա�Ϊ��ʱ������True
    virtual bool app(const T & value) = 0;	// �ڱ�β���һ��Ԫ��value����ĳ�����1
    virtual bool ins(int pos, const T & value) = 0;	 	// ��λ��pos�ϲ���һ��Ԫ��value����ĳ�����1
    virtual bool del(int pos) = 0; 			 	        // ɾ��λ��pos�ϵ�Ԫ�أ���ĳ��ȼ� 1
    virtual bool getValue(int pos, T & value) = 0;		    // ����λ��pos��Ԫ��ֵ
    virtual bool setValue(int pos, const T & value) = 0;	// ��value�޸�λ��pos��Ԫ��ֵ
    virtual bool getPos(int & pos, const T & value) = 0;    // ������ֵΪvalue��Ԫ�ص�λ�÷��ص�pos��
};


#endif // LIST_H_INCLUDE

