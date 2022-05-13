
#include <iostream>
using namespace std;

int main() {

	cout << "asd" << endl;
	return 0;
}

main部分
#include <iostream>
#include <cmath>
using namespace std;
#define N 4

int queen[N] = { 0 };
int count_num = 0;

void display() {
	cout << " ( ";
	for (int i = 0; i < N; i++) {
		cout << queen[i]+1 << " " ;
	}
	cout << ")" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < queen[i]; j++) {
			cout << "0 ";
		}
		cout << "1 ";
		for (int j = queen[i]+1; j < N; j++) {
			cout << "0 ";
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
}

int isPlacedable(int n) {
	for (int i = 0; i < n; i++) { //跟前面的行已放的皇后进行判断
		if ((queen[n] == queen[i]) || abs(queen[n] - queen[i]) == abs(n - i)) {
			return 0;
		}
	}
	return 1;
}

void reBack(int n) {  //为第n个皇后找位置：即行号
	for (int i = 0; i < N; i++) {  //每个皇后都搜索所有四个位置
		queen[n] = i;  //第n行的皇后遍历每个i，
		if (isPlacedable(n)) {  //传n，判断这一行的皇后能不能放下，在判断函数里也是比较queen[n]的值
			if (n == N - 1) {
				display();
				count_num++;
			}
			else {
				reBack(n + 1);
			}
			
		}
	}
}

int main() {

	reBack(0);

	cout << "Total Num: " << count_num << endl;

}

其他
#include <stdio.h>
#define N 20       //皇后的数量
int q[N];          //各行皇后所在的列
int count = 0;     //统计N皇后问题解的个数

//输出 N 皇后问题的解决方案
void print(int n)
{
    int i, j;
    count++;
    printf("第%d个解：\n", count);
    for (i = 1; i <= n; i++)        //行
    {
        for (j = 1; j <= n; j++)   //列
        {
            if (q[i] != j)
                printf("x");
            else
                printf("Q");
        }
        printf("\n");
    }
    printf("\n");
}
//检验第k行第j列上是否可以摆放皇后
int isSafe(int k, int j)
{
    int i;
    for (i = 1; i < k; i++) {
        //如果有其它皇后位置同一列上，或者位于该位置的斜线位置上，则该位置无法使用
        if (q[i] == j || abs(i - k) == abs(q[i] - j))
            return 0;
    }
    return 1;
}
//放置皇后到棋盘上
void n_queens(int k, int n)
{
    int j;
    if (k > n)     //递归的出口
        print(n);
    else
    {
        for (j = 1; j <= n; j++)   //试探第k行的每一列，找到符合要求的列
        {
            if (isSafe(k, j))
            {
                q[k] = j;
                n_queens(k + 1, n);  //在确认第 k 行皇后位置的前提下，继续测试下一行皇后的位置
            }
        }
    }
}

int main()
{
    int n;
    printf("请输入皇后个数：");
    scanf("%d", &n);
    n_queens(1, n);
    printf("共有 %d 种不同的排列", count);
    return 0;
}
