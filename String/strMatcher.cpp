#include "strMatcher.h"

int naiveStrMatching(string T, string P)
{
    int i = 0;							// 模式的下标变量
    int j = 0;							// 目标的下标变量
    int pLen = P.length( );             		// 模式的长度
    int tLen = T.length( );					// 目标的长度

    if  (tLen < pLen) 				    // 如果目标比模式短，匹配无法成功
        return (-1);
    while ( i < pLen  &&  j < tLen)     		// 反复比较对应字符来开始匹配
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

// 求模式字符串的特征数组
void findNext(string pat, int * next)
{
    int i = 0;
    int k = -1;
    int m = pat.length();    				// m为字符串pat的长度
    next[0] = -1;
    while (i < m)   						// 计算i=1..m-1的next值
    {
        while (k >= 0 && pat[i] != pat[k])  // 求最大首尾子串
            k = next[k];
        i++;
        k++;
        if (i == m) break;
        if (pat[i] == pat[k] )
            next[i] = next[k];				//  pat[i]和pat[k]相等，优化
        else next[i] = k;					// 不需要优化，就是位置i的首尾子串长度
    }
}

// 模式匹配的KMP算法
int KMPMatching(string targ, string pat,  int * next)
{
    int pLen=pat.length();     // 模式的长度
    int tLen=targ.length();	   // 目标的长度
    if (tLen < pLen) return (-1);	    // 如果目标比模式短，匹配无法成功
    int i = 0,j = 0;		   // 模式和目标的下标
    while ( i < pLen  &&  j < tLen)  // 反复比较对应字符来开始匹配
    {
        // 循环不变式：i,j指向待比较位置
        if ( i == -1  ||  targ[j] == pat[i]) i++, j++;
        else i = next[i];
    }
    if ( i >= pLen) return (j - pLen);
    else return (-1);
}

int ComprehensiveKMP(string targ, string pat,  int * next)
{
    int pLen = pat.length();      // 模式的长度
    int tLen = targ.length();	  // 目标的长度
    if (tLen < pLen) return (-1); // 目标比模式短！
    int i = 0,j = 0;	// 模式和目标的下标
    for (j=0;j<tLen;j++/*下一个比较位置*/)
    {
        // 循环不变式：i,j指向待比较位置
        while (i>-1&&pat[i]!=targ[j])
            i = next[i]; //i降至少1
        if (i == -1 || targ[j] == pat[i])
            i++; //i增1,下一个比较位置
        if ( i == pLen) return (j - pLen + 1);
    }
    return (-1);
}
