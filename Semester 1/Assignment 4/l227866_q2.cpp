//#include<iostream>
//using namespace std;
//int main()
//{
//	long int empld[7] = { 5658845,4520125,7895122,8777541,8451277,1302850,7580489 };
//	int hours[7] = { 0 },size=7;
//	double payRate[7] = { 0 };
//	double wages[7] = { 0 };
//	for (int ind = 0,i=1; ind < size; ind++,i++)
//	{
//		cout << "Enter the hours of employee number "<<i<<" : ";
//		cin >> hours[ind];
//		if (hours[ind] < 0)
//		{
//			cout << "Enter the value greater than 0." << endl;
//			ind--;
//			i--;
//
//		}
//	}
//	for (int ind = 0,i=1; ind < size; ind++,i++)
//	{
//		cout << "Enter the payRate of employee number " << i<<" : ";
//		cin >> payRate[ind];
//		if (payRate[ind] < 6.00)
//		{
//			cout << "Enter the value greater than 6.00" << endl;
//			ind--;
//			i--;
//		}
//	}
//	for (int ind = 0; ind < size; ind++)
//	{
//		wages[ind] = hours[ind] * payRate[ind];
//
//	}
//	for (int ind = 0,i=1; ind < size; ind++,i++)
//	{
//		cout << "Identifaction number of employee " << i << " : " << empld[ind] << endl;
//		cout << "Gross wage of employee " << i << " : " << wages[ind] << endl;
//
//	}
//}