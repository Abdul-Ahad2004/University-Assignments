#include<iostream>
using namespace std;
int lines=0;
int searchdata(char a[]);
class book
{
public:
	
	char* p = new char[100];// Publication_ID;
	char* p1 = new char[100];//book_title
	char* p2 = new char[100];// author
	char* p3 = new char[100];//list of subscribers
	~book()
	{
		delete[]p;
		p = NULL;
		delete[]p1;
		p1 = NULL;
		delete[]p2;
		p2 = NULL;
		delete[]p3;
		p3 = NULL;
	}
};


book arr[100];
void Addnewbook()
{
	int i = lines;
	cout << "Enter the Publication ID of the book: ";
	cin.ignore();
	cin.getline(arr[i].p, 100);
	int a=searchdata(arr[i].p);
	while (a != -1)
	{
		cout << "Enter the unique publication id: ";
		cin.getline(arr[i].p, 100);
		a = searchdata(arr[i].p);
	}
	cout << "Enter the Title of the book: ";
	cin.getline(arr[i].p1, 100);
	cout << "Enter the name of author of the book: ";
	cin.getline(arr[i].p2, 100);
	cout << "Enter the name of Patron Subscriber of the book: ";
	cin.getline(arr[i].p3, 100);
	lines++;
}
int length(char a[])
{
	int count = 0;
	for (int i = 0; a[i] != '\0'; i++)
	{
		count++;
	}
	return count;
}
int searchdata(char a[])
{
	int l = length(a);
	int k = 0, count = 0;
	for (int i = 0; i < lines; i++)
	{
		if (a[k] == arr[i].p[k])
		{
			k++; count++;
			for (int j = 1; j < l; j++)
			{
				if (a[k] == arr[i].p[k]) {
					count++; k++;
				}
				if (count == l)
					return i;
			}
		}
		count = 0; k = 0;
	}
	return -1;
}
void deletebook(int i)
{
	for (int j = i; j < lines - 1; j++)
	{
		arr[j].p = arr[j + 1].p;
		arr[j].p1 = arr[j + 1].p1;
		arr[j].p2= arr[j + 1].p2;
		arr[j].p3 = arr[j + 1].p3;


	}
	lines--;
}
void display()
{
	cout << "The available books are: " << endl;
	for (int i = 0; i < lines; i++)
	{
		cout << i + 1 << ". Publication Id:" << arr[i].p << "\n\t";
		cout << "Book title:" << arr[i].p1 << "\n\t";
		cout << "Author name:" << arr[i].p2 << "\n\t";
		cout << "Subscriber name:" << arr[i].p3 << "\n";

	}
}
void editbook(int i)
{
	cout << "Enter the  new Publication ID of the book: ";
	cin.getline(arr[i].p, 100);
	cout << "Enter the  new Title of the book: ";
	cin.getline(arr[i].p1, 100);
	cout << "Enter the name of author of the book: ";
	cin.getline(arr[i].p2, 100);
	cout << "Enter the name of Patron Subscriber of the book: ";
	cin.getline(arr[i].p3, 100);
}
int main()
{
	char repeat = '1';
	int choice;
	cout << "*****Welcome to the library management sytem*****";
	cout << "\n           MENU     " << endl;
	while (repeat == '1') {
		cout << "1.Add a new book\n2.Edit details of an available book\n3.Delete a book\n4.Display all books in the Library" << endl;
		cout << "\nEnter your choice: ";
		cin >> choice;
		while (choice < 0 || choice>4)
		{
			cout << "Enter a valid choice." << endl;
			cin >> choice;
		}
		if (choice == 1)
		{
			Addnewbook();
		}
		else if (choice == 2)
		{
			char* p6 = new char[100];
			cout << "Enter the Publication ID of the book which you want to edit: ";
			cin.ignore();
			cin.getline(p6, 100);
			int s = searchdata(p6);
			if (s != -1)
			{
				editbook(s);
				cout << "Book details has been modified." << endl;
			}
			else
				cout << "This book is not availabe in library." << endl;
			delete[]p6;
			p6 = NULL;

		}
		else if (choice == 3)
		{
			char* p6 = new char[100];
			cout << "Enter the Publication ID of the book which you want to delete: ";
			cin.ignore();
			cin.getline(p6, 100);
			int s = searchdata(p6);
			if (s != -1)
			{
				deletebook(s);
				cout << "Book has been deleted." << endl;
			}
			else
				cout << "This book is not availabe in library." << endl;
			delete[]p6;
			p6 = NULL;

		}
		else if (choice == 4)
		{
			display();
		}	
		cout << "Press 1 if you want to again.";
		cin >> repeat;
		system("cls");
	}
}