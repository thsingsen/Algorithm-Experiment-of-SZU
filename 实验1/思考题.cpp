#include<iostream>
#include<cstdio>
#include<time.h>
using namespace std;

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
int* countingSort(int arr[], int count, int max) {
    int index = 0;
    int* tmpArr = (int*)malloc(max * sizeof(int));
    int* result = (int*)malloc(max * sizeof(int));

    for (int k = 0; k < max; k++) {
        tmpArr[k] = 0;
    }

    for (int i = 0; i < count; i++) {
        tmpArr[arr[i]]++;
    }
    for (int j = 0; j < max; j++) {
        while (tmpArr[j]) {
            result[index++] = j;
            tmpArr[j]--;
        }
    }
    free(tmpArr);
    tmpArr = NULL;
    return result;
}
void PrintArray(int* a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}
// 测试快速或计数排序的性能
void TestOP()
{
	srand(time(0));
	const int N = 100000000;
	int* a = new int[N];

	for (int i = 0; i < N; ++i)
		a[i] = rand();

	int begin= clock();
    countingSort(a, N,32800);
	//QuickSort(a, 0, N - 1);
	int end = clock();

	cout<<"countingSort:"<<(double)(end - begin) / CLOCKS_PER_SEC *1000<< "ms" << endl;
	//cout << "QuickSort:" << (double)(end - begin) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}
int main() {
    TestOP();
    return 0;
}