#include<iostream>
using namespace std;
bool global = false;
template <typename T>
class stack
{
private:
	T* A;
	int size;
	int capacity;
	int current;
public:
	stack(int cap = 0) //constructor
	{
		if (cap > 0)
		{
			A = new T[cap];
			capacity = cap;
		}
		else
		{
			A = NULL;
			capacity = 0;
		}
		size = 0;
		current = -1;
	}
	~stack()//destructor
	{
		while (!isEmpty())
			pop();
	}
	void push(const T& data)//function to push data/elements in stack
	{
		if (global == true)
		{
			//if current points to 0 index then push element at start and resize the array
			if (capacity == 0)
			{
				A = new T[1];
				capacity = 1;
				A[++current] = data;
				return;
			}
			T* temp;
			if (size != capacity)
			{
				temp = new T[capacity];
			}
			else
			{
				temp = new T[capacity + 1];
			}
			temp[0] = data;
			int i = 1;
			int j = 0;
			while (j < size)
			{
				temp[i++] = A[j++];
			}
			delete[]A;
			A = temp;
			size++;
		}
		else
		{
			//if current does not point to 0 index then push element at end 
			if (capacity == 0)
			{
				A = new T[1];
				capacity = 1;
				A[++current] = data;
			}
			else if (size == capacity)
			{
				T* temp = new T[capacity * 2];
				int i = 0;
				while (i < size)
				{
					temp[i] = A[i];
					i++;
				}
				delete[] A;
				A = temp;
				capacity *= 2;
				A[++current] = data;
			}
			else
			{
				A[++current] = data;
			}
			size++;
		}
	}
	T pop() //function to pop the data/element from the stack
	{
		if (global == false)
		{
			//if current does not point to 0 index then pop element from end 
			if (size > 0)
			{
				if (size == capacity / 2)
				{
					T* temp = new T[capacity / 2];
					int i = 0;
					while (i < size)
					{
						temp[i] = A[i];
						i++;
					}
					delete[] A;
					A = temp;
					capacity /= 2;
					size--;
					return A[current--];
				}
				else
				{
					size--;
					return A[current--];
				}
			}
			else
			{
				return 0;
			}
		}
		else
		{
			//if current points to 0 index then pop element from start 
			if (size > 0)
			{
				if (size == capacity / 2)
				{
					T* temp = new T[capacity / 2];
					int i = 0;
					int j = current;
					while (i < size)
					{
						temp[i] = A[j];
						i++;
						j++;
					}
					delete[] A;
					A = temp;
					capacity /= 2;
					size--;
					current = 0;
					return A[current++];
				}
				else
				{
					size--;
					return A[current++];
				}
			}
			else
			{
				return 0;
			}
		}
	}
	const T& top()//function to get the current's value
	{
		return A[current];
	}
	bool isEmpty() //function to check the stack is empty
	{
		if (size == 0)
			return true;
		else
			return false;
	}
	void flipstack() //function to flip the stack
	{
		if (size != 0 && size != 1)
		{
			if (current == 0)
			{
				//if current points to 0 index then current should point to the uppermost value
				current = size - 1;
				global = false;
			}
			else
			{
				current = 0;
				global = true;
			}
		}
	}
};

int main()
{
	stack<int> s;
	for (int i = 1; i <= 5; i++)
	{
		s.push(i);
	}
	s.flipstack();
	s.push(8);
	s.push(10);
	s.pop();
//	s.push(6);
//	s.push(7);
	while (!s.isEmpty())
	{
		cout << "Element popped: " << s.pop() << endl;
	}
	return 0;
}