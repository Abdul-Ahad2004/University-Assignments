//#include<iostream>
//using namespace std;
//int main()
//{
//	int TM,limit,W_amount,no5000,no500=0,no1000;
//	cout << "Enter the total amount present in your account: ";
//	cin >> TM;
//	if (TM <= 0)
//		cout<<"Enter a valid moment." << endl;
//	cout << "Enter your maximum daily withdraw limit: ";
//	cin >> limit;
//	cout << "Enter the amount that you wants to withdraw: ";
//	cin >> W_amount;
//	if (W_amount > TM)
//		cout << "There is not enough money in your account." << endl;
//	else if (W_amount > limit)
//		cout << "you are exceeding your maximum daily withdraw limit.You can't withdraw the amount." << endl;
//	else if (W_amount % 500 != 0)
//		cout << "Please enter the multiple of 500 for withdraw the amount" << endl;
//	else
//	{
//		W_amount = W_amount - 500;
//		if (W_amount >= 5000)
//		{
//			no5000 = W_amount / 5000;
//			cout << "Total numbers of note of 5000= " << no5000 << endl;
//			W_amount = W_amount % 5000;
//
//		}
//		if (W_amount >= 1000)
//		{
//			no1000 = W_amount / 1000;
//			cout << "Total numbers of note of 1000= " << no1000 << endl;
//
//		}
//		if (W_amount >= 1000 && W_amount%1000==0)
//		{
//			no500++;
//			cout << "Total numbers of note of 500= " << no500 << endl;
//		}
//		else if (W_amount >= 1000 && W_amount % 1000 != 0)
//		{
//			no500 = no500 + 2;
//			cout << "Total numbers of note of 500= " << no500 << endl;
//
//		}
//	}
//
//
//			
//
//		
//		
//
//	
//}
//
