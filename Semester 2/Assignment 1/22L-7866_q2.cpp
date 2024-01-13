#include<iostream>
#include<fstream>
#include<string>
using namespace std;
ifstream f1;
ofstream f2;
int main()
{
	int rows=0,columns=0;
	f1.open("q2.txt");
	string s;
	while (getline(f1,s))
	{
		rows++;
	}
	f1.close();
	string** p = new string * [rows];//original array
	f1.open("q2.txt");
	string s1,temp;
	getline(f1, s1);
	for (int i = 0; s1[i] != '\0'; i++)
	{
		if(s1[i]==' ')
			columns++;

	}
	columns++;
	f1.close();
	for (int i = 0; i < rows; i++)
	{
		p[i] = new string[columns];
	}
	f1.open("q2.txt");
	string s2="";
	for (int i = 0; i < rows; i++)
	{
		getline(f1, temp);
		for (int j = 0,k=0; j <columns;k++)
		{
			
			if (temp[k] != ' '&& temp[k]!='\0')
				s2 += temp[k];
			else {
				p[i][j] = s2;
				s2="";
				j++;
			}
		}
	}
	f1.close();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << p[i][j] << " ";
		}
		cout << endl;
	}
	int** p1 = new int* [rows];//array to store counters
	for (int i = 0; i < rows; i++)
	{
		p1[i] = new int[2];
	}
	int** p2 = new int * [rows];//array to store indexes
	for (int i = 0; i < rows; i++)
	{
		int count1 = 0, count2 = 0;
		for (int j = 0; j < columns; j++)
		{
			if (p[i][j] == "Yes")
				count1++;
			else
				count2++;
		}
		p1[i][0] = count1;
		p1[i][1] = count2;
		p2[i] = new int[count1];
		for (int j = 0,k=0; j < columns; j++)
		{
			if (p[i][j] == "Yes") {
				p2[i][k] = j;
				k++;
			}
		}
	}
	cout << endl;
	cout << "******Next 2D array******";
	cout << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j <2; j++)
		{
			cout << p1[i][j] << " ";
		}
		cout << endl;
	}
	string** p4 = new string * [rows];// array to make original array
	for (int i = 0; i < rows; i++)
	{
		p4[i] = new string[columns];
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0,k=0; j < columns; j++)
		{
			if (j == p2[i][k]) {
				p4[i][j] = "Yes";
				k++;
			}
			else
				p4[i][j] = "No";
		}
	}
	cout << endl;
	cout << "******Remake of original 2D array******";
	cout << endl;
	int counter = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << p4[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (p[i][j] == "Yes")
				counter++;
		}
	}
	cout << endl;
	cout << "The total number of \'Yes\' in the original array are: " << counter << endl;
	for (int i = 0; i < rows; i++)
	{
		delete[]p[i];
		p[i] = NULL;
	}
	delete[]p;
	p = NULL;
	for (int i = 0; i < rows; i++)
	{
		delete[]p1[i];
		p1[i] = NULL;
	}
	delete[]p1;
	p1= NULL;
	for (int i = 0; i < rows; i++)
	{
		delete[]p2[i];
		p2[i] = NULL;
	}
	delete[]p2;
	p2 = NULL;
	for (int i = 0; i < rows; i++)
	{
		delete[]p4[i];
		p4[i] = NULL;
	}
	delete[]p4;
	p4 = NULL;
}