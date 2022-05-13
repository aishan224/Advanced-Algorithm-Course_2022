#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

#define MAX 20

int x[MAX][MAX] = {0};  // 哨兵设置情况
int y[MAX][MAX] = {0};  // 场馆被监视情况

int bestx[MAX][MAX] = {0}; // 记录最终哨兵放置的结果

int m, n;
int bestk;  //最终的最少的k
int k = 0;  //当前放置的哨兵数量

int t1, t2, redundancy; //用于计算剩余未监视的点所需哨兵数与bestk的关系进行剪枝
int t = 0;        //记录已经被监视的数目

int dx[] = { 0, 1, -1, 0, 0 };
int dy[] = { 0, 0, 0,  1, -1 };  //用来对y进行修改，表示上下左右四个位置被监视与取消监视的操作

ifstream ifile("input.txt");  //文件操作
ofstream ofile("output.txt");

/*当在(i, j)处设置哨兵的时候，更新放置和监视的状态*/
void updateState(int i, int j) { 
	x[i][j] = 1; //此处放置一个哨兵
	k++;

	/*对被监视区域进行扩充*/
	for (int z = 0; z <= 4; z++)     //原位置及周围被监视
	{
		int p = i + dx[z];
		int q = j + dy[z];
		y[p][q]++;
		if (y[p][q] == 1)  //第一次受监视则将记录被监视的数目的变量t自增1
			t++;
	}
}

/*与updateState功能相反*/
void restoreState(int i, int j) {
	x[i][j] = 0;
	k--;

	for (int z = 0; z <= 4; z++)
	{
		int p = i + dx[z];
		int q = j + dy[z];
		y[p][q]--;
		if (y[p][q] == 0)  //最后未被监视t-- 
			t--;
	}
}

/*回溯搜索*/
void search(int i, int j) {
	do
	{
		j++;
		if (j > n) {
			i++;
			j = 1;  //因为外围被填充了1，所以下标从1到m或n
		}
	} while (y[i][j]!=0 && i <= m);  //找到未被监视的第一个位置

	if (i > m) {
		if (k < bestk) {
			bestk = k;
			for (int i = 1; i <= m; i++) {
				for (int j = 1; j <= n; j++) {
					bestx[i][j] = x[i][j];
				}
			}
		}
	}
	// (t1 - t)/5 为剩余未监视的区域所需哨兵的下界，这个最小值加上以放置哨兵数k比当前的bestk大，则剪去返回
	if (k + (t1 - t) / 5 >= bestk)  
		return;
	if (i < m - 1 && (k + (t2 - t) / 5 >= bestk))
		return;

	if (i < m) {                //部署在结点p
		updateState(i + 1, j);
		search(i, j);
		restoreState(i + 1, j);
	}

	if (j < n && (y[i][j + 1] == 0)) {   //部署在结点q
		updateState(i, j);
		search(i, j);
		restoreState(i, j);
	}

	if (j < n && ((y[i][j + 1] == 0) && (y[i][j + 2] == 0))) {  //部署在结点r
		updateState(i, j + 1);
		search(i, j);
		restoreState(i, j + 1);
	}
}

void compute() {
	bestk = m * n / 3 + 2;  //若按照每行每列都无缝排满，数量上界为m*n/3+1，故将m*n/3+2作为上界
	
	redundancy = m / 4 + 1;  //冗余数的最小值
	if (m % 4 == 3) {     //根据不同行数，冗余值稍有不同，用来计算界。
		redundancy += 1;
	}
	else if (m % 4 == 2) {
		redundancy += 2;
	}

	t2 = m * n + redundancy + 4; //用作i<m-1时有额外冗余
	t1 = m * n + 4;

	/*对监视区域的外围进行填充，填充为1，表示被看守，便于处理边界情况*/
	for (int j = 0; j <= n + 1; j++) {
		y[0][j] = 1;
		y[m + 1][j] = 1;
	}
	for (int i = 0; i <= m + 1; i++) {
		y[i][0] = 1;
		y[i][n + 1] = 1;
	}
	search(1, 0);
}

void output() {
	ofile << bestk << endl;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			ofile << bestx[i][j] << " ";
		}
		ofile << endl;
	}
}


int main() {
	ifile >> m >> n; //从input.txt的第一行获取行数列数

	compute();

	//输出到output.txt
	output();

	return 0;
}