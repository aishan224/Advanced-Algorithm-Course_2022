/*动态规划计算二维最短路径*/

#include <iostream>
using namespace std;
#define N 4  //二维数组行列数

typedef struct Node {
	int value;     //记录当前位置dp值
	int pre_flag;  //记录当前位置来自左还是来自上  0表示来自左，1表示来自上，-1表示最左上角元素
}DP_Node;

//能够根据传过来的array，将值记录到以Node为元素的二维数组中
void dp_func(int array[N][N], int rowNum, int colNum) {  // rowNum是N，colNum也是N
	DP_Node dp_array[N][N];
	
	//第一个元素的dp路径复制为原数组的第一个元素
	dp_array[0][0].value = array[0][0];
	dp_array[0][0].pre_flag = -1;

	for (int i = 1; i < rowNum; i++) { //第一列初始化
		dp_array[i][0].value = array[i][0] + dp_array[i - 1][0].value;
		dp_array[i][0].pre_flag = 1;  // 1表示从上面过来
	}
	for (int j = 1; j < colNum; j++) { //第一行初始化
		dp_array[0][j].value = array[0][j] + dp_array[0][j - 1].value;
		dp_array[0][j].pre_flag = 0;  // 0表示从左边来
	}
	
	for (int i = 1; i < rowNum; i++) {
		for (int j = 1; j < colNum; j++){
			/*如果上面的比左边的小*/
			if (dp_array[i - 1][j].value < dp_array[i][j - 1].value) {  
				dp_array[i][j].value = dp_array[i - 1][j].value + array[i][j]; //加上小的
				dp_array[i][j].pre_flag = 1; //上面的小，所以从上面过来，flag设为1
			}
			else { //否则从左边过来 //如果相同 也优先左边
				dp_array[i][j].value = dp_array[i][j - 1].value + array[i][j]; //加上小的
				dp_array[i][j].pre_flag = 0; //左边的小，所以从左边过来，flag设为0
			}
		}
	}
	/*以上就把dp_array填充完了，接下来从后往前根据flag找路径*/
	int rows[7] = { N-1 }; //四行四列从左上走到左下不返回最多经过7个点
	int cols[7] = { N-1 };
	int position = 1;

	int cur_row = N-1;
	int cur_col = N-1;
	
	while (dp_array[cur_row][cur_col].pre_flag != -1) {
		if (dp_array[cur_row][cur_col].pre_flag == 1) {  //从上面来
			rows[position] = --cur_row;
			cols[position] = cur_col;
		}
		else if (dp_array[cur_row][cur_col].pre_flag == 0) {  //从左边来
			rows[position] = cur_row;
			cols[position] = --cur_col;
		}
		position++;
	}

	cout << " 坐标序列为：" << endl;
	for (int i = position-1; i >= 0; i--) {
		cout << " <" << rows[i]+1 << ", " << cols[i]+1 << ">  ";
	}
	cout << endl;
	cout << endl << " 对应位置元素为：" << endl;
	for (int i = position - 1; i >= 0; i--) {
		cout << "    " << array[rows[i]][cols[i]] << "    ";
	}
	cout << endl;
	cout << endl << " 对应每个位置最短路径长度为：" << endl;
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