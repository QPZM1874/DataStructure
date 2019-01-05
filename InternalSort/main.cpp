#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

#include "SortMethods.h"

// �����������Ԫ��ֵ
void valuedArrayRandomly(int * array,int n);

// �������Ԫ��ֵ
void outpuArray(int * array,int n);

int main()
{
    const int cnt = 10;
    int * arr = new int[cnt];

    cout << "����ֱ�Ӳ�������" << endl;
    valuedArrayRandomly(arr,cnt);
    outpuArray(arr,cnt);
    InsertSort<int>(arr,cnt);
    outpuArray(arr,cnt);
    cout << endl;

    cout << "����Shell����" << endl;
    valuedArrayRandomly(arr,cnt);
    outpuArray(arr,cnt);
    ShellSort<int>(arr,cnt);
    outpuArray(arr,cnt);
    cout << endl;

    cout << "����ѡ������" << endl;
    valuedArrayRandomly(arr,cnt);
    outpuArray(arr,cnt);
    SelectSort<int>(arr,cnt);
    outpuArray(arr,cnt);
    cout << endl;

    cout << "���Զ�����" << endl;
    valuedArrayRandomly(arr,cnt);
    outpuArray(arr,cnt);
    HeapSort<int>(arr,cnt);
    outpuArray(arr,cnt);
    cout << endl;


    cout << "����ð������" << endl;
    valuedArrayRandomly(arr,cnt);
    outpuArray(arr,cnt);
    BubbleSort<int>(arr,cnt);
    outpuArray(arr,cnt);
    cout << endl;

    cout << "���Կ�������" << endl;
    valuedArrayRandomly(arr,cnt);
    outpuArray(arr,cnt);
    QuickSort<int>(arr,0,cnt-1);
    outpuArray(arr,cnt);
    cout << endl;

    cout << "���Թ鲢����" << endl;
    valuedArrayRandomly(arr,cnt);
    outpuArray(arr,cnt);
    int * temp = new int[cnt];
    MergeSort<int>(arr,temp,0,cnt-1);
    delete [] temp;
    outpuArray(arr,cnt);
    cout << endl;

    return 0;
}

// �����������Ԫ��ֵ
void valuedArrayRandomly(int * array,int n)
{
    srand(time(NULL));  // ϵͳ��ǰʱ���ʼ�������������
    for (int i=0;i<n;i++) array[i]= rand() % 0xff;
}


// �������Ԫ��ֵ
void outpuArray(int * array,int n)
{
    for (int i=0;i<n;i++) cout << array[i] << "  ";
    cout << endl;
}
