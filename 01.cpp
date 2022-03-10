//#include <iostream>
//using namespace std;
//
///* 十进制各项求和函数 */
//int f(int n)
//{
//	if (n / 10 != 0) { // 若为两位数
//
//		return n % 10 + f(n / 10); // 末尾值加上去掉末尾后的递归调用
//	}
//	else {
//		return n;  // 直到仅剩1位
//	}
//}
//
///* 二进制各项求和函数 */
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
//	cout << "The total number of lucky number is: " << totalLuckyNumbers << " 个" << endl;
//	return 0;
//}
