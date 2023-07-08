#include <cstdio>
#include <time.h>
#include <stdlib.h>
#include<iostream>
using namespace std;
#include<algorithm>

// 假设都用排升序

void PrintArray(int* a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void InsertSort(int* a, int n) {
	// [0, end]有序  end+1位置的值插入[0, end]，让[0, end+1]有序
	for (int j = 1; j <= n - 1; j++) { //n-1次搜索
		int key = a[j];
		int i = j - 1;
		while (i >= 0 && a[i] > key) {
			a[i + 1] = a[i];//移动记录
			i--;
		}
		a[i + 1] = key;//找到插入位置并插入
	}
}

//void TestInsertSort() {
//	int a[] = { 3, 5, 2, 7, 8, 6, 1, 9, 4, 0 };
//	InsertSort(a, sizeof(a) / sizeof(int));
//	PrintArray(a, sizeof(a) / sizeof(int));
//}

void SelectSort(int* a, int n)
{
	for (int i = 0; i <= n - 2;i++) {
		int key = i; 
// 在剩下的序列中选择最小的元素并将其位置赋给key
		for (int j = i + 1; j <= n - 1; j++) {
			if (a[j] < a[key]) {
				key = j;
			}
		}
// 将未排序部分的最小元素换到有序部分的最后位置i
			swap(a[i], a[key]);
	}
}

//void TestSelectSort()
//{
//	int a[] = { 9, 3, 5, 2, 7, 8, 6, -1, 9, 4, 0 };
//	SelectSort(a, sizeof(a) / sizeof(int));
//	PrintArray(a, sizeof(a) / sizeof(int));
//}

void BubbleSort(int* a, int n) {
	for (int i = 0; i < n - 1; ++i) //n个数的数列总共扫描n-1次
	{
		for (int j = 0; j < n - 1 - i; ++j) //每一趟扫描到a[n-i-2]与a[n-i-1]比较为止结束
		{
			if (a[j] > a[j + 1]) //后一位数比前一位数小的话，就交换两个数的位置（升序）
			{
				swap(a[j], a[j + 1]);
			}
		}
	}
}

//void TestBubbleSort()
//{
//	int a[] = { 9, 3, 5, 2, 7, 8, 6, -1, 9, 4, 0 };
//	BubbleSort(a, sizeof(a) / sizeof(int));
//	PrintArray(a, sizeof(a) / sizeof(int));
//}
int Partition(int* arr, int low, int high) {
	int pivotkey = arr[low]; // 用序列的第一个元素作枢轴元素
	while (low < high) {// 从表的两端交替地向中间扫描
		// 将比枢轴元素小的元素移到低端
		while (low < high&&arr[high] >= pivotkey) --high;
		arr[low] = arr[high];
		// 将比枢轴元素大的元素移到高端
		while (low < high&&arr[low] <= pivotkey) ++low;
		arr[high] = arr[low];
	}
	arr[low] = pivotkey; // 枢轴元素到位
	return low; // 返回枢轴位置
}


void QuickSort(int* a, int low,int high) {
	if (low < high) {
		int pivotloc = Partition(a, low, high); // 划分子表操作，定位枢轴记录
		QuickSort(a, low, pivotloc - 1); // 对低子表递归排序
		QuickSort(a, pivotloc + 1, high); // 对高子表递归排序
	}
}

//void TestQuickSort() {
//	int a[] = { 3, 5, 2, 7, 8, 6, 1, 9, 4, 0 };
//	QuickSort(a, 0,sizeof(a) / sizeof(int)-1);
//	PrintArray(a, sizeof(a) / sizeof(int));
//}

void Merge(int *a,int *temp,int start,int mid,int end) {
	int i = start; 
	int j = mid + 1, k = start;
	while (i <= mid && j <= end) //两两比较将较小的并入
	{
		if (a[i] < a[j])
			temp[k] = a[i++];
		else
			temp[k] = a[j++];
		k++;
	}

	while (i <= mid)//将mid前剩余的并入
		temp[k++] = a[i++];

	while (j <= end)//将mid后剩余的并入
		temp[k++] = a[j++];
	
	// 拷贝回去
	for (int i = start; i <= end; ++i)
		a[i] = temp[i];
}
void _MergeSort(int* a, int* tmp,int left, int right)
{
	if (left >= right)
		return;

	int mid = (left + right) >> 1;
	// 假设 [left, mid]有序和[mid+1, right]有序
	// 那么我们就可以归并了
	_MergeSort(a, tmp,left, mid );
	_MergeSort(a, tmp,mid + 1, right);
	Merge(a, tmp, left, mid, right);
	// 归并
}

void MergeSort(int* a, int n)
{
	int* temp = (int*)malloc(sizeof(int) * n);
	_MergeSort(a, temp,0, n - 1);
	free(temp);
}

//void TestMergeSort()
//{
//	int a[] = { 10, 6, 7 ,1, 3, 9, 4, 2, 8 };
//	MergeSort(a, sizeof(a) / sizeof(int));
//	PrintArray(a, sizeof(a) / sizeof(int));
//}

// 测试排序的性能对比
void TestOP()
{	//设置一个随机数种子
	srand(time(0));
	//N代表数据规模
	const int N = 50000;
	int* a1 = new int[N];
	int* a2 = new int[N];
	int* a3 = new int[N];
	int* a4 = new int[N];
	int* a5 = new int[N];
	
	//5个数组一样，控制变量
	for (int i = 0; i < N; ++i)
	{
		a1[i] = rand();
		a2[i] = a1[i];
		a3[i] = a1[i];
		a4[i] = a1[i];
		a5[i] = a1[i];
	}
	//分别得到不同排序算法所需要的时间
	int begin1 = clock();
	InsertSort(a1, N);
	int end1 = clock();

	int begin2 = clock();
	SelectSort(a2, N);
	int end2 = clock();

	int begin3 = clock();
	BubbleSort(a3, N);
	int end3 = clock();

	int begin4 = clock();
	MergeSort(a4, N);
	int end4 = clock();

	int begin5 = clock();
	QuickSort(a5, 0, N - 1);
	int end5 = clock();

	//分别输出不同排序算法所需要的时间 
	cout<<"InsertSort:"<<(double)(end1 - begin1) / CLOCKS_PER_SEC *1000<< "ms" << endl;
	cout << "SelectSort:" << (double)(end2 - begin2) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "BubbleSort:" << (double)(end3 - begin3) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "MergeSort:" << (double)(end4 - begin4) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "QuickSort:" << (double)(end5 - begin5) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}

int main()
{
	TestOP();
	return 0;
}