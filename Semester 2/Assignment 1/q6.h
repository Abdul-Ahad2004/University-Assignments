#include<iostream>
using namespace std;
class MyString
{
private:
	char*p=new char[50];
public:
	MyString()
	{
		cout << "Enter the sentence: ";
		cin.getline(p, 50);
	}
	void getdata()
	{
		for (int i = 0; p[i] != '\0'; i++)
		{
			cout << p[i];
		}
		cout << endl;
	}
	int length()
	{
		int count = 0;
		for (int i = 0; p[i] != '\0'; i++)
		{
			count++;
		}
		return count;
	}
	int length(char* word)
	{
		int count = 0;
		for (int i = 0; word[i] != '\0'; i++)
		{
			count++;
		}
		return count;
	}
	char* concatenate()
	{
		char* p1 = new char[50];
		cout << "Enter the word to which you want to concatenate: ";
		cin.ignore();
		cin.getline(p1,50);
		int l1 = length(p1), l2 = length(p),k=0;
		char* p2 = new char[l1 + l2];
		for (int i = 0; p[i] != '\0'; i++)
		{
			p2[k] = p[i];
			k++;
		}
		for (int i = 0; p1[i] != '\0'; i++)
		{
			p2[k] = p1[i];
			k++;
		}
		p2[k] = '\0';
		delete[]p1;
		p1 = NULL;
			return p2;
	}
	bool search()
	{
		char* p2 = new char[50];
		cout << "Enter the word you want to search: ";
		cin.getline(p2,50);
		int l = length(p2), count = 0;
		for (int i = 0; p[i] != '\0'; i++)
		{

			int k = 0;
			if (p2[k] == p[i])
			{
				k++;
				count++;
				if (count == l) {
					delete[]p2;
					p2 = NULL;
					return true;
				}
				else {
					for (int j = i + 1; count < l && p[j] != '\0'; j++)
					{
						if (p2[k] == p[j])
						{
							count++;
							k++;
						}
						if (count == l) {
							delete[]p2;
							p2 = NULL;
							return true;
						}
					}
				}
			}
			count = 0;
		}
		delete[]p2;
		p2 = NULL;
		return false;
	}
	void reverse()
	{
		int l = length(p);
		for (int i = 0; i < l / 2; i++)
		{
			char temp = p[i];
			p[i] = p[l - 1 - i];
			p[l - 1 - i] = temp;
		}
	}
	char* substring()
	{
		int i,k=0;
		cout << "Enter the first index you want for substring: ";
		cin >> i;
		int l = length(p);
		while (i < 0 || i >= l)
		{
			cout << "Enter the valid index for substring: ";
			cin >> i;
		}
		char* p1 = new char[50];
		for (int j = i;p[j]!='\0'; j++)
		{
			p1[k]= p[j];
			k++;
		}
		p1[k] = '\0';
		return p1;
	}
	~MyString()
	{
		delete[]p;
		p = NULL;
	}

};
