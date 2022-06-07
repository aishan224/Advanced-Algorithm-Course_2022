#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const int INF = 1 << 30;  //����ڴ���������һ���ϴ�����Ϊ�����
int delta;

void print(char *map, int lenx, int leny) {  //��ӡ��ͼ
	for (int i = 0; i < lenx; i++) {
		for (int j = 0; j < leny; j++) {
			cout << map[i*leny+j] << " ";
		}
		cout << endl;
	}
}
void print2(int* weights, int a_nums) {   //��ӡȨ�ؾ���
	for (int i = 1; i <= a_nums; i++) {
		for (int j = 1; j <= a_nums; j++) {
			cout << weights[i * a_nums + j] << " ";
		}
		cout << endl;
	}
}

//��ȡ����(��Ѩ)������������ΪȨ�ؾ�������������� �ñ���a_nums��¼
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

// �����شӵ�ͼ�еõ�Ȩ�ؾ���: ��ǰ��������ɨ��a��H
void get_weights_from_map(char* map, int row_nums, int col_nums, int a_nums, int* weights) {
	int row_cur = 1, col_cur = 1;          //��[1][1]��ʼ
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

// ����aΪҪѰ������·���ġ���ʼ�㡱������
bool find_by_bfs(int* weights, int col_num, bool* visit_a, bool* visit_H, int* label_a, int* label_H, int* match, int a) {
	visit_a[a] = 1;
	for (int h = 1; h <= col_num; h++) {
		if (!visit_H[h]) {   //h���ڽ���·�в���a��h�ı��������ͼ�У�����ʽȡ��
			if (label_a[a] + label_H[h] - weights[a * col_num + h] == 0) { 
				visit_H[h] = 1;
				if (!match[h] || find_by_bfs(weights, col_num, visit_a, visit_H, label_a, label_H, match, match[h])) { //�ݹ���������
					match[h] = a;
					return 1;
				}
			}
			else {
				delta = min(delta, label_a[a] + label_H[h] - weights[a * col_num + h]); //�Ҳ�������Ҫ�ſ���������С���ϵĶ��꣬����Ѩ�Ķ���
			}
		}
	}
	return 0;
}

int KM(int* weights, int col_num, bool* visit_a, bool* visit_H, int* label_a, int* label_H, int* match) {
	memset(match, 0, sizeof(int) * (col_num + 1));   //��ʼ��matchΪȫ0����Ҳ��Ҫ��Ȩ�ؾ���weights��1��ʼ
	
	//��ʼ�����꣬����H��ȫΪ0������a������Ϊ���е�����H�����ֵ
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
				break;   //�ҵ�������·����������Ѱ����һ��

			// ��С����·�е����ϵĶ��꣬����Ѩ�Ķ���
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

	bool* visit_a = (bool*)malloc(pow(a_nums+1, 1) * sizeof(bool));  //��¼������
	bool* visit_H = (bool*)malloc(pow(a_nums+1, 1) * sizeof(bool));

	int* label_a = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));  //��¼����
	int* label_H = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));

	int* match = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));  //��¼��Hƥ���a

	cout << "============================" << endl;
	cout <<"  Test1: " << endl << "��ͼΪ��" << endl;
	print(*map, 7, 8);
	cout << endl << "Ȩ�ؾ���Ϊ��" << endl;
	print2(weights, a_nums);
	cout << endl << "�����ܺ�Ϊ��" << KM(weights, a_nums, visit_a, visit_H, label_a, label_H, match) << endl;
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

	bool* visit_a = (bool*)malloc(pow(a_nums + 1, 1) * sizeof(bool));  //��¼������
	bool* visit_H = (bool*)malloc(pow(a_nums + 1, 1) * sizeof(bool));

	int* label_a = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));  //��¼����
	int* label_H = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));

	int* match = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));  //��¼��Hƥ���a

	cout << "============================" << endl;
	cout << "  Test2: " << endl << "��ͼΪ��" << endl;
	print(*map, 5, 5);
	cout << endl << "Ȩ�ؾ���Ϊ��" << endl;
	print2(weights, a_nums);
	cout << endl << "�����ܺ�Ϊ��" << KM(weights, a_nums, visit_a, visit_H, label_a, label_H, match) << endl;
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

	bool* visit_a = (bool*)malloc(pow(a_nums + 1, 1) * sizeof(bool));  //��¼������
	bool* visit_H = (bool*)malloc(pow(a_nums + 1, 1) * sizeof(bool));

	int* label_a = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));  //��¼����
	int* label_H = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));

	int* match = (int*)malloc(pow(a_nums + 1, 1) * sizeof(int));  //��¼��Hƥ���a

	cout << "============================" << endl;
	cout << "  Test3: " << endl << "��ͼΪ��" << endl;
	print(*map, 7, 8);
	cout << endl << "Ȩ�ؾ���Ϊ��" << endl;
	print2(weights, a_nums);
	cout << endl << "�����ܺ�Ϊ��" << KM(weights, a_nums, visit_a, visit_H, label_a, label_H, match) << endl;
	cout << "============================" << endl << endl;;
}

int main() {

	test1();
	test2();
	test3();

	return 0;
}


