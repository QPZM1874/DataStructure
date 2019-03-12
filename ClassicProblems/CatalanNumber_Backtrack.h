// 列车编组问题，引出卡特兰数、回溯法。
// 注意STL的应用

#ifndef CATALANNUMBER_BACKTRACK_H_INCLUDED
#define CATALANNUMBER_BACKTRACK_H_INCLUDED
#include <vector>
using namespace std;

// 递归求卡特兰数。
// 重复计算了很多相同子问题，可用动态规划避免。
int calcCatalanNumber(int n);

// 回溯法求解列车编组问题，可作为一般回溯法的框架
void backtrackCatalanSequence(int level);

// 回溯法求卡特兰数对应的01序列，0和1在具体问题含义不同。
void CatalanNumber01Sequence(int n,vector<char> & seq,int cnt_1,int cnt_0);


// 回溯法求求车皮编组方案。
void trainSequencing(int n,vector<char> & seq,int cnt_1,int cnt_0);


// 测试卡特兰数、列车编组问题的解决方案
void testCatalan_TrainSequence();


#endif // CATALANNUMBER_BACKTRACK_H_INCLUDED
