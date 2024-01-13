//#include<iostream>
//#include<conio.h>
//#include<time.h>
//using namespace std;
//int main()
//{
//	int** arr = new int* [10];
//	for (int i = 0; i < 10; i++)
//	{
//		arr[i] = new int[10];
//	}
//	//srand(time(0));
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < 10; j++)
//		{
//
//			int a = rand() % 2;
//			arr[i][j] = a;
//			if (i == 0 && j == 0)
//				arr[i][j] = 1;
//			if (i == 9 && j == 9)
//				arr[i][j] = 1;
//		}
//
//	}
//	cout << "Enter w for up\nEnter s for down\nEnter d for right\nEnter a for right\nYour total moves are 25" << endl;
//	cout << "*******Let's start the game******" << endl;
//	int i = 0, j = 0, moves = 25, count = 0;
//	for (; i < 10 || j < 10;)
//	{
//		cout << " ";
//		for (int k = 0; k < 10; k++)
//		{
//			for (int l = 0; l < 10; l++)
//			{
//				if (i == k && j == l)
//					cout << "A" << "  ";
//				else
//					cout << arr[k][l] << "  ";
//			}
//			cout << endl << " ";
//		}
//		cout << "\t\tYour remaining moves are: " << moves << endl;
//		char a = _getch();
//		while (a != 'w' && a != 's' && a != 'd' && a != 'a')
//		{
//			cout << "Enter the valid button: ";
//			cout << endl;
//			a = _getch();
//		}
//		if (i == 0 && j == 0 && (a == 'w' || a == 'a')) {
//			count++;
//			cout << "*******Can't move.*******" << endl;
//		}
//		if (i == 0 && j == 9 && (a == 'w' || a == 'd')) {
//			count++;
//			cout << "*******Can't move.*******" << endl;
//		}
//		if (i == 9 && j == 0 && (a == 's' || a == 'a')) {
//			count++;
//			cout << "*******Can't move.*******" << endl;
//		}
//		if (i == 9 && j == 9 && (a == 's' || a == 'd')) {
//			count++;
//			cout << "*******Can't move.*******" << endl;
//		}
//		if (count == 0) {
//			if (a == 'w')
//			{
//				i--;
//				moves--;
//				if (i < 0)
//				{
//					cout << "*******We can't move.********" << endl;
//					i++;
//					moves++;
//				}
//				if (arr[i][j] == 0)
//				{
//					cout << "********We can't move because of the wall*******" << endl;
//					i++;
//
//				}
//			}
//			else if (a == 's')
//			{
//				i++;
//				moves--;
//				if (i > 9)
//				{
//					cout << "******We can't move.*******" << endl;
//					i--;
//					moves++;
//				}
//				if (arr[i][j] == 0)
//				{
//					cout << "*********We can't move because of the wall********" << endl;
//					i--;
//
//				}
//			}
//			else if (a == 'a')
//			{
//				j--;
//				moves--;
//				if (j < 0)
//				{
//					cout << "********We can't move.********" << endl;
//					j++;
//					moves++;
//				}
//				if (arr[i][j] == 0)
//				{
//					cout << "******We can't move because of the wall******" << endl;
//					j++;
//
//				}
//			}
//			else if (a == 'd')
//			{
//				j++;
//				moves--;
//				if (j > 9)
//				{
//					cout << "******We can't move.******" << endl;
//					j--;
//					moves++;
//				}
//				if (arr[i][j] == 0)
//				{
//					cout << "******We can't move because of the wall*****" << endl;
//					j--;
//
//				}
//			}
//			if (i == 9 && j == 9)
//			{
//				cout << "********Congratulations You won the game.********" << endl;
//				break;
//				system("pause");
//			}
//		}
//		else
//			count = 0;
//
//		if (moves == 0)
//		{
//			system("cls");
//			cout << "\t\tYour remaining moves are: " << moves << endl;
//			cout << "!!!!!!!!Game over!!!!!!" << endl;
//			break;
//			system("pause");
//		}
//		system("cls");
//	}
//	for (int i = 0; i < 10; i++)
//	{
//		delete[]arr[i];
//		arr[i] = NULL;
//	}
//	delete[]arr;
//	arr = NULL;
//	system("pause");
//}