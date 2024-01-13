//#include<iostream>
//using namespace std;
//int main()
//{
//	int a[1000] = { 0 }, size;
//	cout << "Enter the size of the array: ";
//	cin >> size;
//	int s = size;
//	for (int ind = 0; ind < size; ind++)
//	{
//		cout << "Enter the value at " << ind << " index of the array: ";
//		cin >> a[ind];
//	}
//	cout << "Array = ";
//	for (int ind = 0; ind < size; ind++)
//	{
//		cout << a[ind] << " ";
//	}
//	cout << endl;
//	for (int i = 0; i < size; i++)
//	{
//		for (int j = i + 1; j < size; j++)
//		{
//			if (a[i] > a[j])
//			{
//				int temp = a[i];
//				a[i] = a[j];
//				a[j] = temp;
//			}
//		}
//	}
//	int r = size - 1,i=0;
//	//for shifting the values right in the array
//	while(i <= size )
//	{
//		for (int j = r; j > i; j--)
//		{
//			a[j + 1] = a[j];
//
//		}
//		r++;
//		i = i + 2;
//
//	}
//	int l = 1;
//	//for shifting the values left back in the array at odd number of places
//	while( l<= r)
//	{
//		a[l] = a[r];
//		r--;
//		if (l == r - 4) 
//		{
//			r = r - 2;
//			a[l + 2] = a[r];
//		}
//		l = l + 2;
//
//
//
//	}
//	cout << "Resultant Array = ";
//	for (int ind = 0; ind < size; ind++)
//	{
//		cout << a[ind] << " ";
//	}
//	cout << endl;
//
//
//
//}