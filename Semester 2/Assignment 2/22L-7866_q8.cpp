//#include<iostream>
//#include<string>
//#include<fstream>
//using namespace std;
//class Appointments
//{
//public:
//	string description;
//	int day;
//	int month;
//	int year;
//	Appointments()
//	{
//		description = "";
//		day = 0;
//		month = 0;
//		year = 0;
//	}
//	Appointments(string s, int d, int m, int y)
//	{
//		description = s;
//		day = d;
//		month = m;
//		year = y;
//	}
//	int occursOn(int year, int month, int date)
//	{
//		if (this->day == date && this->month == month && this->year == year)
//			return 1;
//		return 0;
//	}
//	string toString()
//	{
//		string s = "";
//		s += to_string(day);
//		s += "-";
//		s += to_string(month);
//		s += "-";
//		s += to_string(year);
//		return s;
//	}
//	void save(string type, string name )
//	{
//		ofstream f2;
//		f2.open(type+"\\" + "Appointments.txt", ios::app);
//		f2 << name << " ";
//		f2 << description << endl;
//		f2.close();
//	}
//};
//class Onetime :public Appointments
//{
//public:
//	Onetime()
//	{
//		description = "";
//		day = 0;
//		month = 0;
//		year = 0;
//	}
//	Onetime(string s, int d, int m, int y)
//	{
//		description = s;
//		day = d;
//		month = m;
//		year = y;
//	}
//	void load()
//	{
//		cout << "Your Appointments of Onetime type are: " << endl;
//		ifstream f1;
//		f1.open("Onetime\\Appointments.txt");
//		string s;
//		int no = 0;
//		while (getline(f1, s))
//			no++;
//		f1.close();
//		f1.open("Onetime\\Appointments.txt");
//		for (int i = 0; i < no; i++)
//		{
//			getline(f1, s, ' ');
//			cout << "On " << s << ": " << endl;
//			getline(f1, s, '\n');
//			cout << "\t" << s << endl;
//		}
//		f1.close();
//	}
//};
//class Daily :public Appointments
//{
//public:
//	Daily()
//	{
//		description = "";
//		day = 0;
//		month = 0;
//		year = 0;
//	}
//	Daily(string s, int d, int m, int y)
//	{
//		description = s;
//		day = d;
//		month = m;
//		year = y;
//	}
//	void load()
//	{
//		cout << "Your Appointments of Daily type are: " << endl;
//		ifstream f1;
//		f1.open("Daily\\Appointments.txt");
//		string s;
//		int no = 0;
//		while (getline(f1, s))
//			no++;
//		f1.close();
//		f1.open("Daily\\Appointments.txt");
//		for (int i = 0; i < no; i++)
//		{
//			getline(f1, s, ' ');
//			cout << "On " << s << ": " << endl;
//			getline(f1, s, '\n');
//			cout << "\t" << s << endl;
//		}
//		f1.close();
//	}
//};
//class Monthly :public Appointments
//{
//public:
//	Monthly ()
//	{
//		description = "";
//		day = 0;
//		month = 0;
//		year = 0;
//	}
//	Monthly(string s, int d, int m, int y)
//	{
//		description = s;
//		day = d;
//		month = m;
//		year = y;
//	}
//	void load()
//	{
//		cout << "Your Appointments of Monthly type are: " << endl;
//		ifstream f1;
//		f1.open("Monthly\\Appointments.txt");
//		string s;
//		int no = 0;
//		while (getline(f1, s))
//			no++;
//		f1.close();
//		f1.open("Monthly\\Appointments.txt");
//		for (int i = 0; i < no; i++)
//		{
//			getline(f1, s, ' ');
//			cout << "On " << s << ": " << endl;
//			getline(f1, s, '\n');
//			cout << "\t" << s << endl;
//		}
//		f1.close();
//	}
//};
//int main()
//{
//	ifstream f1;
//	ofstream f2;
//	int size = 25;
//	Appointments** list=new Appointments*[size];
//	list[0]=new Onetime("see the dentist",2,3,2023);
//	list[0]->save("Onetime", list[0]->toString());
//	list[1] = new Daily("Use mobile phone", 3, 3, 2023);
//	list[1]->save("Daily", list[1]->toString());
//	list[2] = new Monthly("Go to university", 5, 4, 2023);
//	list[2]->save("Monthly", list[2]->toString());
//	list[3] = new Onetime("Preparing exam", 2, 3, 2023);
//	list[3]->save("Onetime", list[3]->toString());
//	list[4] = new Daily("Watch the series", 3, 3, 2023);
//	list[4]->save("Daily", list[4]->toString());
//	int ch,s=5;
//	cout << "Press 1 if you want to add any appointment else press 2: ";
//	cin >> ch;
//	string type,dis;
//	int d, y, m, choice = 1, a;
//	while (ch == 1)
//	{
//		cout << "Enter the type of the appointment:";
//		cin.ignore();
//		getline(cin, type);
//		cout << "Enter the description: ";
//		getline(cin, dis);
//		cout << "Enter the date: ";
//		cin >> d;
//		cout << "Enter the month: ";
//		cin >> m;
//		cout << "Enter the year: ";
//		cin >> y;
//		if (type == "Onetime") {
//			list[s] = new Onetime(dis, d, m, y);
//			list[s]->save("Onetime", list[s]->toString());
//		}
//		else if (type == "Daily") {
//			list[s] = new Daily(dis, d, m, y);
//			list[s]->save("Daily", list[s]->toString());
//		}
//		else if (type == "Monthly") {
//			list[s] = new Monthly(dis, d, m, y);
//			list[s]->save("Monthly", list[s]->toString());
//			
//		}
//		else {
//			cout << "Enter the correct type." << endl;
//			continue;
//		}
//		s++;
//		cout << "Press 1 if you want to add another appointment: ";
//		cin >> ch;
//	    system("cls");
//	}
//	while (choice == 1)
//	{
//		cout << "For Checking the appointments: " << endl;
//		cout << "Enter the type of the appointment:";
//		cin.ignore();
//		getline(cin, type);
//		if (type == "Onetime") {
//			Onetime obj1;
//			obj1.load();
//		}
//		else if (type == "Daily") {
//			Daily obj1;
//			obj1.load();
//		}
//		else if (type == "Monthly") {
//			Monthly obj1;
//			obj1.load();
//		}
//		else {
//			cout << "Enter the correct type." << endl;
//			continue;
//		}
//		cout << "Press 1 if you want to do again: ";
//		cin >> choice;
//		if (choice == 1)
//			system("cls");
//	}
//	for (int i = 0; i < s; i++)
//	{
//		delete list[i];
//		list[i] = NULL;
//	}
//	delete[]list;
//	list = NULL;
//}