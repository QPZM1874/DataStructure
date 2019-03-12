// 排序算法实现
// 模板类，实现在源文件(编译器相关)
// 直接插入排序、Shell排序；
// 选择排序、堆排序
// 冒泡排序、快速排序
// 归并排序

#ifndef SORTMETHODS_H_INCLUDED
#define SORTMETHODS_H_INCLUDED
#include "MaxHeap.h"

// 直接插入排序
template <class Record>
void InsertSort (Record Array[], int n)  {
	// 直接插入排序，Array[]为待排序数组，n为数组长度
	Record TempRecord;						// 临时变量
	for (int i=1; i<n; i++)  {					// 依次插入第i个记录
		TempRecord=Array[i];					// 先把记录Array[i]保留在临时记录变量中
		int j = i-1;							// 内存循环变量从j从i-1开始
		// 往前寻找记录i的正确位置
		while (j >= 0 && TempRecord < Array[j])  {
			Array[j+1] = Array[j];				// 将那些大于等于记录i的记录后移
			j = j - 1;						// 下标j前移
	    }
	    Array[j+1] = TempRecord; 				// 此时j+1就是记录i的正确位置，回填
	}
}

// --------------------------------------------------

// Shell排序
// 对Array[delta]、Array[2*delta]、...、Array[?*delta]进行插入排序
template <class Record>
void ModInsSort(Record Array[], int n, int delta) {
	// 针对变化的增量而修改的插入排序算法，参数delta表示当前的增量
	Record TempRecord;						// 临时变量
	for (int i=delta; i<n; i+=delta) {		// 对子序列中第i个记录排序
		TempRecord=Array[i];
		int j = i-delta;
		//从i开始往前寻找记录i的正确位置
		while (j>=0 && TempRecord < Array[j]) {
			Array[j+delta] = Array[j];		//将那些大于等于记录i的记录后移
			j = j - delta;
	    }
	    Array[j+delta] = TempRecord; 			//此时j后面就是记录i的正确位置，回填
	}
}

/*
// 前一算法的另一实现，逐次交换而非向后挤
template <class Record>
void ModInsSort(Record Array[], int n, int delta) {	// 修改的插入排序算法，参数delta表示当前的增量
	for (int i=delta; i<n; i+=delta)			// 对子序列中第i个记录，寻找合适的插入位置
		for (int j=i; j>=delta; j-=delta)  {		//  j以dealta为步长向前寻找逆置对进行调整
			if (Array[j] < Array[j-delta])		//  Array[j] < Array[j-delta]，则二者为逆置对
				swap<Record>(Array[j], Array[j-delta]);		// 交换Array[j]和Array[j-delta]，库函数提供
			else break;
		}
}
*/

// 增量每次除2的Shell排序
template <class Record>
void ShellSort(Record Array[], int n)  {	 		// Shell排序，Array[]为待排序数组，n为数组长度
	for (int delta=n/2; delta>0; delta/=2)      	// 增量delta每次除以2递减
		for (int i=0; i<delta; i++)			// 分别对delta个子序列进行插入排序
			ModInsSort(&Array[i], n-i, delta);
}

// --------------------------------------------------

// 选择排序
template <class Record>
void SelectSort(Record Array[], int n)  {	// 直接选择排序，Array[]为待排序数组，n为数组长度
	for (int i=0; i<n-1; i++)  {			// 依次选出第i小的记录，即剩余记录中最小的那个
        int Smallest = i;				// 首先假设记录i就是最小的
        for (int j=i+1;j<n; j++)			// 开始向后扫描所有剩余记录
            if (Array[j] < Array[Smallest])
      	       Smallest = j;			// 如果发现更小的记录，记录它的位置
        swap<Record>(Array[i],Array[Smallest]);			// 交换Array[i]和 Array[Smallest]，第i小的记录到位
	}
}

// --------------------------------------------------

// 堆排序
// 最大堆的实现在MaxHeap.h中
template <class Record>
void HeapSort(Record Array[], int n)
{
	MaxHeap<Record> max_heap = MaxHeap<Record>(Array,n,n);	//建堆
	for (int i=0; i<n-1; i++)		 // 依次找出剩余记录中的最大记录，即堆顶
		max_heap.MoveMax();
}

// --------------------------------------------------

// 冒泡排序
template <class Record>
void BubbleSort(Record Array[], int n)  {	// 优化的冒泡排序，Array[]为待排序数组，n为数组长度
	bool NoSwap;			// 是否发生了交换的标志
	for (int i=0; i<n-1; i++)  {
	NoSwap = true;		// 标志初始为真
	for (int j=n-1; j>i; j--)
	  if (Array[j] < Array[j-1])  {	// 判断（Array[j-1]，Array[j]）是否逆置
		swap<Record>(Array[j], Array[j-1]);	// 交换逆置对Array[j]，Array[j-1]
		NoSwap = false;		// 发生了交换，标志变为假
	  }
	if (NoSwap)  			// 如果没发生过交换，表示已排好序，结束算法
		return;
	}
}

// --------------------------------------------------

// 归并排序

// 轴值选择策略
int SelectPivot(int left, int right)  {				// 选择轴值，参数left,right分别表示序列的左右端下标
	return (left+right)/2;						// 选择中间记录作为轴值
}

// 按轴值分割
template <class Record>
int Partition(Record Array[], int left, int right)  {		// 分割函数，分割后轴值已到达正确位置
	int l = left;								//  l为左指针，r为右指针
	int r = right;
	Record TempRecord = Array[r];				// 将轴值存放在临时变量中
	while (l != r)  {							// 开始分割，l,r不断向中间移动，直到相遇
		// l指针向右移动，直到找到一个大于轴值的记录
		while (Array[l] <= TempRecord && r > l)	// 这里也可以把"<="改写为"<"，反正不稳定
			l++;
		if (l < r)  {						// 若l,r尚未相遇，将逆置元素换到右边的空位
			Array[r] = Array[l];
			r--;							//  r指针向左移动一步
		}
		// r指针向左移动，直到找到一个小于等于轴值的记录
		while (Array[r] > TempRecord && r > l) 	// 这里也可以把">"改写为">="，减少记录移动
			r--;
		if (l < r)  {						// 若l,r尚未相遇，将逆置元素换到左边的空位
			Array[l] = Array[r];
			l++;							// l指针向右移动一步
		}
	}	//end while
	Array[l] = TempRecord;					// 把轴值回填到分界位置l上
	return l;								// 返回分界位置l
}

// 快速排序
template <class Record>
void QuickSort(Record Array[], int left, int right) { 		// Array[]为待排序数组，left,right分别为数组两端
	if (right <= left) 	return;					// 如果子序列中只有0或1个记录，就不需排序
	int pivot = SelectPivot(left, right); 			// 选择轴值
	swap<Record>(Array[pivot], Array[right]);   				// 分割前先将轴值放到数组末端
	pivot = Partition(Array, left, right); 			// 分割后轴值已到达正确位置
    	QuickSort(Array, left, pivot-1);  				// 对轴值左边的子序列进行递归快速排序
    	QuickSort(Array, pivot +1, right); 			// 对轴值右边的子序列进行递归快速排序
}

// --------------------------------------------------

// 归并排序

// 一趟合并
// Array-排序数组、TempArray-临时数组
template <class Record>
void Merge(Record Array[], Record TempArray[], int left, int right, int middle)  {  //归并过程
	for (int j=left; j<=right; j++)   					// 将数组暂存入临时数组
		TempArray[j] = Array[j];
	int index1=left;								// 左边子序列的起始位置
	int index2=middle+1;							// 右边子序列的起始位置
	int i=left;									// 从左开始归并
	while (index1 <= middle && index2 <= right)  {
		//取较小者插入合并数组中
		if (TempArray[index1] <= TempArray[index2])	// 为保证稳定性，相等时左边优先
			Array[i++] = TempArray[index1++];
		else  Array[i++] = TempArray[index2++];
	}
	while (index1 <= middle)						// 只剩左序列，可以直接复制
		Array[i++] = TempArray[index1++];
	while (index2 <= right) 						// 与上个循环互斥，直接复制剩余的右序列
		Array[i++] = TempArray[index2++];
}

// 归并排序递归函数
template <class Record>
void MergeSort(Record Array[], Record TempArray[], int left, int right)  {
	//两路归并排序，Array[]为待排序数组，left，right分别为数组两端
	if (left < right)  {							// 如果序列中只有0或1个记录，就不用排序
		int middle=(left+right)/2;					//从中间划分为两个子序列
		MergeSort(Array,TempArray,left,middle);		//对左边一半进行递归
		MergeSort(Array, TempArray,middle+1,right);	//对右边一半进行递归
		Merge(Array, TempArray,left,right,middle);		// 进行归并
	}
}

#endif // SORTMETHODS_H_INCLUDED
