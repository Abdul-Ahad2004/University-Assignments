//#include<iostream>
//using namespace std;
//int counter = 0;
//class ComboLock
//{
//public:
//	int n1, n2, n3, dial, count1;
//	ComboLock(int a, int b, int c)
//	{
//		if (a >= 0 && a <= 39)
//			n1 = a;
//		else
//			n1 = 0;
//		if (b >= 0 && b <= 39)
//			n2 = b;
//		else
//			n2 = 0;
//		if (c >= 0 && c <= 39)
//			n3 = c;
//		else
//			n3 = 0;
//		dial = 0;
//		count1 = 0;
//	}
//	void reset()
//	{
//		dial = 0;
//		cout << "The dial has been reset." << endl;
//	}
//	void turnleft(int ticks)
//	{
//		dial += ticks;
//		while(dial > 40) {
//			dial = dial % 40;
//		}
//
//		if (dial == n2)
//			count1++;
//
//	}
//	void turnright(int ticks)
//	{
//		dial -= ticks;
//		while(dial < 0) {
//			dial = -1 * dial;
//			dial = 40 - dial;
//		}
//		if (counter == 0 && dial == n1)
//			count1++;
//		if (counter == 2 && dial == n3)
//			count1++;
//	}
//	bool open()
//	{
//		if (counter == 3 && count1 == 3)
//			return true;
//		else
//			return false;
//
//	}
//
//};
//
//int main()
//{
//	ComboLock a(1, 2, 1);
//	//39,1,1
//	//39,1,41
//	//39,41,41
//	int choice, ticks, previous = 1;
//	char repeat = '1';
//	while (1 && repeat == '1') {
//		cout << "Enter 0 to reset the dial of lock.\nEnter 1 to turn the dial left.\nEnter 2 to turn the dial right\nEnter 3 to attempt to open a lock. " << endl;
//		cout << "Enter your choice: ";
//		cin >> choice;
//		while (choice > 3 && choice < 0)
//		{
//			cout << "Please enter the valid option: ";
//			cin >> choice;
//		}
//		if (choice == 0)
//		{
//			a.reset();
//		}
//		else if (choice == 1)
//		{
//			cout << "Enter the number of ticks you want to turn left: ";
//			cin >> ticks;
//			a.turnleft(ticks);
//			if (previous == 2 && counter == 1)
//				counter++;
//			else
//				counter = 0;
//		}
//		else if (choice == 2)
//		{
//			cout << "Enter the number of ticks you want to turn right: ";
//			cin >> ticks;
//			a.turnright(ticks);
//			if (counter == 0)
//				counter++;
//			if (previous == 1 && counter == 2)
//				counter++;
//		}
//		else if (choice == 3)
//		{
//			if (a.open()) {
//				cout << "Congratulations!!!The lock has been opened." << endl;
//				break;
//			}
//			else {
//				cout << "The lock has not been opened." << endl;
//				cout << "Enter 1 if you want to try again else 2: ";
//				cin >> repeat;
//			}
//		}
//		previous = choice;
//		system("cls");
//	}
//}