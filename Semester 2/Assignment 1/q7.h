#include<iostream>
using namespace std;
int length(char* word)
{
	int count = 0;
	for (int i = 0; word[i] != '\0'; i++)
	{
		count++;
	}
	return count;
}
void print(char* p)
{
	char* p1 = new char[50];
	int i = 0, m = 0;
	for (; p[i] != '\0'; i++)
	{
		int a = int(p[i]);
		if ((a >= 65 && a <= 90) || (a >= 97 && a <= 122))
		{
			p1[m] = p[i];
			m++;
		}
		else {
			p1[m] = '\0';
			int l = length(p1), count = 0, f = 0;
			for (int i = 0; p[i] != '\0'; i++)
			{

				int k = 0;
				if (p1[k] == p[i])
				{
					k++;
					count++;
					for (int j = i + 1; count < l && p[j] != '\0'; j++)
					{
						if (p1[k] == p[j])
						{
							count++;
							k++;
						}
						else
							break;
						if (count == l)
							f++;
					}
				}
				count = 0;
			}
			int b = int(p1[0]);
			if (f == 0 && ((b >= 65 && b <= 90) || (b >= 97 && b <= 122))) {
				for (int i = 0; p1[i] != '\0'; i++)
				{
					cout << p1[i];
				}
				cout << " =1 " << endl;
			}
			else if (f > 0) {
				for (int i = 0; p1[i] != '\0'; i++)
				{
					cout << p1[i];
				}
				cout << " = " << f << endl;
			}
			for (int i = 0; i < 50; i++)
			{
				p1[i] = '\0';
			}
			m = 0;

		}


	}
	delete[]p1;
	p1 = NULL;
}
