#include <iostream>
#include "strMatcher.h"
using namespace std;

int main()
{
    string t = "abcdefghijklmn";
    string p = "defgh";

    cout <<"Naive:  " << p << " at " << naiveStrMatching(t,p) << " in " << t << endl;

    int * next = new int[t.length()];

    findNext(p,next);

    cout <<"KMP V1: " << p << " at " << KMPMatching(t,p,next) << " in " << t << endl;
    cout <<"KMP V2: " << p << " at " << ComprehensiveKMP(t,p,next) << " in " << t << endl;

    delete [] next;

    // ���������ģʽ��ʾ�������ƥ��ʱ���ƶ����

    string pat = "cccccccccc";  //ȫ��ͬ
    int * nxt = new int[pat.length()];
    findNext(pat, nxt);
    cout << "string: " << pat << endl;
    cout << "next:   ";
    for (int i=0;i<pat.length();i++) cout << nxt[i] << ",";
    cout << endl;
    delete [] nxt;


    pat="abcdefghij"; //ȫ����ͬ
    nxt = new int[pat.length()];
    findNext(pat, nxt);
    cout << "string: " << pat << endl;
    cout << "next:   ";
    for (int i=0;i<pat.length();i++) cout << nxt[i] << ",";
    cout << endl;
    delete [] nxt;

    pat="abacab";
    nxt = new int[pat.length()];
    findNext(pat, nxt);
    cout << "string: " << pat << endl;
    cout << "next:   ";
    for (int i=0;i<pat.length();i++) cout << nxt[i] << ",";
    cout << endl;
    delete [] nxt;


    return 0;
}
