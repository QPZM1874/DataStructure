#include<iostream>
#include<vector>
using namespace std;
#define N 11 //迷宫问题规模

int mp[N][N]=         //N×N矩阵，0代表有路，1代表无路，2代表入口，3代表出口
{
    1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,1,0,1,0,1,
    1,0,1,0,0,0,1,0,1,0,1,
    1,0,1,0,0,0,0,0,1,0,1,
    1,0,1,1,1,1,1,0,1,0,1,
    1,0,1,0,1,0,0,0,1,0,1,
    1,0,0,0,1,0,1,0,0,0,1,
    1,1,1,1,1,0,1,0,0,0,1,
    1,0,1,0,1,0,1,0,0,0,1,
    1,0,1,0,0,0,1,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1
};
const int dx[4]= {0,0,-1,1};
const int dy[4]= {1,-1,0,0};
int a=8,b=9;//入口
int c=3,d=1;//出口
int minnpath=N*N;
int flag=0;
struct node
{
    int x;
    int y;
};
node xy;
vector<node>vec,vec1;//分别保存当前路径和当前最短路径
void back(int x,int y)
{
    if (x==c&&y==d)
    {
        flag=1;
        if (vec.size()<minnpath)
           {
               minnpath=vec.size()-1;
               vec1=vec;
           }
        return;
    }
    for (int k=0; k<4; k++)
    {
        if (mp[x+dx[k]][y+dy[k]]!=1)
        {
            mp[x+dx[k]][y+dy[k]]=1;
            xy.x=x+dx[k];
            xy.y=y+dy[k];
            vec.push_back(xy);
            if (vec.size()>minnpath)    return;
            back(x+dx[k],y+dy[k]);
            mp[x+dx[k]][y+dy[k]]=0;
            vec.erase(--vec.end());
        }
    }

}
int main()
{
    //cin>>x0>>y0;
    //cin>>x1>>y1;
    xy.x=a;
    xy.y=b;
    vec.push_back(xy);
    mp[a][b]=1;
    mp[c][d]=0;
    back(a,b);
    if (flag==0)
        cout<<"No Solution"<<endl;
    else
    {
        cout<<"最短的路径长度为 :"<<minnpath<<endl;
        cout<<"路径为:"<<endl;
        for (int i=0,j=1; i<minnpath+1; i++,j++)
        {
            cout<<"("<<vec1[i].x<<","<<vec1[i].y<<") ";
            if (j%N==0)
                cout<<endl;
        }
    }

    return 0;

}
