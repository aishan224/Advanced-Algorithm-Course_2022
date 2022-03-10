/* ����˼���������� */
#include <iostream>
#include <vector>
using namespace std;

int num_count = 0;

void MergeAndCount(int array[], int left, int middle, int right) {
	int* temp = new int[right - left + 5]; //������žֲ��鲢��Ľ����֮����ԭ����
	int i = left, j = middle + 1;
	int k = 0;  // �궨temp���±��������

	while (i <= middle && j <= right) {
		if (array[i] <= array[j]) {
			temp[k++] = array[i++];
		}
		else {
			/* ��¼ÿ����(��)���й鲢ʱ�������� */
			num_count += middle - i + 1;  // ������������д���jλ�õ����ĸ�����
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

	/* ��temp���ź�������ݸ��ǵ�ԭarray�� */
	for (int index = 0; index < k; index++) {
		array[left++] = temp[index];
	}

	delete[] temp; //�����ʱ����
	temp = NULL;
}

void MergeSort(int array[], int left, int right) {
	if (left == right) {
		return;
	}
	int middle = (left + right) / 2;
	MergeSort(array, left, middle);             // �ݹ����߽��й鲢
	MergeSort(array, middle + 1, right);        // �ݹ���ұ߽��й鲢
	MergeAndCount(array, left, middle, right);  // �鲢
}

int main() {

	int num = 0;
	cout << "Please input the number of sequence: ";
	cin >> num;

	int* sequence = new int[num];  // ����Ϊnum�����飬������
	for (int i = 0; i < num; i++){
		cout << "please input sequence[" << i << "]: ";
		cin >> sequence[i];
	}
	
	cout << endl << "All inverse numbers are as follow: " << endl;
	MergeSort(sequence, 0, num - 1);  //ִ�й鲢
	cout << "The total number of inverse numbers is: " << num_count << endl;
	return 0;
}

