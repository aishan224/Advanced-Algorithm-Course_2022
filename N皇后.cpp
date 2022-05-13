
#include <iostream>
using namespace std;

int main() {

	cout << "asd" << endl;
	return 0;
}

main����
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
	for (int i = 0; i < n; i++) { //��ǰ������ѷŵĻʺ�����ж�
		if ((queen[n] == queen[i]) || abs(queen[n] - queen[i]) == abs(n - i)) {
			return 0;
		}
	}
	return 1;
}

void reBack(int n) {  //Ϊ��n���ʺ���λ�ã����к�
	for (int i = 0; i < N; i++) {  //ÿ���ʺ����������ĸ�λ��
		queen[n] = i;  //��n�еĻʺ����ÿ��i��
		if (isPlacedable(n)) {  //��n���ж���һ�еĻʺ��ܲ��ܷ��£����жϺ�����Ҳ�ǱȽ�queen[n]��ֵ
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

����
#include <stdio.h>
#define N 20       //�ʺ������
int q[N];          //���лʺ����ڵ���
int count = 0;     //ͳ��N�ʺ������ĸ���

//��� N �ʺ�����Ľ������
void print(int n)
{
    int i, j;
    count++;
    printf("��%d���⣺\n", count);
    for (i = 1; i <= n; i++)        //��
    {
        for (j = 1; j <= n; j++)   //��
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
//�����k�е�j�����Ƿ���԰ڷŻʺ�
int isSafe(int k, int j)
{
    int i;
    for (i = 1; i < k; i++) {
        //����������ʺ�λ��ͬһ���ϣ�����λ�ڸ�λ�õ�б��λ���ϣ����λ���޷�ʹ��
        if (q[i] == j || abs(i - k) == abs(q[i] - j))
            return 0;
    }
    return 1;
}
//���ûʺ�������
void n_queens(int k, int n)
{
    int j;
    if (k > n)     //�ݹ�ĳ���
        print(n);
    else
    {
        for (j = 1; j <= n; j++)   //��̽��k�е�ÿһ�У��ҵ�����Ҫ�����
        {
            if (isSafe(k, j))
            {
                q[k] = j;
                n_queens(k + 1, n);  //��ȷ�ϵ� k �лʺ�λ�õ�ǰ���£�����������һ�лʺ��λ��
            }
        }
    }
}

int main()
{
    int n;
    printf("������ʺ������");
    scanf("%d", &n);
    n_queens(1, n);
    printf("���� %d �ֲ�ͬ������", count);
    return 0;
}
