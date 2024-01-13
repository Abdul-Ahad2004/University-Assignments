#include<iostream>
using namespace std;
class Course
{
	int id;
	char* title;
	int teacher_id;
public:
	Course()
	{
		id = 0;
		title = NULL;
		teacher_id = 0;
	}

	Course(int i, char*& t)
	{
		id = i;
		cout << "Enter the course name: ";
		cin.getline(t, 50);
		title = new char[strlen(t) + 1];
		for (int i = 0; t[i] != '\0'; i++)
		{
			title[i] = t[i];
		}
		title[strlen(t)] = '\0';
	}
	void setter_title(char* t)
	{
		title = new char[strlen(t) + 1];
		for (int i = 0; t[i] != '\0'; i++)
		{
			title[i] = t[i];
		}
		title[strlen(t)] = '\0';
	}
	void setter_id(int i)
	{
		id = i;
	}
	void setter_techerid(int i)
	{
		teacher_id = i;
	}
	int getid()
	{
		return id;
	}
	int getteacher_id()
	{
		return teacher_id;
	}
	char* gettitle()
	{
		return title;
	}
	void display()
	{
		cout << "Id:" << id << "\n\tname: " << title << "\n\ttid: " << teacher_id << endl;
	}
	~Course()
	{
		delete[]title;
		title = NULL;
	
	}
};
class Teacher
{
	int id;
	char* name;
	int courses;
	Course* arr;
public:
	Teacher()
	{
		id = 0;
		name = NULL;
		courses = 0;
		arr = NULL;
	}

	Teacher(int i, char*& a, Course* C)
	{
		id = i;
		cout << "Enter the teacher name: ";
		cin.getline(a, 50);
		C->setter_techerid(i);
		name = new char[strlen(a) + 1];
		for (int i = 0; a[i] != '\0'; i++)
		{
			name[i] = a[i];
		}
		name[strlen(a)] = '\0';
		courses = 1;
		arr = new Course[courses];
		for (int i = 0; i < courses; i++)
		{
			char* a1;
			int e, f;
			a1 = C->gettitle();
			arr[i].setter_title(a1);
			e = C->getid();
			arr[i].setter_id(e);
			f = C->getteacher_id();
			arr[i].setter_techerid(f);
		}

	}
	void AddCourses(Course* C)
	{
		C->setter_techerid(getID());
		Course* a = new Course[courses + 1];
		for (int i = 0; i < courses; i++)
		{
			char* a1;
			int e, f;
			a1 = arr[i].gettitle();
			a[i].setter_title(a1);
			e = arr[i].getid();
			a[i].setter_id(e);
			f = arr[i].getteacher_id();
			a[i].setter_techerid(f);
		}
		delete[]arr;
		arr = a;
		for (int i = courses; i < courses + 1; i++)
		{
			char* a1;
			int e, f;
			a1 = C->gettitle();
			arr[i].setter_title(a1);
			e = C->getid();
			arr[i].setter_id(e);
			f = C->getteacher_id();
			arr[i].setter_techerid(f);
		}
		courses++;
	}
	int getID()
	{
		return id;
	}
	void DisplayCourses()
	{
		cout << "Teacher id: " << id << endl;
		cout << "Teacher's name: " << name << endl;
		cout << "Detail of Courses taught by this teacher are following:" << endl;
		for (int i = 0; i < courses; i++)
		{
			cout << i + 1 << "." << endl;
			cout << "\tId: " << arr[i].getid() << "\n\t\Title: " << arr[i].gettitle() << "\n\t\Teacher id: " << arr[i].getteacher_id() << endl;
		}
	}
	~Teacher()
	{
		delete[]name;
		delete[]arr;
		arr = NULL;
		name = NULL;
		
	}
};
int main()
{
	char* arr = new char[50];
	cout << "For C1: " << endl;
	Course C1(001, arr);
	char* arr1 = new char[50];
	cout << "For T1: " << endl;
	Teacher T1(111, arr1, &C1);
	char* arr2 = new char[50];
	cout << "For C2: " << endl;
	Course C2(002, arr2);
	T1.AddCourses(&C2);
	cout << "T1 details:" << endl;
	T1.DisplayCourses();
	delete[]arr;
	delete[]arr1;
	delete[]arr2;
	arr = NULL;
	arr1 = NULL;
	arr2 = NULL;
}