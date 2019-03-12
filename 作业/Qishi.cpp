/*	骑士巡游问题
	解向量为n*n维，每个分量代表坐标，储存在vector向量里

*/
#include<iostream>
#include<fstream>
#include<cstring>
#include<vector>
using namespace std;
#define maxn 100

int n;//问题规模
int counts=0;//记录问题方案数
int map[maxn][maxn];//矩阵表示是否到达过，非零代表已经遍历过，为零表示没有遍历过
bool never;
const int dx[8]= {1,2,-1,-2,-2,-1,1,2};//八个方向
const int dy[8]= {2,1,2,1,-1,-2,-2,-1};
ofstream outfile("f1.txt",ios::out);
struct point
{
    int x;
    int y;
};
struct point a;
vector<point>vec;//遍历的先后坐标存在vector向量里

bool isarrived(int x,int y,int i)//判断各个方向是否可达
{
    return (x+dx[i]>=0&&x+dx[i]<n&&y+dy[i]>=0&&y+dy[i]<n
            &&map[x+dx[i]][y+dy[i]]==0);
}

void out_to_file()
{
    outfile<<"The "<<counts<<" methods:"<<endl;
    for (int i=0,j=1; i<n*n; i++,j++)
    {
        outfile<<"("<<vec[i].x<<","<<vec[i].y<<") ";
        if (j%n==0)	outfile<<endl;
    }
}
bool finish()
{
    for (int i=0; i<8; i++)
    {
        if (vec[n*n-1].x+dx[i]==vec[0].x&&vec[n*n-1].y+dy[i]==vec[0].y)
            return true;
    }
    return false;
}
void back(int s,int x,int y)
{
    if (s==n*n)
    {
        //if (finish())
        {
            counts++;
            out_to_file();
            //if (counts>=5000)
               // exit(1);
            return ;
        }
    }
    for (int i=0; i<8; i++)
    {
        if (isarrived(x,y,i))
        {
            map[x+dx[i]][y+dy[i]]=s+1;//标记已遍历
            a.x=x+dx[i];
            a.y=y+dy[i];
            vec.push_back(a);
            back(s+1,x+dx[i],y+dy[i]);
            map[x+dx[i]][y+dy[i]]=0;//去除标记
            vec.erase(--vec.end());

        }

    }
}
int main()
{
   // cin>>n;
   // cin>>a.x>>a.y;
   n=5;
   a.x=0;
   a.y=0;
    memset(map,0,sizeof(map));
    vec.push_back(a);
    map[a.x][a.y]=1;
    back(1,a.x,a.y);
    outfile.close();
    if (counts==0)
        cout<<"No Solution"<<endl;
    else
        cout<<"The total methods: "<<counts<<endl;
    return 0;
}
