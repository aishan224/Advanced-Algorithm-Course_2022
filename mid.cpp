#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

#define MAX 20

int x[MAX][MAX] = {0};  // �ڱ��������
int y[MAX][MAX] = {0};  // ���ݱ��������

int bestx[MAX][MAX] = {0}; // ��¼�����ڱ����õĽ��

int m, n;
int bestk;  //���յ����ٵ�k
int k = 0;  //��ǰ���õ��ڱ�����

int t1, t2, redundancy; //���ڼ���ʣ��δ���ӵĵ������ڱ�����bestk�Ĺ�ϵ���м�֦
int t = 0;        //��¼�Ѿ������ӵ���Ŀ

int dx[] = { 0, 1, -1, 0, 0 };
int dy[] = { 0, 0, 0,  1, -1 };  //������y�����޸ģ���ʾ���������ĸ�λ�ñ�������ȡ�����ӵĲ���

ifstream ifile("input.txt");  //�ļ�����
ofstream ofile("output.txt");

/*����(i, j)�������ڱ���ʱ�򣬸��·��úͼ��ӵ�״̬*/
void updateState(int i, int j) { 
	x[i][j] = 1; //�˴�����һ���ڱ�
	k++;

	/*�Ա����������������*/
	for (int z = 0; z <= 4; z++)     //ԭλ�ü���Χ������
	{
		int p = i + dx[z];
		int q = j + dy[z];
		y[p][q]++;
		if (y[p][q] == 1)  //��һ���ܼ����򽫼�¼�����ӵ���Ŀ�ı���t����1
			t++;
	}
}

/*��updateState�����෴*/
void restoreState(int i, int j) {
	x[i][j] = 0;
	k--;

	for (int z = 0; z <= 4; z++)
	{
		int p = i + dx[z];
		int q = j + dy[z];
		y[p][q]--;
		if (y[p][q] == 0)  //���δ������t-- 
			t--;
	}
}

/*��������*/
void search(int i, int j) {
	do
	{
		j++;
		if (j > n) {
			i++;
			j = 1;  //��Ϊ��Χ�������1�������±��1��m��n
		}
	} while (y[i][j]!=0 && i <= m);  //�ҵ�δ�����ӵĵ�һ��λ��

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
	// (t1 - t)/5 Ϊʣ��δ���ӵ����������ڱ����½磬�����Сֵ�����Է����ڱ���k�ȵ�ǰ��bestk�����ȥ����
	if (k + (t1 - t) / 5 >= bestk)  
		return;
	if (i < m - 1 && (k + (t2 - t) / 5 >= bestk))
		return;

	if (i < m) {                //�����ڽ��p
		updateState(i + 1, j);
		search(i, j);
		restoreState(i + 1, j);
	}

	if (j < n && (y[i][j + 1] == 0)) {   //�����ڽ��q
		updateState(i, j);
		search(i, j);
		restoreState(i, j);
	}

	if (j < n && ((y[i][j + 1] == 0) && (y[i][j + 2] == 0))) {  //�����ڽ��r
		updateState(i, j + 1);
		search(i, j);
		restoreState(i, j + 1);
	}
}

void compute() {
	bestk = m * n / 3 + 2;  //������ÿ��ÿ�ж��޷������������Ͻ�Ϊm*n/3+1���ʽ�m*n/3+2��Ϊ�Ͻ�
	
	redundancy = m / 4 + 1;  //����������Сֵ
	if (m % 4 == 3) {     //���ݲ�ͬ����������ֵ���в�ͬ����������硣
		redundancy += 1;
	}
	else if (m % 4 == 2) {
		redundancy += 2;
	}

	t2 = m * n + redundancy + 4; //����i<m-1ʱ�ж�������
	t1 = m * n + 4;

	/*�Լ����������Χ������䣬���Ϊ1����ʾ�����أ����ڴ���߽����*/
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
	ifile >> m >> n; //��input.txt�ĵ�һ�л�ȡ��������

	compute();

	//�����output.txt
	output();

	return 0;
}