// 列车编组问题，引出卡特兰数、回溯法。
// 注意STL的应用
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
using namespace std;
#include "CatalanNumber_Backtrack.h"

// 递归求卡特兰数。
// 重复计算了很多相同子问题，可用动态规划避免。
int calcCatalanNumber(int n)
{
    if (n==0) return 1;
    if (n==1) return 1;
    int cnt=0;
    for (int i=1; i<=n; i++) cnt += calcCatalanNumber(i-1) * calcCatalanNumber(n-i);
    return cnt;
}

// 回溯法求解列车编组问题，可作为一般回溯法的框架
// 使用全局变量是为了突出框架，但降低了模块化程度
static int scale = 3; //问题规模
static vector<int> sequence;  //当前解
static int countOf01[2] = {0,0};  //当前解中0、1的累计数
static int solutionCount = 0; //可行解计数
// level:解空间树的当前层，递归从1层开始
void backtrackCatalanSequence(int level)
{
    if (level > 2*scale) //搜索到叶之外结点，得一可行解
    {
        solutionCount++;
        cout << setw(6) << setiosflags(ios::left) << solutionCount << ": ";
        vector<int>::iterator iter;  //实质是栈，使用vector是为了遍历！
        stack<int> aStack;
        int k=0;
        for(iter=sequence.begin(); iter!=sequence.end(); iter++)
        {
            if((*iter)==1)
            {
                k++;
                aStack.push(k);
            }
            else
            {
                cout<<aStack.top()<<" ";
                aStack.pop();
            }
        }
        cout<<endl;
        return;
    }
    for(int k=1; k>=0; k--) //搜索左、右子树
    {
        sequence.push_back(k);
        countOf01[k]++;
        if (countOf01[1]>=countOf01[0]
                && countOf01[1]<=scale
                && countOf01[0]<=scale)
        {
            backtrackCatalanSequence(level+1);
            countOf01[k]--;
            sequence.pop_back();
        }
        else
        {
            countOf01[k]--;
            sequence.pop_back();
        }
    }
}

// 回溯法求卡特兰数对应的01序列，0和1在具体问题含义不同。
// 函数参数时期封装性更好！
// n:问题规模。
// seq:栈结构01序列。初始为空，增长或缩短，到2n得到一个结果。
// cnt_1,cnt_0:seq中1和0的个数。初始为0。
// seq应用传递是因为递归过程只有一个记录结果的序列。
void CatalanNumber01Sequence(int n,vector<char> & seq,int cnt_1,int cnt_0)
{
    static int totalNumber = 0;
    if (cnt_1 < n)  //序列中1的个数不到n
    {
        seq.push_back('1');
        cnt_1++;
        CatalanNumber01Sequence(n,seq,cnt_1,cnt_0);
        seq.pop_back(); //去掉末尾元素
        cnt_1--;
    }
    if((cnt_1 <= n) && (cnt_0 < cnt_1)) //序列中1的个数不到n、0的个数少于1的个数
    {
        seq.push_back('0');
        cnt_0++;
        CatalanNumber01Sequence(n,seq,cnt_1,cnt_0);
        seq.pop_back(); //去掉末尾元素
        cnt_0--;
    }
    if(seq.size()==2*n)
    {
        totalNumber++;
        cout << setw(6) << setiosflags(ios::left) << totalNumber << ": ";
        vector<char>::iterator iter;  //实质是栈，使用vector是为了遍历！
        for(iter=seq.begin(); iter!=seq.end(); iter++)
        {
            cout<<(*iter)<<" ";
        }
        cout<<endl;
    }
}

// 回溯法求求车皮编组方案。
// 先求卡特兰数对应的01序列，然后转换成编组序列。
// 1对应进栈，0对应出栈。
// n:问题规模。
// seq:栈结构01序列。初始为空，增长或缩短，到2n得到一个结果。
// cnt_1,cnt_0:seq中1和0的个数。初始为0。
// seq应用传递是因为递归过程只有一个记录结果的序列。
void trainSequencing(int n,vector<char> & seq,int cnt_1,int cnt_0)
{
    static int totalNumber = 0;
    if (cnt_1 < n)  //序列中1的个数不到n
    {
        seq.push_back('1');
        cnt_1++;
        trainSequencing(n,seq,cnt_1,cnt_0);
        seq.pop_back(); //去掉末尾元素
        cnt_1--;
    }
    if((cnt_1 <= n) && (cnt_0 < cnt_1)) //序列中1的个数不到n、0的个数少于1的个数
    {
        seq.push_back('0');
        cnt_0++;
        trainSequencing(n,seq,cnt_1,cnt_0);
        seq.pop_back(); //去掉末尾元素
        cnt_0--;
    }
    if(seq.size()==2*n)
    {
        totalNumber++;
        cout << setw(6) << setiosflags(ios::left) << totalNumber << ": ";
        vector<char>::iterator iter;
        stack<int> aStack;
        int k=0;
        for(iter=seq.begin(); iter!=seq.end(); iter++)
        {
            if((*iter)=='1')
            {
                k++;
                aStack.push(k);
            }
            else
            {
                cout<<aStack.top()<<" ";
                aStack.pop();
            }
        }
        cout<<endl;
    }
}

// 测试卡特兰数、列车编组问题的解决方案
void testCatalan_TrainSequence()
{

}
