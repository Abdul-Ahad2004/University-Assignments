#include<iostream>
using namespace std;
template <typename T>
class Node
{
	T data;
	Node* nextNode;
public:
	Node()
	{
		data = 0;
		nextNode = NULL;
	}
	Node(const T& d, Node* next = NULL)
	{
		data = d;
		nextNode = next;
	}
	T get()
	{
		return data;
	}
	void set(T d)
	{
		data = d;
	}
	Node<T>* getNext()
	{
		return nextNode;
	}
	void setNext(Node<T>* next)
	{
		nextNode = next;
	}
};
template <typename T>
class SortedSet
{
	Node<T>* head;
	Node<T>* tail;
	int size;
public:
	SortedSet()
	{
		head = tail = new Node<T>();
		size = 0;
	}
	void insertAtHead(const T& obj)
	{
		Node<T>* newNode = new Node<T>(obj, head->getNext());
		head->setNext(newNode);
		if (size == 0)
		{
			tail = newNode;
		}
		size++;
	}
	void insertAtTail(const T& obj)
	{
		Node<T>* newNode = new Node<T>(obj, NULL);
		tail->setNext(newNode);
		tail = newNode;
		size++;
	}
	int getsize()
	{
		return size;
	}
	void insert(T const data)
	{
		int count = 0;
		Node<T>* p = head->getNext();
		while (p != NULL)
		{
			if (p->get() == data)
			{
				count = 1;
				break;
			}
			p = p->getNext();
		}
		if (count == 0)
		{
			if (size == 0)
			{
				insertAtHead(data);
			}
			else if (data <= (head->getNext())->get())
			{
				insertAtHead(data);
			}
			else if (data >= tail->get())
			{
				insertAtTail(data);
			}
			else
			{
				Node<T>* newNode = new Node<T>(data, NULL);
				Node<T>* current = head->getNext();
				Node<T>* lastcurrent = head;
				while (current != NULL && data >= current->get())
				{
					lastcurrent = current;
					current = current->getNext();
				}
				lastcurrent->setNext(newNode);
				newNode->setNext(current);
				size++;
			}
		}
	}
	void delete1(int const index)
	{
		if (index < size && index >= 0)
		{
			Node<T>* current = head->getNext();
			Node<T>* lastcurrent = head;
			int count = 0;
			while (count < index)
			{
				lastcurrent = current;
				current = current->getNext();
				count++;
			}
			lastcurrent->setNext(current->getNext());
			if (index == size - 1)
			{
				tail = lastcurrent;
			}
			delete current;
			size--;
		}
	}
	void print() const
	{
		if (size != 0)
		{
			Node<T>* p = head->getNext();
			while (p != NULL)
			{
				cout << p->get() << "->";
				p = p->getNext();
			}
			cout << "NULL" << endl;
		}
		else
			cout << "NULL" << endl;
	}
	friend void reverse(SortedSet<T>& List)
	{
		if (List.getsize() !=0 && List.getsize() != 1)
		{
		   Node<T>* current = List.head->getNext();
		   List.tail= List.head->getNext();
		   Node<T>* temp = current->getNext();
		   Node<T>* lastcurrent = NULL;
		   for(int i=1;i<=List.size;i++)
		   {
			   current->setNext(lastcurrent);
		   	   lastcurrent = current;
		   	   current = temp;
			   if (temp != NULL)
			   {
				   temp = temp->getNext();
			   }
		   }
		   List.head->setNext(lastcurrent);
		}
	}
	~SortedSet()
	{
		Node<T>* temp;
		Node<T>* current = head->getNext();
		while (current != NULL)
		{
			temp = current;
			current = current->getNext();
			delete temp;
		}
		delete head;
		head = NULL;
	}
};
int main()
{
	SortedSet <int> List;
	List.insert(1);
	List.insert(2);
	List.insert(3);
	List.insert(4);
	List.insert(5);
	
	cout << "List 1: ";
	List.print();
	reverse(List);
	cout << "After reverse: " << endl;
	cout << "List 1: ";
	List.print();
}