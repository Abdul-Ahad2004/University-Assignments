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
	int height;
public:
	TreeNode()
	{
		size = 1;
		keyword = "";
		height = 0;
		URL = new string[size];
		this->left = NULL;
		this->right = NULL;
	}
	TreeNode(TreeNode& obj)
	{
		size = obj.size;
		keyword = obj.keyword;
		height = obj.height;
		URL = new string[obj.getsize()];
		for (int i = 0; i < obj.getsize(); i++)
		{
			URL[i] = obj.URL[i];
		}
		this->left = obj.left;
		this->right = obj.right;
	}
	TreeNode(TreeNode* obj)
	{
		size = obj->size;
		keyword = obj->keyword;
		height = obj->height;
		URL = new string[obj->getsize()];
		for (int i = 0; i < obj->getsize(); i++)
		{
			URL[i] = obj->URL[i];
		}
		this->left = obj->left;
		this->right = obj->right;
	}
	void setHeight(int h)
	{
		height = h;
	}
	int getHeight()
	{
		return height;
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
class AVL
{
	TreeNode* root;
public:
	AVL()
	{
		root = NULL;
	}
	void setroot(TreeNode* object) //setter
	{
		root = new TreeNode(object);
	}
	void setroot1(TreeNode* r)
	{
		root = r;
	}
	int max(int a, int b)
	{
		if (a > b)
			return a;
		return b;
	}
	int Height(TreeNode* node)
	{
		if (node == NULL)
		{
			return 0;
		}
		return 1 + max(Height(node->getLeft()), Height(node->getRight()));
	}
	TreeNode* avlInsert(TreeNode* root, TreeNode& object)
	{
		if (root == NULL)
		{
			// If the current node is NULL, create a new node with the given keyword and URL.
			TreeNode* temp = new TreeNode(object);
			return temp;
		}
		else if (object.getKeyword() == root->getKeyword())
		{
			string* url = root->getURL();
			string* url1 = object.getURL();
			if (url1[0] != url[root->getsize() - 1])
			{
				string* a = new string[root->getsize() + 1];
				int i;
				for (i = 0; i < root->getsize(); i++)
				{
					a[i] = url[i];
				}
				a[i] = url1[0];
				delete[] url;
				root->setsize(root->getsize() + 1);
				root->setURL1(a);
			}
			return root;
		}
		else if (object.getKeyword() < root->getKeyword())
		{
			// If the keyword is less than the current node, then recursively insert in the left sub-tree.
			root->setLeft(avlInsert(root->getLeft(), object));
		}
		else if (object.getKeyword() > root->getKeyword())
		{
			// If the keyword is greater than the keyword at the current node, then recursively insert in the right sub-tree.
			root->setRight(avlInsert(root->getRight(), object));
		}

		int balance = Height(root->getLeft()) - Height(root->getRight());

		if (balance > 1 && object.getKeyword() < root->getLeft()->getKeyword())
		{
			// Left imbalance
			return singleRightRotate(root);
		}
		else if (balance < -1 && object.getKeyword() > root->getRight()->getKeyword())
		{
			// Right imbalance
			return singleLeftRotate(root);
		}
		else if (balance > 1 && object.getKeyword() > root->getLeft()->getKeyword())
		{
			// Left-right imbalance
			root->setLeft(singleLeftRotate(root->getLeft()));
			return singleRightRotate(root);
		}
		else if (balance < -1 && object.getKeyword() < root->getRight()->getKeyword())
		{
			// Right-left imbalance
			root->setRight(singleRightRotate(root->getRight()));
			return singleLeftRotate(root);
		}

		return root;
	}
	TreeNode* singleRightRotate(TreeNode* k2)
	{
		if (k2 == NULL)
			return NULL;
		TreeNode* k1 = k2->getLeft();
		k2->setLeft(k1->getRight());
		k1->setRight(k2);
		int h = max(Height(k2->getLeft()), Height(k2->getRight()));
		k2->setHeight(h + 1);
		h = max(Height(k1->getLeft()), k2->getHeight());
		k1->setHeight(h + 1);
		return k1;
	}

	TreeNode* singleLeftRotate(TreeNode* k2)
	{
		if (k2 == NULL)
			return NULL;
		TreeNode* k1 = k2->getRight();
		k2->setRight(k1->getLeft());
		k1->setLeft(k2);
		int h = max(Height(k2->getLeft()), Height(k2->getRight()));
		k2->setHeight(h + 1);
		h = max(k2->getHeight(), Height(k1->getRight()));
		k1->setHeight(h + 1);
		return k1;

	}
	TreeNode* doubleRightLeftRotate(TreeNode* k1)
	{
		//Single right rotate
		k1->setRight(singleRightRotate(k1->getRight()));
		//Single left rotate
		return singleLeftRotate(k1);
	}
	TreeNode* doubleLeftRightRotate(TreeNode* k3)
	{
		//Single left Rotate
		k3->setLeft(singleLeftRotate(k3->getLeft()));
		//Single Right Rotate
		return singleRightRotate(k3);
	}
	/*void inorder(TreeNode* root)
	{
		if (root != NULL)
		{
			inorder(root->getLeft());
			cout << root->getKeyword() << " ";
			inorder(root->getRight());
		}
	}*/
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
	AVL tree;
	f1.open(file + ".txt");
	if (f1.is_open())
	{
		cout << "\nFile loaded successfully.\n" << endl;
		cout << endl;
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
						tree.setroot1(tree.avlInsert(tree.getroot(), newNode));
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
					tree.setroot1(tree.avlInsert(tree.getroot(), newNode));
			}
		}
		f1.close();
		string key;
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
			cout << size << " result(s) found: " << endl;
			for (int i = 0; i < size; i++)
			{
				cout << i + 1 << ". " << url[i] << endl;
			}
		}
	}
	else
	{
		cout << "File is not found!!" << endl;
	}
}
