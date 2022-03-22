/*��̬�滮�����ά���·��*/

#include <iostream>
using namespace std;
#define N 4  //��ά����������

typedef struct Node {
	int value;     //��¼��ǰλ��dpֵ
	int pre_flag;  //��¼��ǰλ����������������  0��ʾ������1��ʾ�����ϣ�-1��ʾ�����Ͻ�Ԫ��
}DP_Node;

//�ܹ����ݴ�������array����ֵ��¼����NodeΪԪ�صĶ�ά������
void dp_func(int array[N][N], int rowNum, int colNum) {  // rowNum��N��colNumҲ��N
	DP_Node dp_array[N][N];
	
	//��һ��Ԫ�ص�dp·������Ϊԭ����ĵ�һ��Ԫ��
	dp_array[0][0].value = array[0][0];
	dp_array[0][0].pre_flag = -1;

	for (int i = 1; i < rowNum; i++) { //��һ�г�ʼ��
		dp_array[i][0].value = array[i][0] + dp_array[i - 1][0].value;
		dp_array[i][0].pre_flag = 1;  // 1��ʾ���������
	}
	for (int j = 1; j < colNum; j++) { //��һ�г�ʼ��
		dp_array[0][j].value = array[0][j] + dp_array[0][j - 1].value;
		dp_array[0][j].pre_flag = 0;  // 0��ʾ�������
	}
	
	for (int i = 1; i < rowNum; i++) {
		for (int j = 1; j < colNum; j++){
			/*�������ı���ߵ�С*/
			if (dp_array[i - 1][j].value < dp_array[i][j - 1].value) {  
				dp_array[i][j].value = dp_array[i - 1][j].value + array[i][j]; //����С��
				dp_array[i][j].pre_flag = 1; //�����С�����Դ����������flag��Ϊ1
			}
			else { //�������߹��� //�����ͬ Ҳ�������
				dp_array[i][j].value = dp_array[i][j - 1].value + array[i][j]; //����С��
				dp_array[i][j].pre_flag = 0; //��ߵ�С�����Դ���߹�����flag��Ϊ0
			}
		}
	}
	/*���ϾͰ�dp_array������ˣ��������Ӻ���ǰ����flag��·��*/
	int rows[7] = { N-1 }; //�������д������ߵ����²�������ྭ��7����
	int cols[7] = { N-1 };
	int position = 1;

	int cur_row = N-1;
	int cur_col = N-1;
	
	while (dp_array[cur_row][cur_col].pre_flag != -1) {
		if (dp_array[cur_row][cur_col].pre_flag == 1) {  //��������
			rows[position] = --cur_row;
			cols[position] = cur_col;
		}
		else if (dp_array[cur_row][cur_col].pre_flag == 0) {  //�������
			rows[position] = cur_row;
			cols[position] = --cur_col;
		}
		position++;
	}

	cout << " ��������Ϊ��" << endl;
	for (int i = position-1; i >= 0; i--) {
		cout << " <" << rows[i]+1 << ", " << cols[i]+1 << ">  ";
	}
	cout << endl;
	cout << endl << " ��Ӧλ��Ԫ��Ϊ��" << endl;
	for (int i = position - 1; i >= 0; i--) {
		cout << "    " << array[rows[i]][cols[i]] << "    ";
	}
	cout << endl;
	cout << endl << " ��Ӧÿ��λ�����·������Ϊ��" << endl;
	for (int i = position - 1; i >= 0; i--) {
		cout << "    " << dp_array[rows[i]][cols[i]].value << "    ";
	}
	cout << endl;
}


int main() {

	int array[4][4] = { {1,3,5,9}, {8,1,3,4}, {5,0,6,1}, {8,8,4,0} };
	//int array[4][4] = { {3,1,4,6}, {1,6,7,9}, {2,5,3,2}, {1,3,0,5} };
	
	dp_func(array, 4, 4);

	return 0;
}