//#include<iostream>
//using namespace std;
//int main()
//{
//	int again;
//	
//	do
//	{
//		long long int choice, m,N,n,e, n1 = 0, n2 = 1,sum;
//		cout << " What do you want to do?\n\t\t1.\tDisplay nth term in the Fibonacci series\n\t\t2.\tDisplay first n Fibonacci numbers\n\t\t3.\tDisplay Fibonacci numbers between m and n." << endl;
//		cout << "Enter your choice: ";
//		cin >> choice;
//		if (choice <= 0 || choice > 3)
//		{
//			cout << "Please enter the valid choice.";
//		}
//		if (choice == 1)
//		{
//			cout << "Enter n(term number): ";
//			cin >> N;
//			if (N <= 0)
//			{
//				cout << "Please enter the valid data." << endl;
//			}
//			else
//			{
//				if (N == 1)
//				{
//					cout << N << " term in the Fibonacci series is " << n1<< endl;
//				}
//				else if (N == 2)
//				{
//					cout <<N << " term in the Fibonacci series is " << n2 << endl;
//				}
//				else
//				{
//					n = N - 2;
//					for (int i = 1; i <= n; i++)
//					{
//						sum = n1 + n2;
//						n1 = n2;
//						n2 = sum;
//
//					}
//					cout << N << " term in the Fibonacci series is " << sum << endl;
//				}
//			}
//			
//		}
//		if (choice == 2)
//		{
//			cout << "Enter n(number of terms): ";
//			cin >> N;
//			if (N <= 0)
//			{
//				cout << "Please enter the valid data." << endl;
//			}
//			else
//			{
//				if (N == 1)
//				{
//					cout<<"First" << N << " Fibonacci number is " << n1 << endl;
//				}
//				else
//				{
//					n = N - 2;
//					cout << "First " << N << " Fibonacci numbers are" << n1 << "," << n2;
//					for (int i = 1; i <= n; i++)
//					{
//						sum = n1 + n2;
//						cout << "," << sum;
//						n1 = n2;
//						n2 = sum;
//
//					}
//				}
//			}
//		}
//		if (choice == 3)
//		{
//			cout << "Enter m(start of range): ";
//			cin >> m;
//			cout << "Enter n(end of range): ";
//			cin >> e;
//			n = e;
//			cout << "Fibonacci numbers between " << m << " and " << e << " are ";
//			for (int i = 1; i <= e; i++)
//			{
//				sum = n1 + n2;
//				if (sum > m && sum < e) {
//					if (sum == 0)
//						cout << "none." << endl;
//					else
//					{
//						cout << sum << " ";
//					}
//				}
//				n1 = n2;
//				n2 = sum;
//
//			}
//		}
//		cout << "\nPress 1 if you want to continue again: ";
//		cin >> again;
//		
//		
//	}
//	while (again == 1);
//}