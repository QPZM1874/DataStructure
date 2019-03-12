/* n皇后问题（回溯）
	每一行放一个皇后，解向量为（x0,x1,x2,...,xn)，
	xi表示第i行的皇后在第xi列
	i!=j时,xi!=xj,且abs(xi-xj)!=abs(i-j)

*/
#include<iostream>
#include<cmath>
using namespace std;
int x[1000];
int n;
int counts=0;
bool place(int k)
{
	for (int j=0;j<k;j++)//已摆放的皇后要与当前皇后不在同一行同一列
	{
		if (x[k]==x[j]||abs(x[k]-x[j])==abs(k-j))
			return false;
	}
	return true;
}
void back(int i)
{//i为递归层数即第i列
	//cout<<"hello\n";
	if (i>n-1)
	{
		counts++;//解法增加一
		for (int k=0;k<n;k++)
			cout<<x[k];	//输出解
		cout<<endl;
		return;
	}
	else
	{
		for ( int j=0;j<n;j++)
		{
			x[i]=j;	//x[i]有n种选择，逐个测试
			//cout<<"x "<<i<<"="<<j<<endl;
			if (place(i))
			{
				back(i+1);
			}
		}
	}

}
int main()
{
	cin>>n;
	back(0);
	cout<<"The total methods: ";
	cout<<counts<<endl;
	return 0;
}
