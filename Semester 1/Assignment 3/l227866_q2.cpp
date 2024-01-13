//#include<iostream>
//using namespace std;
//int main()
//{
//	cout << "\t\t\tmenu function\n press 1 for factorial of a number\n press 2 for npr\n press 3 for ncr by using formula n!/(n-r)!*r!\n press 4 for ncr by using the formula npr/r!\n press 5 to exit the program. " << endl;
//	int a, number;
//	long n, r;
//	do
//	{
//		int f1 = 1, f2 = 1, f3 = 1, npr, ncr;
//		cout << "enter the number from the menu: ";
//		cin >> number;
//		if (number <= 0 || number > 5)
//		{
//			cout << "please enter the valid number from menu." << endl;
//			continue;
//		}
//		if (number == 5)
//			break;
//		cout << "enter the value of n greater than 0: ";
//		cin >> n;
//
//		if (n > 0)
//		{
//			for (int i = 1; i <= n; i++)
//			{
//				f1 = f1 * i;
//
//			}
//		}
//		else if (n == 0)
//			f1 = 1;
//		if (number == 1)
//		{
//			if (n < 0)
//				cout << "factorial of a negative number does not exist.";
//			else
//				cout << "the factorial of " << n << " is: " << f1 << "." << endl;
//		}
//		if (number == 2)
//		{
//			cout << "enter the value of r greater than 0: ";
//			cin >> r;
//			a = n - r;
//			if (r > 0)
//			{
//				for (int i = 1; i <= r; i++)
//				{
//					f2 = f2 * i;
//
//				}
//			}
//			else if (r == 0)
//				f2 = 1;
//			if (a > 0)
//			{
//				for (int i = 1; i <= a; i++)
//				{
//					f3 = f3 * i;
//
//				}
//			}
//			else if (a == 0)
//				f3 = 1;
//			if (n < 0 || a < 0)
//				cout << "factorial of a negative number does not exist." << endl;
//			else
//			{
//				npr = f1 / f3;
//				cout << "the number of permutation is: " << npr << endl;
//			}
//		}
//		if (number == 3)
//		{
//			cout << "enter the value of r greater than 0: ";
//			cin >> r;
//			a = n - r;
//			if (r > 0)
//			{
//				for (int i = 1; i <= r; i++)
//				{
//					f2 = f2 * i;
//
//				}
//			}
//			else if (r == 0)
//				f2 = 1;
//			if (a > 0)
//			{
//				for (int i = 1; i <= a; i++)
//				{
//					f3 = f3 * i;
//
//				}
//			}
//			else if (a == 0)
//				f3 = 1;
//			if (n < 0 || a < 0 || r < 0)
//				cout << "factorial of a negative number does not exist." << endl;
//			else
//			{
//				ncr = f1 / (f3 * f2);
//				cout << "the number of combinations are: " << ncr << endl;
//			}
//
//
//		}
//		if (number == 4)
//		{
//			cout << "enter the value of r greater than 0: ";
//			cin >> r;
//			a = n - r;
//			if (r > 0)
//			{
//				for (int i = 1; i <= r; i++)
//				{
//					f2 = f2 * i;
//
//				}
//			}
//			else if (r == 0)
//				f2 = 1;
//			if (a > 0)
//			{
//				for (int i = 1; i <= a; i++)
//				{
//					f3 = f3 * i;
//
//				}
//			}
//			else if (a == 0)
//				f3 = 1;
//			if (r < 0 || n < 0 || a < 0)
//				cout << "factorial of a negative number does not exist." << endl;
//			else
//			{
//				npr = f1 / f3;
//				ncr = npr / f2;
//				cout << "the number of combinations are: " << ncr << endl;
//			}
//		}
//
//	} while (1);
//}