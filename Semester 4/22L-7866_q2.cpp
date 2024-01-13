#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>
using namespace std;
class TreeNode
{
private:
	string keyword;
	string* URL;
	TreeNode* left;
	TreeNode* right;
	int size;
public:
	TreeNode()
	{
		size = 1;
		keyword = "";
		URL = new string[size];
		this->left = NULL;
		this->right = NULL;
	}
	TreeNode(TreeNode* obj)
	{
		size = obj->size;
		keyword = obj->keyword;
		URL = new string[obj->getsize()];
		for (int i = 0; i < obj->getsize(); i++)
		{
			URL[i] = obj->URL[i];
		}
		this->left = obj->left;
		this->right = obj->right;
	}
	string getKeyword()
	{
		return  keyword;
	}
	void setKeyword(string object)
	{
		keyword = object;
	}
	int getsize()
	{
		return size;
	}
	void setsize(int s)
	{
		size = s;
	}
	string* getURL()
	{
		return  URL;
	}
	void setURL(string object)
	{
		URL[size - 1] = object;
	}
	void setURL1(string* object)
	{
		URL = new string[getsize()];
		for (int i = 0; i < getsize(); i++)
		{
			URL[i] = object[i];
		}
	}
	TreeNode* getLeft()
	{
		return left;
	}
	void setLeft(TreeNode* l)
	{
		if (l != NULL)
		{
			left = new TreeNode(l);
		}
		else
			this->left = NULL;
	}
	TreeNode* getRight()
	{
		return right;
	}
	void setRight(TreeNode* r)
	{
		if (r != NULL)
		{
			right = new TreeNode(r);
		}
		else
			this->right = NULL;
	}
};
class BST
{
	TreeNode* root;
public:
	BST()
	{
		root = NULL;
	}
	void setroot(TreeNode* object) //setter
	{
		root = new TreeNode();
		root->setKeyword(object->getKeyword());
		root->setURL1(object->getURL());
		root->setLeft(NULL);
		root->setRight(NULL);
	}
	void insert(TreeNode object) //iterative function to insert node in BST
	{
		TreeNode* p, * q;
		p = root;
		q = root;
		while (object.getKeyword() != p->getKeyword() && q != NULL)
		{
			p = q;
			if (object.getKeyword() < p->getKeyword())
				q = p->getLeft();
			else
				q = p->getRight();
		}
		if (object.getKeyword() == p->getKeyword())
		{
			string* url = p->getURL();
			string* url1 = object.getURL();
			if (url1[0] != url[p->getsize() - 1])
			{
				string* a = new string[p->getsize() + 1];
				int i;
				for (i = 0; i < p->getsize(); i++)
				{
					a[i] = url[i];
				}
				a[i] = url1[0];
				delete[]url;
				p->setsize(p->getsize() + 1);
				p->setURL1(a);
			}
		}
		else if (object.getKeyword() < p->getKeyword())
			p->setLeft(&object);
		else
			p->setRight(&object);

	}
	TreeNode* search(const string& x)const
	{
		TreeNode* t = root;
		while (t != NULL)
		{
			if (x < t->getKeyword())
				t = t->getLeft();
			else if (x > t->getKeyword())
				t = t->getRight();
			else
				return t; //Match
		}
		return NULL;//No Match	
	}
	TreeNode* findMin(TreeNode* root)
	{
		if (root == NULL)
			return NULL;
		if (root->getLeft() == NULL)
			return root;
		return findMin(root->getLeft());
	}
	TreeNode* remove(TreeNode* root, string info)
	{
		TreeNode* t;
		if (info < root->getKeyword())
		{
			t = remove(root->getLeft(), info);
			root->setLeft(t);
		}
		else if (info>root->getKeyword())
		{
			t = remove(root->getRight(), info);
			root->setRight(t);
		}
		else if (root->getLeft() != NULL && root->getRight() != NULL)
		{
			TreeNode* minNode;
			minNode = findMin(root->getRight());
			root->setKeyword(minNode->getKeyword());
			t = remove(root->getRight(), minNode->getKeyword());
			root->setRight(t);
		}
		else
		{
			TreeNode* deleteNode = root;
			if (root->getLeft() == NULL)
				root = root->getRight();
			else if (root->getRight() == NULL)
				root = root->getLeft();
			else
				root = NULL;

			delete deleteNode;

		}
		return root;
	}
	TreeNode* getroot()
	{
		return root;
	}
};
int main()
{
	string file;
	cout << "Enter a filename: ";
	getline(cin, file);
	ifstream f1;
	int lines = 0;
	string s;
	BST tree;
	f1.open(file + ".txt");
	if (f1.is_open())
	{
		cout << "\nFile loaded successfully.\n" << endl;
		cout << "Enter any key to continue...";
		_getch();
		while (getline(f1, s))
			lines++;
		f1.close();
		int length;
		string s1, s2;
		bool check = false;
		f1.open(file + ".txt");
		for (int i = 0; i < lines; i++)
		{
			s1 = "";
			s2 = "";
			getline(f1, s);
			if (s == "")
				continue;
			length = s.length();
			if (i == 0)
			{
				check = true;
			}
			for (int j = 2; j < length; j++)
			{
				s1 += s[j];
			}
			i++;
			getline(f1, s);
			length = s.length();
			int j;
			for (j = 0; j < length; j++)
			{
				if (int(s[j]) == 32)
				{
					TreeNode newNode;
					newNode.setURL(s1);
					newNode.setKeyword(s2);
					s2 = "";
					if (check)
					{
						tree.setroot(&newNode);
						check = false;
					}
					else
						tree.insert(newNode);
				}
				else
					s2 += s[j];
			}
			if (j == length)
			{
				TreeNode newNode;
				newNode.setURL(s1);
				newNode.setKeyword(s2);
				s2 = "";
				if (check)
				{
					tree.setroot(&newNode);
					check = false;
				}
				else
					tree.insert(newNode);
			}
		}
		f1.close();
		string key;
		int choice1;
		while (1)
		{
			system("cls");
			cout << "Press 1 to insert a keyword\nPress 2 to search a keyword\nPress 3 to delete a keyword\nPress 4 to exit the program\nEnter your choice: ";
			cin >> choice1;
			while (choice1 < 0 || choice1>4)
			{
				cout << "Please enter a valid choice: ";
				cin >> choice1;
			}
			if (choice1 == 1)
			{
				system("cls");
				cout << "Please enter a keyword to insert: ";
				cin >> key;
				string url,url1;
				C:cout << "\nEnter the URL related to keyword: http://www.";
				cin.ignore();
				getline(cin, url);
				if (url.find('.') == -1)
				{
					cout << "Enter a valid URL!!" << endl;
					goto C;
				}
				url1 = "http://www." + url;
				TreeNode newNode;
				newNode.setURL(url1);
				newNode.setKeyword(key);
				tree.insert(newNode);
				cout << "\nKeyword inserted successfully!!" << endl;
			}
			else if (choice1 == 2)
			{
				system("cls");
				cout << "Please enter a word to search: ";
				cin >> key;
				cout << endl;
				TreeNode* search = tree.search(key);
				if (search == NULL)
				{
					cout << "No result found!!" << endl;
				}
				else
				{
					int size = search->getsize();
					string* url = search->getURL();
					cout << size << " result(s) found: " << endl << endl;
					for (int i = 0; i < size; i++)
					{
						cout << i + 1 << ". " << url[i] << endl;
					}
				}
			}
			else if(choice1==3)
			{
				system("cls");
				cout << "Please enter a keyword to delete: ";
				cin >> key;
				cout << endl;
				TreeNode* search = tree.search(key);
				TreeNode* root = tree.getroot();
				if (search == NULL)
				{
					cout << "No result found!!" << endl;
				}
				else
				{
					tree.remove(root, key);
					cout << "\nKeyword deleted successfully!!" << endl;
				}
			}
			else
			{
				break;
				system("exit");
			}
			cout << "\nEnter any key to continue...";
			_getch();
		}
	}
	else
	{
		cout << "File is not found!!" << endl;
	}
}
