//#include<iostream>
//using namespace std;
//int main()
//{
//	int key[20] = { 66,68,65,65,67,65,66,65,67,68,66,67,68,65,68,67,67,66,68,65 };
//	int answer[20] = { 0 },count=0;
//	char ch;
//	for (int ind = 0, i = 1; ind < 20; ind++, i++)
//	{
//		cout << "enter the answer for question no. " << i << " : ";
//		cin >>ch;
//		answer[ind] = (int)ch;
//	}
//	for (int ind = 0; ind < 20; ind++)
//	{
//		if (key[ind] == answer[ind])
//		{
//			count++;
//		}
//	}
//	if (count >= 15)
//	{
//		cout << "*****************************" << endl;
//		cout << "you are pass." << endl;
//	}
//	else
//	{
//		cout << "*****************************" << endl;
//		cout << "you are fail." << endl;
//    }
//	cout << "the total number of correct questions are: " << count << endl;
//	cout << "the total number of incorrect questions are: " <<20-count << endl;
//	cout << "the incorrect question numbers are: ";
//	for (int ind = 0,i=1,a=0; ind < 20; ind++,i++)
//	{
//		if (key[ind] != answer[ind])
//		{
//			cout << i << " ";
//			a++;
//		}
//		if (a == 0)
//		{
//			cout << "0" << endl;
//
//		}
//	}
//
//}