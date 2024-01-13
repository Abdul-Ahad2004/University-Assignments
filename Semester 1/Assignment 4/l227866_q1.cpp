//#include<iostream>
//#include<time.h>
//using namespace std;
//int main()
//{
//	srand(time(0));
//	int lottery[5] = { 0 },count=0;
//	for (int ind = 0; ind < 5; ind++)
//	{
//		int a = rand() % 10;
//		lottery[ind] = a;
//	}
//	int user[5] = { 0 };
//	for (int ind = 0; ind < 5; ind++)
//	{
//		
//		cout << "Enter the value at index " << ind << " : ";
//		cin >> user[ind];
//
//	}
//	cout << "User array: " << endl;
//	for (int ind = 0; ind < 5; ind++)
//	{
//		cout<< user[ind]<<" ";
//
//	}
//	cout << endl;
//	cout << "Lottery array: " << endl;
//	for (int ind = 0; ind < 5; ind++)
//	{
//		cout << lottery[ind] << " ";
//
//	}
//	cout << endl;
//	for (int ind = 0; ind < 5; ind++)
//	{
//		if (lottery[ind] == user[ind])
//		{
//			count++;
//		}
//
//	}
//	cout << "The number of matching digits : " << count << endl;
//	if (count == 5)
//	{
//		cout << "Congratulations! You are a grand prize winner." << endl;
//	}
//
//}