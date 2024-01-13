//#include<iostream>
//#include<time.h>
//#include<conio.h>
//using namespace std;
//int main()
//{
//	srand(time(0));
//	int a,b,c,d,i=0,j=0,g=1;
//	char ch;
//	int total1 = 0, total2 = 0;
//	cout << "\t\tGame " << g << endl;
//	while (g<=5)
//	{
//		if (i == 3)
//		{
//			cout << "The winner of series is player1." << endl;
//			break;
//		}
//		if (j == 3)
//		{
//			cout << "The winner of series is player2." << endl;
//			break;
//		}
//		cout << "\n\nPlayer 1 turn: ";
//		ch=_getch();
//		a = (rand() % 6) + 1;
//		cout << a << endl;
//		c = total1;
//		total1 = total1 + a;
//		if (total1 > 20)
//		{
//			cout << "Player 1's total: " << c << " (move not possible)" << endl;
//			total1 = c;
//		}
//		else if (total1 == 20)
//		{
//			cout << "Player 1's total: 20" << endl;
//			cout << "\t\tThe winner of game " << g << " is player 1." << endl;
//			cout << "\n*******************************" << endl;
//			i++;
//			g++;
//			total1 = 0, total2 = 0;
//			continue;
//		}
//		else
//			cout << "The player 1's total: " << total1 << endl;
//		cout << "Player 2 turn: ";
//		ch = _getch();
//		b = (rand() % 6) + 1;
//		cout << b << endl;
//		d = total2;
//		total2 = total2 + b;
//		if (total2 > 20)
//		{
//			cout << "Player 2's total: " << d << " (move not possible)" << endl;
//			total2 = d;
//		}
//		else if (total2== 20)
//		{
//			cout << "Player 2's total: 20" << endl;
//			cout << "\t\tThe winner of game " << g << " is player 2." << endl;
//			cout << "************************" << endl;
//			g++;
//			j++;
//			total1 = 0, total2 = 0;
//			continue;
//		}
//		else
//			cout << "Player 2's total: " << total2 << endl;
//		
//	}
//	if (g == 6)
//	{
//		if (i == 3)
//		{
//			cout << "The winner of series is player1." << endl;
//		}
//		if (j == 3)
//		{
//			cout << "The winner of series is player2." << endl;
//		}
//	}
//}