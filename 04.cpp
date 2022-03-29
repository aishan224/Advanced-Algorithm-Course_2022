/*贪心实现磁盘SSTF(Shortest Seek Time First)调度*/
#include <iostream>
#include <cmath>
using namespace std;

/*  requestSeq 为初始的请求序列， cur为当前访问的位置，
	diff标记当前访问的与requestSeq中的其他的距离和是否访问过，
	len为requestSeq的长度  */
void calculateDifference(int requestSeq[], int cur, int **diff, int len) {
	for (int i = 0; i < len; i++) {
		diff[i][0] = abs(cur - requestSeq[i]); //第一列保存距离
	}
}

/* 找到距离当前访问的位置最近的 */
int findMinIndex(int **diff, int len) {
    int index = -1;
    int min = 1e9;

    for (int i = 0; i < len; i++) {
        /* diff[i][1]  初始化为0表示此位置并未访问过 */
        if (!diff[i][1] && min > diff[i][0]) //仅在未访问过的中寻找最小的
        {
            min = diff[i][0];  //找到距离中的最小值，也就是greedy所寻求的
            index = i;
        }
    }
    return index;
}

/* 算法主要函数 */
int ShortestSeekTimeFirst(int requestSeq[], int cur, int len) {
    if (len == 0) { // 边界条件
        return 0;
    }

    /* diff数组的创建和初始化 */
    int **diff = new int *[len];
    for (int i = 0; i < len; i++) {
        diff[i] = new int[2];
    }

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < 2; j++) {
            diff[i][j] = 0;
        }
    }

    int sum = 0;  //记录最终的磁头移动总数

    int* selectSeq = new int[len]{0};  //记录访问过的位置

    for (int i = 0; i < len; i++) {
        
        calculateDifference(requestSeq, cur, diff, len); //每次都更新diff数组为距离当前磁头的距离
        int m_index = findMinIndex(diff, len);
        diff[m_index][1] = 1;  // 标记为已选择

        sum += diff[m_index][0];
        cur = requestSeq[m_index];
        selectSeq[i] = cur;  //赋给记录数组
    }

    /* Display */
    cout << "The minimum length is: " << sum << endl;
    cout << endl << "The Sequence is: " << endl;
    for (int i = 0; i < len; i++) {
        cout << selectSeq[i] << endl;
    }

    //释放空间
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