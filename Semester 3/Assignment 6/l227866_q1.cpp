#include<iostream>
using namespace std;
class Node 
{
private:
	int data;
	int age;
	int number;
	Node* nextNode;
public:
	Node()
	{
		nextNode = NULL;
	}
	Node(int d, int a,int n)
	{
		data = d;
		age = a;
		number = n;
	}
	Node(const Node &n)
	{
		data = n.data;
		age = n.age;
		number = n.number;
	}
	int getdata()
	{
		return data;
	}
	int getage()
	{
		return age;
	}
	void setdata(int obj)
	{
		data= obj;
	}
	int getnumber()
	{
		return number;
	}
	void setnumber(int obj)
	{
		number = obj;
	}
	void setage(int obj)
	{
		age = obj;
	}
	Node* getNext()
	{
		return nextNode;
	}
	void setNext(Node* nextNode)
	{
		this->nextNode = nextNode;
	}
};
class queue
{
private:
	Node* front, * rear;
	int count;
	int size;
public:
	queue() //constructor
	{
		front = new Node();
		rear = NULL;
		size = 0;
		count = 0;
	}
	void enqueue(Node node) //push elements/data into queue
	{
		if (front->getNext() == NULL)
		{
			Node* newNode = new Node(node);
			front->setNext(newNode);
			newNode->setNext(NULL);
			rear = newNode;
			count += newNode->getdata();
		}
		else if (rear->getage()>=node.getage())
		{
			Node* newNode = new Node(node);
			rear->setNext(newNode);
			newNode->setNext(NULL);
			rear = newNode;
			count += newNode->getdata();
		}
		else if (node.getage() >= (front->getNext())->getage())
		{
			Node* newNode = new Node(node);
			Node* temp = front->getNext();
			front->setNext(newNode);
			newNode->setNext(temp);
			count += newNode->getdata();
		}
		else
		{
			Node* newNode = new Node(node);
			Node* temp = front->getNext();
			Node* temp1 = front;
			while (temp != NULL)
			{
				if (temp->getage() <= node.getage())
				{
					temp1->setNext(newNode);
					newNode->setNext(temp);
					count += newNode->getdata();
					break;
				}
				temp = temp->getNext();
				temp1 = temp1->getNext();
			}
		}
		size++;
	}
	void enqueue1(Node node)
	{
		if (front->getNext() != NULL)
		{
			Node* newNode = new Node(node);
			rear->setNext(newNode);
			newNode->setNext(NULL);
			rear = newNode;
		}
		else
		{
			Node* newNode = new Node(node);
			front->setNext(newNode);
			newNode->setNext(NULL);
			rear = newNode;
		}
		size++;
	}
	Node dequeue() //remove data/element from a queue
	{
		if (front->getNext() != NULL)
		{
			int d= (front->getNext())->getdata();
			int a = (front->getNext())->getage();
			int n = (front->getNext())->getnumber();
			Node* p = front->getNext();
			front->setNext(p->getNext());
			delete p;
			size--;
			return Node(d,a,n);
		}
	}
	int getsize()
	{
		return size;
	}
	int getcount()
	{
		return count;
	}
	bool isEmpty() //function to check queue is empty
	{
		if (size == 0)
			return true;
		return false;
	}
	Node getfront()
	{

		return Node((front->getNext())->getdata(), (front->getNext())->getage(), (front->getNext())->getnumber());
	}
	~queue() //destructor
	{
		while (!isEmpty())
			dequeue();
	}
	
};
void setqueue(queue& q1, queue& q2, queue& q3, queue& q4, Node node)
{
	if (q1.isEmpty())
		q1.enqueue(node);
	else if (q2.isEmpty())
		q2.enqueue(node);
	else if (q3.isEmpty())
		q3.enqueue(node);
	else if (q4.isEmpty())
		q4.enqueue(node);
	else if (q1.getcount() <= q2.getcount() && q1.getcount() <= q3.getcount() && q1.getcount() <= q4.getcount())
		q1.enqueue(node);
	else if (q2.getcount() <= q1.getcount() && q2.getcount() <= q3.getcount() && q2.getcount() <= q4.getcount())
		q2.enqueue(node);
	else if (q3.getcount() <= q2.getcount() && q3.getcount() <= q1.getcount() && q3.getcount() <= q4.getcount())
		q3.enqueue(node);
	else
		q4.enqueue(node);
}
void print(queue& q1, queue& q2, queue& q3, queue& q4)
{
	cout << endl;
	cout << "Queue 1: ";
	for (int i = 0; i < q1.getsize(); i++)
	{
		Node temp = q1.dequeue();
		cout << " C" << temp.getnumber() << "(" << temp.getdata() << "," << temp.getage() << ")" <<" ,";
		q1.enqueue1(temp);
	}
	cout <<"\b "<< endl;
	cout << "Queue 2: ";
	for (int i = 0; i < q2.getsize(); i++)
	{
		Node temp = q2.dequeue();
		cout << " C" << temp.getnumber() << "(" << temp.getdata() << "," << temp.getage() << ")" << " ,";
		q2.enqueue1(temp);
	}
	cout << "\b " << endl;
	cout << "Queue 3: ";
	for (int i = 0; i < q3.getsize(); i++)
	{
		Node temp = q3.dequeue();
		cout << " C" << temp.getnumber() << "(" << temp.getdata() << "," << temp.getage() << ")" << " ,";
		q3.enqueue1(temp);
	}
	cout << "\b " << endl;
	cout << "Queue 4: ";
	for (int i = 0; i < q4.getsize(); i++)
	{
		Node temp = q4.dequeue();
		cout << " C" << temp.getnumber() << "(" << temp.getdata() << "," << temp.getage() << ")" << " ,";
		q4.enqueue1(temp);
	}
	cout << "\b " << endl;
}
int main()
{
	queue q1;
	queue q2;
	queue q3;
	queue q4;
	int data, age,counter=0;
	char choice;
	cout << "Do you want to pay your bills (Y/N): ";
	cin >> choice;
	while (choice != 'Y' && choice != 'N')
	{
		cout << "Enter valid character!!!" << endl;
		cout << "Do you want to pay your bills (Y/N): ";
		cin >> choice;
	}
	if (choice == 'Y')
	{
		while (choice == 'Y')
		{
			counter++;
			cout << "Customer Number: " << counter << endl;
			cout << "Please enter how many items do you want to purchase: ";
			cin >> data;
			while (data <= 0)
			{
				cout << "Enter the valide number of items!!" << endl;
				cout << "Please enter how many items do you want to purchase: ";
				cin >> data;
			}
			cout << "Please enter your age: ";
			cin >> age;
			while (age<= 0)
			{
				cout << "Enter the valide age!!" << endl;
				cout << "Please enter your age: ";
				cin >> age;
			}
			Node newNode(data, age, counter);
			setqueue(q1, q2, q3, q4, newNode);
			print(q1, q2, q3, q4);
			cout << endl;
			cout << "Do you want to pay your bills (Y/N): ";
			cin >> choice;
			while (choice != 'Y' && choice != 'N')
			{
				cout << "Enter valid character!!!" << endl;
				cout << "Do you want to pay your bills (Y/N): ";
				cin >> choice;
			}
			system("cls");
		}
	}
    cout << "Exit!!!" << endl;
}