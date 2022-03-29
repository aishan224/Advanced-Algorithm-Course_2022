/*̰��ʵ�ִ���SSTF(Shortest Seek Time First)����*/
#include <iostream>
#include <cmath>
using namespace std;

/*  requestSeq Ϊ��ʼ���������У� curΪ��ǰ���ʵ�λ�ã�
	diff��ǵ�ǰ���ʵ���requestSeq�е������ľ�����Ƿ���ʹ���
	lenΪrequestSeq�ĳ���  */
void calculateDifference(int requestSeq[], int cur, int **diff, int len) {
	for (int i = 0; i < len; i++) {
		diff[i][0] = abs(cur - requestSeq[i]); //��һ�б������
	}
}

/* �ҵ����뵱ǰ���ʵ�λ������� */
int findMinIndex(int **diff, int len) {
    int index = -1;
    int min = 1e9;

    for (int i = 0; i < len; i++) {
        /* diff[i][1]  ��ʼ��Ϊ0��ʾ��λ�ò�δ���ʹ� */
        if (!diff[i][1] && min > diff[i][0]) //����δ���ʹ�����Ѱ����С��
        {
            min = diff[i][0];  //�ҵ������е���Сֵ��Ҳ����greedy��Ѱ���
            index = i;
        }
    }
    return index;
}

/* �㷨��Ҫ���� */
int ShortestSeekTimeFirst(int requestSeq[], int cur, int len) {
    if (len == 0) { // �߽�����
        return 0;
    }

    /* diff����Ĵ����ͳ�ʼ�� */
    int **diff = new int *[len];
    for (int i = 0; i < len; i++) {
        diff[i] = new int[2];
    }

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < 2; j++) {
            diff[i][j] = 0;
        }
    }

    int sum = 0;  //��¼���յĴ�ͷ�ƶ�����

    int* selectSeq = new int[len]{0};  //��¼���ʹ���λ��

    for (int i = 0; i < len; i++) {
        
        calculateDifference(requestSeq, cur, diff, len); //ÿ�ζ�����diff����Ϊ���뵱ǰ��ͷ�ľ���
        int m_index = findMinIndex(diff, len);
        diff[m_index][1] = 1;  // ���Ϊ��ѡ��

        sum += diff[m_index][0];
        cur = requestSeq[m_index];
        selectSeq[i] = cur;  //������¼����
    }

    /* Display */
    cout << "The minimum length is: " << sum << endl;
    cout << endl << "The Sequence is: " << endl;
    for (int i = 0; i < len; i++) {
        cout << selectSeq[i] << endl;
    }

    //�ͷſռ�
    for (int i = 0; i < len; i++)
    {
        delete[] diff[i];
    }
    delete[] diff;

    delete[] selectSeq;
}

int main() {

    int requestSequence[8] = { 98, 183, 37, 122, 14, 124, 65, 67 };
    int length = sizeof(requestSequence) / sizeof(requestSequence[0]);
    int c = 53;
    
    ShortestSeekTimeFirst(requestSequence, c, length);
	return 0;
}