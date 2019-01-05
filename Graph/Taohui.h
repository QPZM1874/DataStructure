//套汇问题

#ifndef TAOHUI_H_INCLUDED
#define TAOHUI_H_INCLUDED
#include"AdjacencyMatrix.h"
#include<vector>
#include<string>
#include<fstream>
using namespace std;
ofstream outfile("Methods.txt",ios::out);
void Taohui(Graphm &G,int s,int t,vector<int>vec,string *str)
{
    double rate=1;
    vec.push_back(s);
    G.Mark[s]=VISITED;
    for (Edge e=G.FirstEdge(s); G.IsEdge(e); e=G.NextEdge(e))
    {
        rate=1;
        if (G.Mark[G.ToVertex(e)]==UNVISITED)
            Taohui(G,G.ToVertex(e),t,vec,str);
        else  if (G.ToVertex(e)==t)
        {
            int i;
            for ( i=0; i<vec.size()-1; i++)
                    rate*=G.ValueMatrix[vec [i] ] [vec [i+1] ];
            rate*=G.ValueMatrix[ vec[i] ] [ t ];
          //  cout<<"Rate:"<<rate<<endl;
            if (rate>1.0)
            {
                outfile<<"汇率: "<<rate<<endl;
                outfile<<"套汇方案:";
                for (int i=0;i<vec.size();i++)
                    outfile<<str[vec[i]]<<"-->";
                outfile<<str[t]<<endl;
                outfile<<endl;
            }
        }
    }
    G.Mark[s]=UNVISITED;
    vec.erase(--vec.end());
}
void testTaohui()
{
    const int N=5;
    int A[N][N]=
    {
        {0,1,1,1,1},
        {1,0,1,1,1},
        {1,1,0,1,1},
        {1,1,1,0,1},
        {1,1,1,1,0}
    };
    Graphm aGraph(N);              // 建立图
    aGraph.IniGraphm(&aGraph, (int *)A); // 初始化图
    double valuematrix[N][N]=
    {                     /*人民币       美元           日元             欧元        英镑
    /*人民币*/         {1,              0.15,          17.04,          0.13,       0.11},
    /*美元*/            {1/0.15,      1,               112.76,        0.84,        0.75},
    /*日元*/            {1/17.04,    1/112.76,    1,                0.008,      0.0066},
    /*欧元*/            {1/0.12,      1/0.84,        1/0.008,      1,             0.88},
   /*英镑*/             {1/0.11,      1/0.75,        1/0.0066,    1/0.88,     1      }

    };
    string str[N]={"人民币","美元","日元","欧元","英镑"};

    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            aGraph.ValueMatrix[i][j]=valuematrix[i][j];
    //vector<int>vec;
    for (int i=0;i<N;i++)
        {
            vector<int>vec;
            Taohui(aGraph,i,i,vec,str);
            aGraph.Mark[i]=VISITED;
            //vec.clear();
        }
        outfile.close();
}





#endif // TAOHUI_H_INCLUDED
