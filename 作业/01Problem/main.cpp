/*0—1背包问题（回溯解法）
	n个物品，背包容量为 M ,第i个物品重wi，价值是pi
	解向量是（x1,x2,...,xn),xi是0或1；
	约束要求 x1w1+x2w2+...+xnwn<=M;
			使 x1p1+x2p2+...+xnpn 取最大值
*/
#include<iostream>
#include<algorithm>

using namespace std;
int n,M;//物品数量，背包容量
bool x[10000],y[10000];//解向量，x是当前解向量，y是最终解向量
double weight=0,value=0,bestvalue=0;//当前重量和价值，最大价值
struct node
{
    double w;//物品重量
    double p;//物品价值
    double avervalue;//单位价值
} wp[10000];

bool cmap(node a,node b)
{
    return a.avervalue>b.avervalue;
}
double supvalue(int i)//计算从i开始的子树能达到的价值上界
{
    double leftweight=M-weight;//当前剩余的容量
    double sup=value;//价值上界先设置为当前价值
    while (i<n&&wp[i].w<=leftweight)
    {
        leftweight-=wp[i].w;
        sup+=wp[i].p;
        i++;
    }//直到背包无法装下物品
    if (i<n)
        sup+=wp[i].p*leftweight/wp[i].w;//求上界
    return sup;
}
void back(int i)
{
    //i为递归层数，weight为当前重量，value为当前价值
    if (i>=n)
    {
        if (value>bestvalue)
        {
            bestvalue=value;
            for (int j=0; j<n; j++)
                y[j]=x[j];		//保存最优解
        }
        return;
    }
    else
    {
        //x[i]=1;
        if (weight+wp[i].w<=M)
        {
            x[i]=1;
            weight+=wp[i].w*x[i];
            value+=wp[i].p*x[i];
            back(i+1);
            weight-=wp[i].w*x[i];//去除标记
            value-=wp[i].p*x[i];
        }
        //x[i]=0;
        if (supvalue(i+1)>bestvalue)
        {
            x[i]=0;			//进入右子树
            back(i+1);
        }
    }
}
int main()
{
    cin>>n>>M;
    for (int i=0; i<n; i++)
    {
        cin>>wp[i].w;
    }
    for (int i=0; i<n; i++)
    {
        cin>>wp[i].p;
        wp[i].avervalue=wp[i].p/wp[i].w;
    }
    int maxvalue=0,weight1=0;
    for (int i=0; i<n; i++)
        weight1+=wp[i].w;
    if (weight1<=M)
    {
        for (int i=0; i<n; i++)
        {
            y[i]=1;
            maxvalue+=wp[i].p;
        }
    }
    else
    {
        sort(wp,wp+n,cmap);
        back(0);
    }
    cout<<"The sorted weight and price:" <<endl;;
    for (int i=0; i<n; i++)
        cout<<wp[i].w<<" ";
    cout<<endl;
    for (int i=0; i<n; i++)
        cout<<wp[i].p<<" ";
    cout<<endl;
    cout<<"The methods vector:";
    for (int i=0; i<n; i++)
    {
        cout<<y[i];
        maxvalue+=y[i]*wp[i].p;
    }
    cout<<endl<<"The maximum value:"<<maxvalue<<endl;
    return 0;
}
/*
10 150
11 23 43 1 21 55 29 38 45 12
21 33 67 11 31 65 28 43 60 29
*/
