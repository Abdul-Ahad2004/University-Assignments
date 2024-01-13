#include<iostream>
#include<string>
using namespace std;
template<class T>
class Node 
{
private:
	T obj;
	Node<T>* nextNode;
public:
	Node()
	{
		nextNode = NULL;
	}
	T get()
	{
		return obj;
	}
	void set(T obj)
	{
		this->obj = obj;
	}

	Node<T>* getNext()
	{
		return nextNode;
	}
	void setNext(Node<T>* nextNode)
	{
		this->nextNode = nextNode;
	}
};
template <typename T>
class queue
{
private:
	Node<T>* front, * rear;
	int size;
public:
	queue() //constructor
	{
		front = new Node<T>();
		rear = NULL;
		size = 0;
	}
	void enqueue(const T& data) //function to insert element/data into queue
	{
		if (front->getNext() != NULL)
		{
			Node<T>* newNode = new Node<T>();
			newNode->set(data);
			rear->setNext(newNode);
			newNode->setNext(NULL);
			rear = newNode;
		}
		else
		{
			Node<T>* newNode = new Node<T>();
			newNode->set(data);
			front->setNext(newNode);
			newNode->setNext(NULL);
			rear = newNode;
		}
		size++;
	}
	T dequeue() //function to remove element/data from queue
	{
		if (front->getNext() != NULL)
		{
			T x = (front->getNext())->get();
			Node<T>* p = front->getNext();
			front->setNext(p->getNext());
			delete p;
			size--;
			return x;
		}
	}
	T findmax() //function to get maximum number between positive numbers
	{
		if (front->getNext() != NULL)
		{
			T max = (front->getNext())->get();
			Node<T>* temp = front->getNext();
			while (temp != NULL)
			{
				if (max < temp->get())
					max = temp->get();
				temp = temp->getNext();
			}
			return max;
		}
	}
	T findmax1() //function to get maximum number between negative numbers
	{
		if (front->getNext() != NULL)
		{
			T max = (front->getNext())->get();
			Node<T>* temp = front->getNext();
			while (temp != NULL)
			{
				if (max > temp->get())
					max = temp->get();
				temp = temp->getNext();
			}
			return max;
		}
	}
	int findmaxlength() //function to get maximum length in string data type queue
	{
		if (front->getNext() != NULL)
		{
			int length;
			int temp1;
			Node<T>* temp = front->getNext();
			string s = temp->get();
			length = s.length();
			temp = temp->getNext();
			while (temp != NULL)
			{
				s = temp->get();
				temp1 = s.length();
				if (length < temp1)
					length = temp1;
				temp = temp->getNext();
			}
			return length;
		}
	}
	int getsize()
	{
		return size;
	}
	bool isEmpty() //function to check queue is empty
	{
		if (size == 0)
			return true;
		return false;
	}
	~queue() //destructor
	{
		while (!isEmpty())
			dequeue();
	}
};
void reverse(queue<long int>& q) //function to reverse a queue of negative numbers
{
	if (q.getsize() == 0)
		return;
	long int data = q.dequeue();
	reverse(q);
	q.enqueue(data);
}
void RadixSort(queue<long int>& q) //Radix sort function for integer type queues
{
	if (q.getsize() == 0)
	{
		cout << "Queue is empty" << endl;
		return;
	}
	queue<long int> q_plus, q_neg;
	int size = q.getsize();
	for (int i = 0; i < size; i++)// separate the positive and negative numbers in different queues
	{
		long int data = q.dequeue();
		if (data < 0)
			q_neg.enqueue(data);
		else
			q_plus.enqueue(data);
	}
	long int max = q_plus.findmax();
	if (max < 0)
		max *= -1;
	for (int j = 1; max / j > 0; j *= 10)
	{
		//create 10 queues to store sorted numbers by digitwise approach
		queue<long int>** arr = new queue<long int>*[10];
		queue<long int> q1;//queue to store sorted data
		for (int i = 0; i < 10; i++)
		{
			arr[i] = new queue<long int>();
		}
		int size1 = q_plus.getsize();
		for (int i = 0; i < size1; i++)
		{
			long int data = q_plus.dequeue();
			long int digit = (data / j) % 10;
			if (digit < 0)
				digit *= -1;
			arr[digit]->enqueue(data);
		}
		for (int i = 0; i < 10; i++)
		{
			while (!arr[i]->isEmpty())
			{
				q1.enqueue(arr[i]->dequeue());
			}
		}
		for (int i = 0; i < size1; i++)
		{//insert the sorted back into positive numbers queue
			q_plus.enqueue(q1.dequeue());
		}
		for (int i = 0; i < 10; i++)
		{
			delete arr[i];
			arr[i] = NULL;
		}
		delete[]arr;
		arr = NULL;
	}
	int size2 = q_neg.getsize();
	if (size2 != 0)
	{
		//same procedure for queue of negative numbers
		max = q_neg.findmax1();
		if (max < 0)
			max *= -1;
		for (int j = 1; max / j > 0; j *= 10)
		{
			queue<long int>** arr = new queue<long int>*[10];
			queue<long int> q1;
			for (int i = 0; i < 10; i++)
			{
				arr[i] = new queue<long int>();
			}
			int size1 = q_neg.getsize();
			for (int i = 0; i < size1; i++)
			{
				long int data = q_neg.dequeue();
				long int digit = (data / j) % 10;
				if (digit < 0)
					digit *= -1;
				arr[digit]->enqueue(data);
			}
			for (int i = 0; i < 10; i++)
			{
				while (!arr[i]->isEmpty())
				{
					q1.enqueue(arr[i]->dequeue());
				}
			}
			for (int i = 0; i < size2; i++)
			{
				q_neg.enqueue(q1.dequeue());
			}
			for (int i = 0; i < 10; i++)
			{
				delete arr[i];
				arr[i] = NULL;
			}
			delete[]arr;
			arr = NULL;
		}
		int size1 = q_neg.getsize();
		reverse(q_neg);
		//insert the sorted negative numbers back in the original queue
		for (int i = 0; i < size1; i++)
		{
			q.enqueue(q_neg.dequeue());
		}
	}
	int size1 = q_plus.getsize();
	//insert the sorted positive numbers back in the original queue
	for (int i = 0; i < size1; i++)
	{
		q.enqueue(q_plus.dequeue());
	}
}
void RadixSort(queue<string>& q) //Radix sort function for string type queues
{
	if (q.getsize() == 0)
	{
		cout << "Queue is empty" << endl;
		return;
	}
	int max = q.findmaxlength();
	for (int j = max - 1; j >= 0; j--)
	{
		queue<string>** arr = new queue<string>*[58];
		queue<string> q1;
		for (int i = 0; i < 58; i++)
		{
			arr[i] = new queue<string>();
		}
		int size = q.getsize();
		//To store datain their corresponding queues
		for (int i = 0; i < size; i++)
		{
			string s = q.dequeue();
			char ch = s[j];
			if (int(ch) >= 65 && int(ch) <= 122)
			{
				int digit = (int(ch)) % 65;
				arr[digit]->enqueue(s);
			}
			else
			{
				int digit = (int(ch)) % 48;
				arr[digit]->enqueue(s);
			}
		}
		for (int i = 0; i < 58; i++)
		{
			while (!arr[i]->isEmpty())
			{
				q1.enqueue(arr[i]->dequeue());
			}
		}
		for (int i = 0; i < size; i++)
		{
			//insert sorted data in the original queue 
			q.enqueue(q1.dequeue());
		}
		for (int i = 0; i < 58; i++)
		{
			delete arr[i];
			arr[i] = NULL;
		}
		delete[]arr;
		arr = NULL;
	}
}
int main()
{
	queue< long int> q;
	q.enqueue(824);
	q.enqueue(270);
	q.enqueue(657);
	q.enqueue(154);
	q.enqueue(702);
	q.enqueue(789);
	q.enqueue(222);

	RadixSort(q);
	cout << "Sorted data: " << endl;
	while (!q.isEmpty())
	{
		cout << q.dequeue() << endl;
	}
	cout << endl << endl;
	cout << "Sorted data: " << endl;
	queue<string> q1;
	q1.enqueue("hassan");
	q1.enqueue("arslan");
	q1.enqueue("sultan");

	RadixSort(q1);
	while (!q1.isEmpty())
	{
		cout << q1.dequeue() << endl;
	}
	return 0;
}