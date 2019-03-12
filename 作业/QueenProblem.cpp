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
	for (int j=0;j<k;j++)
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
		counts++;
		for (int k=0;k<n;k++)
			cout<<x[k];
		cout<<endl;
		//return;
	}
	else
	{
		for ( int j=0;j<n;j++)
		{
			x[i]=j;
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
	cout<<"总的解决方案数：";
	cout<<counts<<endl;
	return 0;
}
