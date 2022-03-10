/* 分治思想求逆序数 */
#include <iostream>
#include <vector>
using namespace std;

int num_count = 0;

void MergeAndCount(int array[], int left, int middle, int right) {
	int* temp = new int[right - left + 5]; //用来存放局部归并后的结果，之后赋予原数组
	int i = left, j = middle + 1;
	int k = 0;  // 标定temp的下标和数量。

	while (i <= middle && j <= right) {
		if (array[i] <= array[j]) {
			temp[k++] = array[i++];
		}
		else {
			/* 记录每两个(子)序列归并时的逆序数 */
			num_count += middle - i + 1;  // 加上左半中所有大于j位置的数的个数。
			for (int m = i; m <= middle; m++) {
				cout << "<" << array[m] << ", " << array[j] << ">" << endl;
			}

			temp[k++] = array[j++];
			
		}
	}
	
	if (i <= middle){
	    while (i <= middle)
	        temp[k++] = array[i++];
	}
	else
	{
	    while (j <= right)
	        temp[k++] = array[j++];
	}

	/* 将temp中排好序的数据覆盖到原array中 */
	for (int index = 0; index < k; index++) {
		array[left++] = temp[index];
	}

	delete[] temp; //清空临时数组
	temp = NULL;
}

void MergeSort(int array[], int left, int right) {
	if (left == right) {
		return;
	}
	int middle = (left + right) / 2;
	MergeSort(array, left, middle);             // 递归对左边进行归并
	MergeSort(array, middle + 1, right);        // 递归对右边进行归并
	MergeAndCount(array, left, middle, right);  // 归并
}

int main() {

	int num = 0;
	cout << "Please input the number of sequence: ";
	cin >> num;

	int* sequence = new int[num];  // 长度为num的数组，存序列
	for (int i = 0; i < num; i++){
		cout << "please input sequence[" << i << "]: ";
		cin >> sequence[i];
	}
	
	cout << endl << "All inverse numbers are as follow: " << endl;
	MergeSort(sequence, 0, num - 1);  //执行归并
	cout << "The total number of inverse numbers is: " << num_count << endl;
	return 0;
}

