//#include <iostream>
//using namespace std;
//
///* ʮ���Ƹ�����ͺ��� */
//int f(int n)
//{
//	if (n / 10 != 0) { // ��Ϊ��λ��
//
//		return n % 10 + f(n / 10); // ĩβֵ����ȥ��ĩβ��ĵݹ����
//	}
//	else {
//		return n;  // ֱ����ʣ1λ
//	}
//}
//
///* �����Ƹ�����ͺ��� */
//int g(int n)
//{
//	if (n / 2 != 0) {
//		return n % 2 + g(n / 2);
//	}
//	else {
//		return 1;
//	}
//}
//
//
//int main()
//{
//	int num, totalLuckyNumbers = 0;
//	cout << "Please enter upper bound: ";
//	cin >> num;
//	for (int i = 1; i <= num; i++)
//	{
//		int decimal = f(i);
//		if (decimal == g(i))
//		{
//			totalLuckyNumbers++;
//			cout << " one of lucky numbers is: " << i << endl;
//		}
//	}
//	cout << "The total number of lucky number is: " << totalLuckyNumbers << " ��" << endl;
//	return 0;
//}
