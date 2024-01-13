#include<iostream>
using namespace std;
template <typename T>
class Undostack
{
private:
	T* A;
	int size;
	int capacity;
	int current;
public:
	Undostack(int cap = 0) //constructor
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
	void push(const T& data) //function to push the data/element at the top of the stack
	{
		if (size == 100) //when size will be 100 it should forget the oldest element
		{
			T* temp = new T[size];
			int i = 1;
			int j = 0;
			while (i < size)
			{
				temp[j++] = A[i++];
			}
			delete[]A;
			A = temp;
			current--;
			size--;
		}
		if (capacity == 0)
		{
			A = new T[1];
			capacity = 1;
			A[++current] = data;
		}
		else if (size == capacity) //increase the stack if our capacity is full
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
	T pop() //function to remove the data/element from the top of the stack
	{
		if (size > 0)
		{
			if (size == capacity / 2) //if used stack is half of its capacity then half the stack's capacity to save memory
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
				size--;
				capacity /= 2;
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
			cout << "stack is already empty." << endl;
			return T();
		}
	}
	const T& top() //function to get the data at top of the stack
	{
		return A[current];
	}
	bool isEmpty() //function to check stack is empty 
	{
		if (size == 0)
			return true;
		else
			return false;
	}
	~Undostack() //destructor
	{
        while (!isEmpty()) 
	    {
            pop();
        }
    }
};

int main()
{
	Undostack<int> s;
	for (int i = 1; i <=102; i++)
	{
		s.push(i);
	}
	/*s.pop();
	s.pop();
	s.push(101);*/
	while (!s.isEmpty())
	{
		cout << "Element popped: " << s.pop() << endl;
	}
	return 0;
}