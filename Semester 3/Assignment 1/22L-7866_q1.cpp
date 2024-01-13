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
		if (size == 0)
		{
			insertAtHead(obj);
		}
		else
		{
			Node<T>* newNode = new Node<T>(obj, NULL);
			tail->setNext(newNode);
			tail = newNode;
			size++;
		}
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
		if (index < size && index>=0)
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
		else
		{
			cout << "You inserted incorrect index." << endl;
		}
	}
	void print() const
	{
		if (size != 0)
		{
			Node<T>* p = head->getNext();
			cout << "{";
			while (p != NULL)
			{
				cout << p->get() <<",";
				p = p->getNext();
			}
			cout << "\b}" << endl;
		}
		else
			cout << "{}" << endl;
	}
	void union1(SortedSet<T> const& otherset)
	{
		SortedSet<T> List3;
		Node<T>* p1 = head->getNext();
		Node<T>* p2 = otherset.head->getNext();
		for (int i = 0; i < (size + otherset.size); i++)
		{
			if (p2 == NULL)
			{
				List3.insertAtTail(p1->get());
				p1 = p1->getNext();
			}
			else if (p1 == NULL)
			{
				List3.insertAtTail(p2->get());
				p2 = p2->getNext();
			}
			else 
			{
				if (p1->get() <= p2->get())
				{
					List3.insertAtTail(p1->get());
					p1 = p1->getNext();
				}
				else
				{
					List3.insertAtTail(p2->get());
					p2 = p2->getNext();
				}
			}
		}
		p1 = List3.head;
		p2 = List3.head->getNext();
		int s = List3.size;
		for (int i = 0; i <s; i++)
		{
			if (p2->get() == p1->get())
			{
				Node<T>* temp = p2;
				p2 = p2->getNext();
				p1->setNext(temp->getNext());
				delete temp;
				List3.size--;
			}
			else 
			{
				p1 = p2;
				p2 = p2->getNext();
			}
		}
		Node<T>* temp;
		Node<T>* current = head->getNext();
		while (current != NULL)
		{
			temp = current;
			current = current->getNext();
			delete temp;
			size--;
		}
		current = List3.head->getNext();
		for (int i = 0; i < List3.size; i++)
		{
			insertAtTail(current->get());
			current = current->getNext();
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
	SortedSet <int> List1;
	List1.insert(5);
	List1.insert(4);
	List1.insert(3);
	/*List1.insert(4);
	List1.insert(5);*/
	//List1.delete1(0);
	cout << "List 1: ";
	List1.print();

	SortedSet <int> List2;
	List2.insert(1);
	List2.insert(2);
	List2.insert(3);
	/*List2.insert(2);*/
	/*List2.insert(13);*/
	cout << "List 2: ";
	List2.print();

	List1.union1(List2);
	cout << "After union, List 1: ";
	List1.print();
}