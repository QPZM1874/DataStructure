// �г��������⣬�����������������ݷ���
// ע��STL��Ӧ��

#ifndef CATALANNUMBER_BACKTRACK_H_INCLUDED
#define CATALANNUMBER_BACKTRACK_H_INCLUDED
#include <vector>
using namespace std;

// �ݹ�����������
// �ظ������˺ܶ���ͬ�����⣬���ö�̬�滮���⡣
int calcCatalanNumber(int n);

// ���ݷ�����г��������⣬����Ϊһ����ݷ��Ŀ��
void backtrackCatalanSequence(int level);

// ���ݷ�����������Ӧ��01���У�0��1�ھ������⺬�岻ͬ��
void CatalanNumber01Sequence(int n,vector<char> & seq,int cnt_1,int cnt_0);


// ���ݷ�����Ƥ���鷽����
void trainSequencing(int n,vector<char> & seq,int cnt_1,int cnt_0);


// ���Կ����������г���������Ľ������
void testCatalan_TrainSequence();


#endif // CATALANNUMBER_BACKTRACK_H_INCLUDED
