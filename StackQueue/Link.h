#ifndef LINKNODE_H
#define LINKNODE_H

// �õ���������ģ��
template <class T>
class Link
{
public:
    T  		data;						// ���ڱ�����Ԫ�ص�����
    Link 	* next;						// ָ���̽���ָ��

    Link(const T info, Link* nextValue) // ��������������Link���캯��
    {
        data = info;
        next = nextValue;
    }
    Link(Link* nextValue = NULL)   	    // ��������������Link���캯��
    {
        next = nextValue;
    }
};

#endif // LINKNODE_H

