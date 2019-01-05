// �г��������⣬�����������������ݷ���
// ע��STL��Ӧ��
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
using namespace std;
#include "CatalanNumber_Backtrack.h"

// �ݹ�����������
// �ظ������˺ܶ���ͬ�����⣬���ö�̬�滮���⡣
int calcCatalanNumber(int n)
{
    if (n==0) return 1;
    if (n==1) return 1;
    int cnt=0;
    for (int i=1; i<=n; i++) cnt += calcCatalanNumber(i-1) * calcCatalanNumber(n-i);
    return cnt;
}

// ���ݷ�����г��������⣬����Ϊһ����ݷ��Ŀ��
// ʹ��ȫ�ֱ�����Ϊ��ͻ����ܣ���������ģ�黯�̶�
static int scale = 3; //�����ģ
static vector<int> sequence;  //��ǰ��
static int countOf01[2] = {0,0};  //��ǰ����0��1���ۼ���
static int solutionCount = 0; //���н����
// level:��ռ����ĵ�ǰ�㣬�ݹ��1�㿪ʼ
void backtrackCatalanSequence(int level)
{
    if (level > 2*scale) //������Ҷ֮���㣬��һ���н�
    {
        solutionCount++;
        cout << setw(6) << setiosflags(ios::left) << solutionCount << ": ";
        vector<int>::iterator iter;  //ʵ����ջ��ʹ��vector��Ϊ�˱�����
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
    for(int k=1; k>=0; k--) //������������
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

// ���ݷ�����������Ӧ��01���У�0��1�ھ������⺬�岻ͬ��
// ��������ʱ�ڷ�װ�Ը��ã�
// n:�����ģ��
// seq:ջ�ṹ01���С���ʼΪ�գ����������̣���2n�õ�һ�������
// cnt_1,cnt_0:seq��1��0�ĸ�������ʼΪ0��
// seqӦ�ô�������Ϊ�ݹ����ֻ��һ����¼��������С�
void CatalanNumber01Sequence(int n,vector<char> & seq,int cnt_1,int cnt_0)
{
    static int totalNumber = 0;
    if (cnt_1 < n)  //������1�ĸ�������n
    {
        seq.push_back('1');
        cnt_1++;
        CatalanNumber01Sequence(n,seq,cnt_1,cnt_0);
        seq.pop_back(); //ȥ��ĩβԪ��
        cnt_1--;
    }
    if((cnt_1 <= n) && (cnt_0 < cnt_1)) //������1�ĸ�������n��0�ĸ�������1�ĸ���
    {
        seq.push_back('0');
        cnt_0++;
        CatalanNumber01Sequence(n,seq,cnt_1,cnt_0);
        seq.pop_back(); //ȥ��ĩβԪ��
        cnt_0--;
    }
    if(seq.size()==2*n)
    {
        totalNumber++;
        cout << setw(6) << setiosflags(ios::left) << totalNumber << ": ";
        vector<char>::iterator iter;  //ʵ����ջ��ʹ��vector��Ϊ�˱�����
        for(iter=seq.begin(); iter!=seq.end(); iter++)
        {
            cout<<(*iter)<<" ";
        }
        cout<<endl;
    }
}

// ���ݷ�����Ƥ���鷽����
// ������������Ӧ��01���У�Ȼ��ת���ɱ������С�
// 1��Ӧ��ջ��0��Ӧ��ջ��
// n:�����ģ��
// seq:ջ�ṹ01���С���ʼΪ�գ����������̣���2n�õ�һ�������
// cnt_1,cnt_0:seq��1��0�ĸ�������ʼΪ0��
// seqӦ�ô�������Ϊ�ݹ����ֻ��һ����¼��������С�
void trainSequencing(int n,vector<char> & seq,int cnt_1,int cnt_0)
{
    static int totalNumber = 0;
    if (cnt_1 < n)  //������1�ĸ�������n
    {
        seq.push_back('1');
        cnt_1++;
        trainSequencing(n,seq,cnt_1,cnt_0);
        seq.pop_back(); //ȥ��ĩβԪ��
        cnt_1--;
    }
    if((cnt_1 <= n) && (cnt_0 < cnt_1)) //������1�ĸ�������n��0�ĸ�������1�ĸ���
    {
        seq.push_back('0');
        cnt_0++;
        trainSequencing(n,seq,cnt_1,cnt_0);
        seq.pop_back(); //ȥ��ĩβԪ��
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

// ���Կ����������г���������Ľ������
void testCatalan_TrainSequence()
{

}
