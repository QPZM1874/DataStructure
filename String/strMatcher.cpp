#include "strMatcher.h"

int naiveStrMatching(string T, string P)
{
    int i = 0;							// ģʽ���±����
    int j = 0;							// Ŀ����±����
    int pLen = P.length( );             		// ģʽ�ĳ���
    int tLen = T.length( );					// Ŀ��ĳ���

    if  (tLen < pLen) 				    // ���Ŀ���ģʽ�̣�ƥ���޷��ɹ�
        return (-1);
    while ( i < pLen  &&  j < tLen)     		// �����Ƚ϶�Ӧ�ַ�����ʼƥ��
    {
        if (T[j] == P[i])
            i++,  j++;
        else
        {
            j = j - i + 1;
            i = 0;
        }
    }
    if ( i >= pLen)
        return (j - pLen);
    else return (-1);
}

// ��ģʽ�ַ�������������
void findNext(string pat, int * next)
{
    int i = 0;
    int k = -1;
    int m = pat.length();    				// mΪ�ַ���pat�ĳ���
    next[0] = -1;
    while (i < m)   						// ����i=1..m-1��nextֵ
    {
        while (k >= 0 && pat[i] != pat[k])  // �������β�Ӵ�
            k = next[k];
        i++;
        k++;
        if (i == m) break;
        if (pat[i] == pat[k] )
            next[i] = next[k];				//  pat[i]��pat[k]��ȣ��Ż�
        else next[i] = k;					// ����Ҫ�Ż�������λ��i����β�Ӵ�����
    }
}

// ģʽƥ���KMP�㷨
int KMPMatching(string targ, string pat,  int * next)
{
    int pLen=pat.length();     // ģʽ�ĳ���
    int tLen=targ.length();	   // Ŀ��ĳ���
    if (tLen < pLen) return (-1);	    // ���Ŀ���ģʽ�̣�ƥ���޷��ɹ�
    int i = 0,j = 0;		   // ģʽ��Ŀ����±�
    while ( i < pLen  &&  j < tLen)  // �����Ƚ϶�Ӧ�ַ�����ʼƥ��
    {
        // ѭ������ʽ��i,jָ����Ƚ�λ��
        if ( i == -1  ||  targ[j] == pat[i]) i++, j++;
        else i = next[i];
    }
    if ( i >= pLen) return (j - pLen);
    else return (-1);
}

int ComprehensiveKMP(string targ, string pat,  int * next)
{
    int pLen = pat.length();      // ģʽ�ĳ���
    int tLen = targ.length();	  // Ŀ��ĳ���
    if (tLen < pLen) return (-1); // Ŀ���ģʽ�̣�
    int i = 0,j = 0;	// ģʽ��Ŀ����±�
    for (j=0;j<tLen;j++/*��һ���Ƚ�λ��*/)
    {
        // ѭ������ʽ��i,jָ����Ƚ�λ��
        while (i>-1&&pat[i]!=targ[j])
            i = next[i]; //i������1
        if (i == -1 || targ[j] == pat[i])
            i++; //i��1,��һ���Ƚ�λ��
        if ( i == pLen) return (j - pLen + 1);
    }
    return (-1);
}
