//#include <iostream>
//#include <cstring>
//#include <cmath>
//using namespace std;
//
//const int maxn = 100;
//const int INF = 1 << 30;
//
//char map[7][8] = { {'.','.','.','.','H','.','.','a'},
//				   {'.','a','.','H','.','.','.','.'},
//				   {'.','.','.','.','.','.','.','.'},
//				   {'a','.','a','H','a','.','.','a'},
//				   {'.','.','.','.','.','.','.','.'},
//				   {'.','.','.','H','.','.','H','.'},
//				   {'.','.','.','.','H','.','.','.'} };
//
//int weights[maxn][maxn];  //从map中获得权重
//int label_a[maxn], label_H[maxn];   //记录顶标
//int match[maxn] = {0};  //记录与H匹配的a，初始化为0,表示不与任何匹配，weights中的数据从下标1开始
//
//bool visit_a[maxn], visit_H[maxn];  //记录标记与否
//
//int delta;  //d
//
//int get_a_nums_from_map(char* map, int row_nums, int col_nums);  //函数声明
//int get_weights_from_map(char* map, int row_nums, int col_nums, int a_nums, int weights[maxn][maxn]);
//
//int a_nums = get_a_nums_from_map(*map, 7, 8);
//int _ = get_weights_from_map(*map, 7, 8, a_nums, weights);
//
//void print(char* map, int lenx, int leny) {
//	for (int i = 0; i < lenx; i++) {
//		for (int j = 0; j < leny; j++) {
//			cout << map[i * leny + j] << " ";
//		}
//		cout << endl;
//	}
//}
//void print2(int weights[maxn][maxn], int a_nums) {
//	for (int i = 1; i <= a_nums; i++) {
//		for (int j = 1; j <= a_nums; j++) {
//			cout << weights[i][j] << " ";
//		}
//		cout << endl;
//	}
//}
//
//int get_a_nums_from_map(char* map, int row_nums, int col_nums) {
//	int count = 0;
//	for (int i = 0; i < row_nums; i++) {
//		for (int j = 0; j < col_nums; j++) {
//			if (map[i * col_nums + j] == 'a') {
//				count++;
//			}
//		}
//	}
//	return count;
//}
//
//int get_weights_from_map(char* map, int row_nums, int col_nums, int a_nums, int weights[maxn][maxn]) {
//	int row_cur = 1, col_cur = 1;
//	for (int i = 0; i < row_nums; i++) 
//		for (int j = 0; j < col_nums; j++) 
//			if (map[i * col_nums + j] == 'a')
//				for (int m = 0; m < row_nums; m++) 
//					for (int n = 0; n < col_nums; n++) 
//						if (map[m * col_nums + n] == 'H') {
//							weights[row_cur][col_cur++] = -(abs(m - i) + abs(n - j));
//							if ((col_cur-1) % a_nums == 0) {
//								col_cur = 1;
//								row_cur++;
//							}
//						}
//	return 0;
//}
//
//void set_false(bool* a, int col_num) {
//	for (int i = 0; i < col_num; i++) {
//		a[i] = 0;
//	}
//}
//
////bool find_by_bfs(int* weights, int col_num, bool* visit_a, bool* visit_H, int* label_a, int* label_H, int* match, int a) {
////	// a为要寻找增广路径的“起始点”的蚂蚁  其他相关数据
////	visit_a[a] = 1;
////	for (int h = 0; h < col_num; h++) {
////		if (!visit_H[h] && label_a[a] + label_H[h] == weights[a * col_num + h]) { 
////			visit_H[h] = 1;
////	
////			//如果h还未匹配或者从h的match还能另外找到一条匹配边
////			if (match[h] == -1 || find_by_bfs(weights, col_num, visit_a, visit_H, label_a, label_H, match, match[h])) { 
////				match[h] = a;
////				return 1;
////			}
////		}
////	}
////	return 0;
////}
////	
////int KM(int* weights, int col_num, bool* visit_a, bool* visit_H, int* label_a, int* label_H, int* match) {
////	memset(match, 0, sizeof(int) * col_num);
////	
////	/*for (int i = 0; i < col_num; i++) {
////		label_a[i] = -(1 << 30);
////		label_H[i] = 0;
////		for (int j = 0; j < col_num; j++) {
////			label_a[i] = max(label_a[i], weights[i * col_num + j]);
////		}
////	}*/
////		
////	for (int a = 0; a < col_num; a++) {
////		while (1){
////			/*set_false(visit_a, col_num);
////			set_false(visit_H, col_num);*/
////			memset(visit_a, 0, sizeof(bool) * col_num);
////			memset(visit_H, 0, sizeof(bool) * col_num);
////			delta = 1 << 30;
////			if (find_by_bfs(weights, col_num, visit_a, visit_H, label_a, label_H, match, a))
////				break;
////			else {
////				for (int i = 0; i < col_num; i++) {
////					if (visit_a[i]) {
////						for (int j = 0; j < col_num; j++) {
////							if (visit_H[j]) {
////								delta = min(delta, label_a[i] + label_H[j] - weights[i * col_num + j]);
////							}
////						}
////					}
////				}
////	
////				for (int i = 0; i < col_num; i++) {
////					if (visit_a[i])
////						label_a[i] -= delta;
////				}
////	
////				for (int j = 0; j < col_num; j++) {
////					if (visit_H[j])
////						label_H[j] += delta;
////				}
////			}
////		}
////	}
////	
////	int ans = 0; 
////	for (int i = 0; i < col_num; i++) {
////		ans += weights[match[i] * col_num + i];
////	}
////	ans = -ans;
////	return ans;
////}
//
//bool find_by_bfs(int a) {
//	visit_a[a] = 1;
//	for (int h = 1; h <= a_nums; h++) {
//		if (!visit_H[h]) {
//			if (label_a[a] + label_H[h] - weights[a][h] == 0) {
//				visit_H[h] = 1;
//				if (!match[h] || find_by_bfs(match[h])) {
//					match[h] = a;
//					return 1;
//				}
//			}
//			else {
//				delta = min(delta, label_a[a] + label_H[h] - weights[a][h]);
//			}
//		}
//	}
//	return 0;
//}
//
//int KM() {
//	//memset(match, 0, sizeof(int) * a_nums);
//	for (int i = 1; i <= a_nums; i++) {
//		label_a[i] = -(1 << 30);
//		label_H[i] = 0;
//		for (int j = 1; j <= a_nums; j++) {
//			label_a[i] = max(label_a[i], weights[i][j]);
//		}
//	}
//	for (int a = 1; a <= a_nums; a++) {
//		while (true) {
//			memset(visit_a, 0, sizeof(visit_a));
//			memset(visit_H, 0, sizeof(visit_a));
//			/*set_false(visit_a, col_num);
//			set_false(visit_H, col_num);*/
//			/*for (int i = 0; i < col_num; i++) {
//				visit_a[i] = 0;
//			}
//			for (int i = 0; i < col_num; i++) {
//				visit_H[i] = 0;
//			}*/
//
//
//			delta = INF;
//			if (find_by_bfs(a))
//				break;
//			for (int j = 1; j <= a_nums; j++) {
//				if (visit_a[j])
//					label_a[j] -= delta;
//				if (visit_H[j])
//					label_H[j] += delta;
//			}
//		}
//	}
//	int ans = 0;
//	for (int i = 1; i <= a_nums; i++) {
//		ans += weights[match[i]][i];
//	}
//	return -ans;
//}
//
////void test1() {
////	/*char map[7][8] = { {'.','.','.','H','.','.','.','.'},
////					   {'.','.','.','H','.','.','.','.'},
////					   {'.','.','.','H','.','.','.','.'},
////					   {'a','a','a','H','a','a','a','a'},
////					   {'.','.','.','H','.','.','.','.'},
////					   {'.','.','.','H','.','.','.','.'},
////					   {'.','.','.','H','.','.','.','.'} };*/
////	char map[7][8] = { {'.','.','.','.','H','.','.','a'},
////					   {'.','a','.','H','.','.','.','.'},
////					   {'.','.','.','.','.','.','.','.'},
////					   {'a','.','.','H','a','.','.','a'},
////					   {'.','.','.','.','.','.','.','.'},
////					   {'.','.','.','H','.','.','H','.'},
////					   {'.','.','.','.','.','.','.','.'} };
////
////
////	int count = get_a_nums_from_map(*map, 7, 8);
////	cout << count << endl;
////	int* weights = (int*)malloc(pow(count, 2) * sizeof(int));
////	get_weights_from_map(*map, 7, 8, weights);
////
////	bool* visit_a = (bool*)malloc(count * sizeof(bool));  //记录标记与否
////	bool* visit_H = (bool*)malloc(count * sizeof(bool));
////
////	int* label_a = (int*)malloc(count * sizeof(int));  //记录顶标
////	int* label_H = (int*)malloc(count * sizeof(int));
////
////	int* match = (int*)malloc(count * sizeof(int));  //记录与H匹配的a
////
////	print2(weights, count, count);
////	cout << KM(weights, count, visit_a, visit_H, label_a, label_H, match);
////
////	//print(*map2, 5, 5);
////}
//
//void test2() {
//	char map[5][5] = { {'H','H','.','.','a'},
//						{'.','.','.','.','.'},
//						{'.','.','.','.','.'},
//						{'.','.','.','.','.'},
//						{'a','a','.','.','H'} };
//
//}
//
//int main() {
//
//	//test1();
//	print2(weights, a_nums);
//	cout << KM();
//	return 0;
//}
//
//
