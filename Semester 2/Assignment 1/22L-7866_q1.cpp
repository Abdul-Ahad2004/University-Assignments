#include<iostream>
using namespace std;
int  main()
{
	int r1, c1;
	cout << "Enter the number of rows you want in list: ";
	cin >> r1;
	cout << "Enter the number of columns you want in list: ";
	cin >> c1;
	int** arr1 = new int* [r1];
	for (int i = 0; i < r1; i++)
	{
		arr1[i] = new int[c1];
	}
	cout << "\n\nEnter the values in your list." << endl;
	for (int i = 0; i < r1; i++)
	{
		for (int j = 0; j < c1; j++)
		{
			cin >> arr1[i][j];
		}
	}
	cout << "Entered 2D array is:" << endl;
	for (int i = 0; i < r1; i++)
	{
		for (int j = 0; j < c1; j++)
		{
			cout << arr1[i][j] << " ";
		}
		cout << endl;
	}
	int r2 = 0, c2 = 0;
	for (int i = 0; i < r1; i++)
	{
		for (int j = 0; j < c1; j++)
		{
			if (arr1[i][j] > 0)
			{
				r2++;
				break;
			}
		}
	}
	cout << "\n\n**********************\nNew 2D array is:" << endl;
	int** arr2 = new int* [r2], k = 0, sum = 0, count = 0;
	for (int i = 0; i < r1; i++)
	{
		for (int j = 0; j < c1; j++)
		{
			if (arr1[i][j] > 0)
			{
				c2++;
				count = 1;
				

			}
		}
		if (count == 1) {
			arr2[k] = new int[c2];
			for (int j = 0,s=0;s<c2&& j < c1; j++)
			{
				if (arr1[i][j] > 0)
				{
					arr2[k][s] = arr1[i][j];
					s++;


				}
			}

			for (int j = 0; j < c2; j++)
			{
				cout << arr2[k][j] << " ";
				sum += arr2[k][j];
			}
			cout << endl;
			k++; c2= 0; count = 0;
		}


	}
	cout << "Sum= " << sum << endl;
	for (int i = 0; i < r1; i++)
	{
		delete[]arr1[i];
		arr1[i] = NULL;
	}
	delete[]arr1;
	arr1 = NULL;
	for (int i = 0; i < r2; i++)
	{
		delete[]arr2[i];
		arr2[i] = NULL;
	}
	delete[]arr2;
	arr2 = NULL;
	
}