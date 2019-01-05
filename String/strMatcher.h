#ifndef STRMATCHER_H_INCLUDED
#define STRMATCHER_H_INCLUDED

#include <string>

using namespace std;

// �����ַ���ƥ��
// ���ش�0��ʼ�ĵ�һ��ƥ��λ��
// ����-1��ʾû��ƥ��
int naiveStrMatching(string T, string P);

// ��ģʽ�ַ�������������
// pat-ģʽ�ַ�����next-�����������������
void findNext(string pat, int * next);

// ģʽƥ���KMP�㷨
// ���ش�0��ʼ�ĵ�һ��ƥ��λ��
// ����-1��ʾû��ƥ��
int KMPMatching(string targ, string pat,  int * next);

// KMP���������ѭ���İ汾
int ComprehensiveKMP(string targ, string pat,  int * next);

#endif // STRMATCHER_H_INCLUDED
