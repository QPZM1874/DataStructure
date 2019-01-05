#ifndef STRMATCHER_H_INCLUDED
#define STRMATCHER_H_INCLUDED

#include <string>

using namespace std;

// 朴素字符串匹配
// 返回从0开始的第一个匹配位置
// 返回-1表示没有匹配
int naiveStrMatching(string T, string P);

// 求模式字符串的特征数组
// pat-模式字符串，next-存放特征向量的数组
void findNext(string pat, int * next);

// 模式匹配的KMP算法
// 返回从0开始的第一个匹配位置
// 返回-1表示没有匹配
int KMPMatching(string targ, string pat,  int * next);

// KMP易于理解其循环的版本
int ComprehensiveKMP(string targ, string pat,  int * next);

#endif // STRMATCHER_H_INCLUDED
