//#include<iostream>
//#include"q7.h"
//using namespace std;
//int main()
//{
//	char*p=new char[100];
//	cout << "Enter the sentence: ";
//	cin.getline(p, 100);
//	char*p1=new char[100];
//	char choice = '1';
//	while (choice == '1') {
//		cout << "Enter the word to find its frequency: ";
//		cin.getline(p1,100);
//		int l = length(p1), count = 0, f = 0;
//		for (int i = 0; p[i] != '\0'; i++)
//		{
//
//			int k = 0;
//			if (p1[k] ==p[i])
//			{
//				k++;
//				count++;
//				if (count == l) {
//					f++;
//					break;
//				}
//				else {
//					for (int j = i + 1; count < l && p[j] != '\0'; j++)
//					{
//						if (p1[k] == p[j])
//						{
//							count++;
//							k++;
//						}
//						else
//							break;
//						if (count == l && (p[j+1]==' '|| p[j + 1] == ','|| p[j+1] == '.'))
//							f++;
//					}
//				}
//				
//			}
//			count = 0;
//		}
//		cout << "The frequency of " << p1<< " in sentence= " << f << endl;
//		cout << "Press 1 if you want to search another word else press 2: ";
//		cin >> choice;
//		cin.ignore();
//	}
//	print(p);
//	delete[]p;
//	p = NULL;
//	delete[]p1;
//	p1 = NULL;
//
//
//}