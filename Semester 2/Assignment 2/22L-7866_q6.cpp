#include<iostream>
using namespace std;
class Appointments
{
public:
	string description;
	int day;
	int month;
	int year;
	Appointments()
	{
		description = "";
		day = 0;
		month = 0;
		year = 0;
	}
	Appointments(string s,int d,int m,int y)
	{
		description = s;
		day = d;
		month = m;
		year = y;
	}
	int occursOn(int year, int month, int date)
	{
		if (this->day == date && this->month == month && this->year == year)
			return 1;
		return 0;
	}
};
class Onetime :public Appointments
{
public:
	Onetime()
	{
		description = "";
		day = 0;
		month = 0;
		year = 0;
	}
	Onetime(string s, int d, int m, int y)
	{
		description = s;
		day = d;
		month = m;
		year = y;
	}
};
class Daily :public Appointments
{
public:
	Daily()
	{
		description = "";
		day = 0;
		month = 0;
		year = 0;
	}
	Daily(string s, int d, int m, int y)
	{
		description = s;
		day = d;
		month = m;
		year = y;
	}
};
class Monthly :public Appointments
{
public:
	Monthly ()
	{
		description = "";
		day = 0;
		month = 0;
		year = 0;
	}
	Monthly(string s, int d, int m, int y)
	{
		description = s;
		day = d;
		month = m;
		year = y;
	}
};
int main()
{
	Appointments** list=new Appointments*[5];
	list[0]=new Onetime("see the dentist",2,3,2023);
	list[1] = new Daily("Use mobile phone", 3, 3, 2023);
	list[2] = new Monthly("Go to university", 5, 4, 2023);
	list[3] = new Onetime("Preparing exam", 2, 3, 2023);
	list[4] = new Daily("Watch the series", 3, 3, 2023);
	int d, y, m,choice = 1,a;
	while (choice == 1)
	{
		cout << "Enter the date: ";
		cin >> d;
		cout << "Enter the month: ";
		cin >> m;
		cout << "Enter the year: ";
		cin >> y;
		int k = 1, ch = 0;
		cout << "Your Appointments on the entered date are: " << endl;
		for (int i = 0; i < 5; i++)
		{
			a=list[i]->occursOn(y, m, d);
			if (a == 1) {
				cout << k << ". " << list[i]->description << endl;
				k++;
				ch = 1;
			}
		}
		if (ch == 0)
		{
			cout << "You have not any appointment on the entered date. " << endl;
		}
		cout << "Press 1 if you want to do again: ";
		cin >> choice;
		if (choice == 1)
			system("cls");
	}

}