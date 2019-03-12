// �����㷨ʵ��
// ģ���࣬ʵ����Դ�ļ�(���������)
// ֱ�Ӳ�������Shell����
// ѡ�����򡢶�����
// ð�����򡢿�������
// �鲢����

#ifndef SORTMETHODS_H_INCLUDED
#define SORTMETHODS_H_INCLUDED
#include "MaxHeap.h"

// ֱ�Ӳ�������
template <class Record>
void InsertSort (Record Array[], int n)  {
	// ֱ�Ӳ�������Array[]Ϊ���������飬nΪ���鳤��
	Record TempRecord;						// ��ʱ����
	for (int i=1; i<n; i++)  {					// ���β����i����¼
		TempRecord=Array[i];					// �ȰѼ�¼Array[i]��������ʱ��¼������
		int j = i-1;							// �ڴ�ѭ��������j��i-1��ʼ
		// ��ǰѰ�Ҽ�¼i����ȷλ��
		while (j >= 0 && TempRecord < Array[j])  {
			Array[j+1] = Array[j];				// ����Щ���ڵ��ڼ�¼i�ļ�¼����
			j = j - 1;						// �±�jǰ��
	    }
	    Array[j+1] = TempRecord; 				// ��ʱj+1���Ǽ�¼i����ȷλ�ã�����
	}
}

// --------------------------------------------------

// Shell����
// ��Array[delta]��Array[2*delta]��...��Array[?*delta]���в�������
template <class Record>
void ModInsSort(Record Array[], int n, int delta) {
	// ��Ա仯���������޸ĵĲ��������㷨������delta��ʾ��ǰ������
	Record TempRecord;						// ��ʱ����
	for (int i=delta; i<n; i+=delta) {		// ���������е�i����¼����
		TempRecord=Array[i];
		int j = i-delta;
		//��i��ʼ��ǰѰ�Ҽ�¼i����ȷλ��
		while (j>=0 && TempRecord < Array[j]) {
			Array[j+delta] = Array[j];		//����Щ���ڵ��ڼ�¼i�ļ�¼����
			j = j - delta;
	    }
	    Array[j+delta] = TempRecord; 			//��ʱj������Ǽ�¼i����ȷλ�ã�����
	}
}

/*
// ǰһ�㷨����һʵ�֣���ν����������
template <class Record>
void ModInsSort(Record Array[], int n, int delta) {	// �޸ĵĲ��������㷨������delta��ʾ��ǰ������
	for (int i=delta; i<n; i+=delta)			// ���������е�i����¼��Ѱ�Һ��ʵĲ���λ��
		for (int j=i; j>=delta; j-=delta)  {		//  j��dealtaΪ������ǰѰ�����öԽ��е���
			if (Array[j] < Array[j-delta])		//  Array[j] < Array[j-delta]�������Ϊ���ö�
				swap<Record>(Array[j], Array[j-delta]);		// ����Array[j]��Array[j-delta]���⺯���ṩ
			else break;
		}
}
*/

// ����ÿ�γ�2��Shell����
template <class Record>
void ShellSort(Record Array[], int n)  {	 		// Shell����Array[]Ϊ���������飬nΪ���鳤��
	for (int delta=n/2; delta>0; delta/=2)      	// ����deltaÿ�γ���2�ݼ�
		for (int i=0; i<delta; i++)			// �ֱ��delta�������н��в�������
			ModInsSort(&Array[i], n-i, delta);
}

// --------------------------------------------------

// ѡ������
template <class Record>
void SelectSort(Record Array[], int n)  {	// ֱ��ѡ������Array[]Ϊ���������飬nΪ���鳤��
	for (int i=0; i<n-1; i++)  {			// ����ѡ����iС�ļ�¼����ʣ���¼����С���Ǹ�
        int Smallest = i;				// ���ȼ����¼i������С��
        for (int j=i+1;j<n; j++)			// ��ʼ���ɨ������ʣ���¼
            if (Array[j] < Array[Smallest])
      	       Smallest = j;			// ������ָ�С�ļ�¼����¼����λ��
        swap<Record>(Array[i],Array[Smallest]);			// ����Array[i]�� Array[Smallest]����iС�ļ�¼��λ
	}
}

// --------------------------------------------------

// ������
// ���ѵ�ʵ����MaxHeap.h��
template <class Record>
void HeapSort(Record Array[], int n)
{
	MaxHeap<Record> max_heap = MaxHeap<Record>(Array,n,n);	//����
	for (int i=0; i<n-1; i++)		 // �����ҳ�ʣ���¼�е�����¼�����Ѷ�
		max_heap.MoveMax();
}

// --------------------------------------------------

// ð������
template <class Record>
void BubbleSort(Record Array[], int n)  {	// �Ż���ð������Array[]Ϊ���������飬nΪ���鳤��
	bool NoSwap;			// �Ƿ����˽����ı�־
	for (int i=0; i<n-1; i++)  {
	NoSwap = true;		// ��־��ʼΪ��
	for (int j=n-1; j>i; j--)
	  if (Array[j] < Array[j-1])  {	// �жϣ�Array[j-1]��Array[j]���Ƿ�����
		swap<Record>(Array[j], Array[j-1]);	// �������ö�Array[j]��Array[j-1]
		NoSwap = false;		// �����˽�������־��Ϊ��
	  }
	if (NoSwap)  			// ���û��������������ʾ���ź��򣬽����㷨
		return;
	}
}

// --------------------------------------------------

// �鲢����

// ��ֵѡ�����
int SelectPivot(int left, int right)  {				// ѡ����ֵ������left,right�ֱ��ʾ���е����Ҷ��±�
	return (left+right)/2;						// ѡ���м��¼��Ϊ��ֵ
}

// ����ֵ�ָ�
template <class Record>
int Partition(Record Array[], int left, int right)  {		// �ָ�����ָ����ֵ�ѵ�����ȷλ��
	int l = left;								//  lΪ��ָ�룬rΪ��ָ��
	int r = right;
	Record TempRecord = Array[r];				// ����ֵ�������ʱ������
	while (l != r)  {							// ��ʼ�ָl,r�������м��ƶ���ֱ������
		// lָ�������ƶ���ֱ���ҵ�һ��������ֵ�ļ�¼
		while (Array[l] <= TempRecord && r > l)	// ����Ҳ���԰�"<="��дΪ"<"���������ȶ�
			l++;
		if (l < r)  {						// ��l,r��δ������������Ԫ�ػ����ұߵĿ�λ
			Array[r] = Array[l];
			r--;							//  rָ�������ƶ�һ��
		}
		// rָ�������ƶ���ֱ���ҵ�һ��С�ڵ�����ֵ�ļ�¼
		while (Array[r] > TempRecord && r > l) 	// ����Ҳ���԰�">"��дΪ">="�����ټ�¼�ƶ�
			r--;
		if (l < r)  {						// ��l,r��δ������������Ԫ�ػ�����ߵĿ�λ
			Array[l] = Array[r];
			l++;							// lָ�������ƶ�һ��
		}
	}	//end while
	Array[l] = TempRecord;					// ����ֵ����ֽ�λ��l��
	return l;								// ���طֽ�λ��l
}

// ��������
template <class Record>
void QuickSort(Record Array[], int left, int right) { 		// Array[]Ϊ���������飬left,right�ֱ�Ϊ��������
	if (right <= left) 	return;					// �����������ֻ��0��1����¼���Ͳ�������
	int pivot = SelectPivot(left, right); 			// ѡ����ֵ
	swap<Record>(Array[pivot], Array[right]);   				// �ָ�ǰ�Ƚ���ֵ�ŵ�����ĩ��
	pivot = Partition(Array, left, right); 			// �ָ����ֵ�ѵ�����ȷλ��
    	QuickSort(Array, left, pivot-1);  				// ����ֵ��ߵ������н��еݹ��������
    	QuickSort(Array, pivot +1, right); 			// ����ֵ�ұߵ������н��еݹ��������
}

// --------------------------------------------------

// �鲢����

// һ�˺ϲ�
// Array-�������顢TempArray-��ʱ����
template <class Record>
void Merge(Record Array[], Record TempArray[], int left, int right, int middle)  {  //�鲢����
	for (int j=left; j<=right; j++)   					// �������ݴ�����ʱ����
		TempArray[j] = Array[j];
	int index1=left;								// ��������е���ʼλ��
	int index2=middle+1;							// �ұ������е���ʼλ��
	int i=left;									// ����ʼ�鲢
	while (index1 <= middle && index2 <= right)  {
		//ȡ��С�߲���ϲ�������
		if (TempArray[index1] <= TempArray[index2])	// Ϊ��֤�ȶ��ԣ����ʱ�������
			Array[i++] = TempArray[index1++];
		else  Array[i++] = TempArray[index2++];
	}
	while (index1 <= middle)						// ֻʣ�����У�����ֱ�Ӹ���
		Array[i++] = TempArray[index1++];
	while (index2 <= right) 						// ���ϸ�ѭ�����⣬ֱ�Ӹ���ʣ���������
		Array[i++] = TempArray[index2++];
}

// �鲢����ݹ麯��
template <class Record>
void MergeSort(Record Array[], Record TempArray[], int left, int right)  {
	//��·�鲢����Array[]Ϊ���������飬left��right�ֱ�Ϊ��������
	if (left < right)  {							// ���������ֻ��0��1����¼���Ͳ�������
		int middle=(left+right)/2;					//���м仮��Ϊ����������
		MergeSort(Array,TempArray,left,middle);		//�����һ����еݹ�
		MergeSort(Array, TempArray,middle+1,right);	//���ұ�һ����еݹ�
		Merge(Array, TempArray,left,right,middle);		// ���й鲢
	}
}

#endif // SORTMETHODS_H_INCLUDED
