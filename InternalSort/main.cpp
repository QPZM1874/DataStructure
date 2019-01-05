#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

#include "SortMethods.h"

// 数组随机生成元素值
void valuedArrayRandomly(int * array,int n);

// 输出数组元素值
void outpuArray(int * array,int n);

int main()
{
    const int cnt = 10;
    int * arr = new int[cnt];

    cout << "测试直接插入排序" << endl;
    valuedArrayRandomly(arr,cnt);
    outpuArray(arr,cnt);
    InsertSort<int>(arr,cnt);
    outpuArray(arr,cnt);
    cout << endl;

    cout << "测试Shell排序" << endl;
    valuedArrayRandomly(arr,cnt);
    outpuArray(arr,cnt);
    ShellSort<int>(arr,cnt);
    outpuArray(arr,cnt);
    cout << endl;

    cout << "测试选择排序" << endl;
    valuedArrayRandomly(arr,cnt);
    outpuArray(arr,cnt);
    SelectSort<int>(arr,cnt);
    outpuArray(arr,cnt);
    cout << endl;

    cout << "测试堆排序" << endl;
    valuedArrayRandomly(arr,cnt);
    outpuArray(arr,cnt);
    HeapSort<int>(arr,cnt);
    outpuArray(arr,cnt);
    cout << endl;


    cout << "测试冒泡排序" << endl;
    valuedArrayRandomly(arr,cnt);
    outpuArray(arr,cnt);
    BubbleSort<int>(arr,cnt);
    outpuArray(arr,cnt);
    cout << endl;

    cout << "测试快速排序" << endl;
    valuedArrayRandomly(arr,cnt);
    outpuArray(arr,cnt);
    QuickSort<int>(arr,0,cnt-1);
    outpuArray(arr,cnt);
    cout << endl;

    cout << "测试归并排序" << endl;
    valuedArrayRandomly(arr,cnt);
    outpuArray(arr,cnt);
    int * temp = new int[cnt];
    MergeSort<int>(arr,temp,0,cnt-1);
    delete [] temp;
    outpuArray(arr,cnt);
    cout << endl;

    return 0;
}

// 数组随机生成元素值
void valuedArrayRandomly(int * array,int n)
{
    srand(time(NULL));  // 系统当前时间初始化随机数发生器
    for (int i=0;i<n;i++) array[i]= rand() % 0xff;
}


// 输出数组元素值
void outpuArray(int * array,int n)
{
    for (int i=0;i<n;i++) cout << array[i] << "  ";
    cout << endl;
}
