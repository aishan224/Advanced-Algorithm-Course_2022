#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const int INF = 1 << 30;  //相对于此问题设置一个较大数作为无穷大
int delta;

void print(char *map, int lenx, int leny) {  //打印地图
	for (int i = 0; i < lenx; i++) {
		for (int j = 0; j < leny; j++) {
			cout << map[i*leny+j] << " ";
		}
		cout << endl;
	}
}
void print2(int* weights, int a_nums) {   //打印权重矩阵
	for (int i = 1; i <= a_nums; i++) {
		for (int j = 1; j <= a_nums; j++) {
			cout << weights[i * a_nums + j] << " ";
		}
		cout << endl;
	}
}

//获取蚂蚁(洞穴)的数量，即作为权重矩阵的行数和列数 用变量a_nums记录
int get_a_nums_from_map(char* map, int row_nums, int col_nums) {  
	int count = 0;
	for (int i = 0; i < row_nums; i++) {
		for (int j = 0; j < col_nums; j++) {
			if (map[i * col_nums + j] == 'a') {
				count++;
			}
		}
	}
	return count;
}

// 暴力地从地图中得到权重矩阵: 从前到后依次扫描a和H
void get_weights_from_map(char* map, int row_nums, int col_nums, int a_nums, int* weights) {
	int row_cur = 1, col_cur = 1;          //从[1][1]开始
	for (int i = 0; i < row_nums; i++) 
		for (int j = 0; j < col_nums; j++) 
			if (map[i * col_nums + j] == 'a') 
				for (int m = 0; m < row_nums; m++) 
					for (int n = 0; n < col_nums; n++) 
						if (map[m * col_nums + n] == 'H') {
							weights[row_cur * a_nums + col_cur] = -(abs(m - i) + abs(n - j));
							col_cur++;
							if ((col_cur - 1) % a_nums == 0) {
								col_cur = 1;
								row_cur++;
							}
						}
}

// 参数a为要寻找增广路径的“起始点”的蚂蚁
bool find_by_bfs(int* weights, int col_num, bool* visit_a, bool* visit_H, int* label_a, int* label_H, int* match, int a) {
	visit_a[a] = 1;
	for (int h = 1; h <= col_num; h++) {
		if (!visit_H[h]) {   //h不在交错路中并且a与h的边在相等子图中（即下式取等
			if (label_a[a] + label_H[h] - weights[a * col_num + h] == 0) { 
				visit_H[h] = 1;
				if (!match[h] || find_by_bfs(weights, col_num, visit_a, visit_H, label_a, label_H, match, match[h])) { //递归找增广链
					match[h] = a;
					return 1;
				}
			}
			else {
				delta = min(delta, label_a[a] + label_H[h] - weights[a * col_num + h]); //找不到则需要放宽条件，减小蚂蚁的顶标，增大洞穴的顶标
			}
		}
	}
	return 0;
}

int KM(int* weights, int col_num, bool* visit_a, bool* visit_H, int* label_a, int* label_H, int* match) {
	memset(match, 0, sizeof(int) * (col_num + 1));   //初始化match为全0，这也就要求权重矩阵weights从1开始
	
	//初始化顶标，对于H，全为0；对于a，设置为所有到其他H的最大值
	for (int i = 1; i <= col_num; i++) {  
		label_a[i] = -INF;
		label_H[i] = 0;
		for (int j = 1; j <= col_num; j++) {
			label_a[i] = max(label_a[i], weights[i * col_num + j]);
		}
	}
	for (int a = 1; a <= col_num; a++) {
		while (true) {
			memset(visit_a, 0, sizeof(bool) * (col_num + 1));
			memset(visit_H, 0, sizeof(bool) * (col_num + 1));
			delta = INF;

			if (find_by_bfs(weights, col_num, visit_a, visit_H, label_a, label_H, match, a)) 
				break;   //找到了增广路，跳出继续寻找下一个

			// 减小增光路中的蚂蚁的顶标，增大洞穴的顶标
			for (int j = 1; j <= col_num; j++) {
				if (visit_a[j])
					label_a[j] -= delta;
				if (visit_H[j])
					label_H[j] += delta;
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= col_num; i++) {
		ans += weights[match[i] * col_num + i];
	}
	return -ans;
}

void test1() {
	char map[7][8] = { {'.','.','.','H','.','.','.','.'},
					   {'.','.','.','H','.','.','.','.'},
					   {'.','.','.','H','.','.','.','.'},
					   {'a','a','a','H','a','a','a','a'},
					   {'.','.','.','H','.','.','.','.'},
					   {'.','.','.','H','.','.','.','.'},
					   {'.','.','.','H','.','.','.','.'} };

	int a_nums = get_a_nums_from_map(*map, 7, 8);
	//cout << a_nums << endl;
	int* weights = (int*)malloc(pow(a_nums+1, 2) * sizeof(int)); 
	get_weights_from_map(*map, 7, 8, a_nums, weights);

	bool* visit_a = (bool*)malloc(pow(a_nums+1, 1) * sizeof(bool));  //记录标记与否
	bool* visit_H = (bool*)malloc(pow(a_nums+1, 1) * sizeof(bool));

	int* label_a = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));  //记录顶标
	int* label_H = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));

	int* match = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));  //记录与H匹配的a

	cout << "============================" << endl;
	cout <<"  Test1: " << endl << "地图为：" << endl;
	print(*map, 7, 8);
	cout << endl << "权重矩阵为：" << endl;
	print2(weights, a_nums);
	cout << endl << "最少能耗为：" << KM(weights, a_nums, visit_a, visit_H, label_a, label_H, match) << endl;
	cout << "============================" << endl << endl;;
}

void test2() {
	char map[5][5] = { {'H','H','.','.','a'},
						{'.','.','.','.','.'},
						{'.','.','.','.','.'},
						{'.','.','.','.','.'},
						{'a','a','.','.','H'} };
	int a_nums = get_a_nums_from_map(*map, 5, 5);
	//cout << a_nums << endl;
	int* weights = (int*)malloc(pow(a_nums + 1, 2) * sizeof(int));
	get_weights_from_map(*map, 5, 5, a_nums, weights);

	bool* visit_a = (bool*)malloc(pow(a_nums + 1, 1) * sizeof(bool));  //记录标记与否
	bool* visit_H = (bool*)malloc(pow(a_nums + 1, 1) * sizeof(bool));

	int* label_a = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));  //记录顶标
	int* label_H = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));

	int* match = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));  //记录与H匹配的a

	cout << "============================" << endl;
	cout << "  Test2: " << endl << "地图为：" << endl;
	print(*map, 5, 5);
	cout << endl << "权重矩阵为：" << endl;
	print2(weights, a_nums);
	cout << endl << "最少能耗为：" << KM(weights, a_nums, visit_a, visit_H, label_a, label_H, match) << endl;
	cout << "============================" << endl << endl;
}

void test3() {
	/*char map[7][8] = { {'.','.','.','.','H','.','.','a'},
					   {'.','a','.','H','.','.','.','.'},
					   {'.','.','.','.','.','.','.','.'},
					   {'a','.','.','H','a','.','.','a'},
					   {'.','.','.','.','.','.','.','.'},
					   {'.','.','.','H','.','.','H','.'},
					   {'.','.','.','.','.','.','.','.'} };*/
	char map[7][8] = { {'.','.','.','.','.','H','.','a'},
					   {'.','a','.','H','.','.','.','.'},
					   {'.','.','.','.','.','.','H','.'},
					   {'a','a','.','.','a','.','.','a'},
					   {'.','.','.','.','.','.','.','.'},
					   {'.','H','.','.','.','.','H','.'},
					   {'.','.','.','.','H','.','.','.'} };
	int a_nums = get_a_nums_from_map(*map, 7, 8);
	//cout << a_nums << endl;
	int* weights = (int*)malloc(pow(a_nums + 1, 2) * sizeof(int));
	get_weights_from_map(*map, 7, 8, a_nums, weights);

	bool* visit_a = (bool*)malloc(pow(a_nums + 1, 1) * sizeof(bool));  //记录标记与否
	bool* visit_H = (bool*)malloc(pow(a_nums + 1, 1) * sizeof(bool));

	int* label_a = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));  //记录顶标
	int* label_H = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));

	int* match = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));  //记录与H匹配的a

	cout << "============================" << endl;
	cout << "  Test3: " << endl << "地图为：" << endl;
	print(*map, 7, 8);
	cout << endl << "权重矩阵为：" << endl;
	print2(weights, a_nums);
	cout << endl << "最少能耗为：" << KM(weights, a_nums, visit_a, visit_H, label_a, label_H, match) << endl;
	cout << "============================" << endl << endl;;
}

int main() {

	test1();
	test2();
	test3();

	return 0;
}


