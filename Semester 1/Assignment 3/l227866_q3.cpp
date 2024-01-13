#include<iostream>
using namespace std;
int main()
{
	int n1,n2,n3,choice;
	char ch1,ch2;
	cout << "Enter 1 for the  hollow square diamond, Enter 2 for hexagon or enter 3 for arrow: ";
	cin >> choice;
	if (choice < 0 || choice>3)
	{
		cout << "Please enter the valid data." << endl;
	}
	if (choice == 2)
	{
		cout << "Enter the size of hexagon, must be greter than 0: ";
		cin >> n1;
		if (n1 < 0)
			cout << "Please enter the positive number." << endl;
		else
		{
			cout << "Enter the character to print: ";
			cin >> ch1;
			int a = n1;
			for (int i =1;i<=a; i++)
			{
				for (int s = a-1; s >= i; s--)
				{
					cout << " ";
				}
				for (int j = 1; j <=n1; j++)
				{
					cout << ch1;
				}
				cout << endl;
				n1 = n1 + 2;
			}
			n1 = n1 - 4;
			for (int i = 1; i < a; i++)
			{
				for (int s = 1; s <= i; s++)
				{
					cout << " ";
				}
				for (int j = 1; j <= n1; j++)
				{
					cout << ch1;
				}
				cout << endl;
				n1 = n1 - 2;
			}
			
			
		}
	}
	if (choice == 3)
	{
		cout << "Enter the size of arrow, must be greter than 0: ";
		cin >> n2;
		int k = n2 - 1;
		if (n2 < 0)
			cout << "Please enter the positive number." << endl;
		else
		{
			cout << "Enter the character to print: ";
			cin >> ch2;
			int a=1,b=1;
			for (int i = 1; i <= n2; i++)
			{
				for (int s = n2 - 1; s >= i; s--)
				{
					cout << " ";
				}
				for (int j = 1; j <= a; j++)
				{
					cout << ch2;
					if (i >= 3)
					{
						for (int s = 1; s <= b-2; s++)
						{
							cout << " ";
						}
					}
				
					
				}
				b++;
				cout << endl;
				a = 3;
			}
			for (int i = 1; i <= n2; i++)
			{
				for (int s = k; s >= 1; s--)
				{
					cout << " ";
				}
				cout << ch2;
				cout << endl;
			}
			
		}
	}
	if (choice == 1)
	{
		cout << "Enter the size of hollow square diamond , must be greter than 0: ";
		cin >> n3;
		int c= n3 - 1;
		int d = n3;
		if (n3 < 0)
			cout << "Please enter the positive number." << endl;
		else
		{
			int m = 1;
			for (int i = 1; i <= d; i++)
			{

				for (int j = 1; j <= n3; j++)
				{

					cout << j;
				}
				for (int s = 1; s <= m; s++)
				{
					if (i == 1)
					{
						m = 0;
						cout << "";
					}
					else
					{

						cout << " ";

					}
				}
				for (int k = c; k >= 1; k--)
				{
					cout << k;
				}
				cout << endl;
				if (i <= 1) {
					m = m + 1;
				
			}
				else  {
					m = m + 2;
				}
				
				n3 = n3 - 1;
				c = n3;
			}
			m = m - 4;
			for (int i = 1; i <d; i++)
			{
				for (int j = 1; j <=i+1; j++)
				{
					
					cout << j;
				}
				for (int s = 1; s <=m; s++)
				{
					cout << " ";
				}
				for (int k = i+1; k >=1; k--)
				{
					if (i == d - 1) {
						int z = k - 1;
						if (z == 0)
							cout << "";
						else
							cout << z;
					
						
					
					}
					else {
						cout << k;

					}
					
				}
				cout << endl;
				m = m - 2;
			}


		}
	}
}