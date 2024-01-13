#include<iostream>
using namespace std;
void resize(int*& stack, int& top, int& size)
{
	int* arr = new int[size + 1];
	for (int i = 0; i < size; i++)
	{
		arr[i] = stack[i];
	}
	delete[]stack;
	stack = arr;
	size++;
}
void push(int*& stack, int n, int& top, int& size)
{
	if (top == -1 && stack == NULL) {
		stack = new int[size];
	}
	else if (top == size - 1) {
		resize(stack, top, size);
	}
	top++;
	stack[top] = n;
}
bool isEmpty(int top)
{
	if (top == -1)
		return 1;
	return 0;
}
void pop(int*& stack, int& top, int& size)
{
	if (size == 1)
	{
		top = -1;
		delete[]stack;
		stack = NULL;
	}
	else {
		int* arr = new int[size - 1];
		for (int i = 0; i < size - 1; i++)
		{
			arr[i] = stack[i];
		}
		delete[]stack;
		stack = arr;
		size--;
		top--;
	}
}
int main()
{
	int N, top = -1, size = 1;
	int* C;
	cout << "Enter N: ";
	cin >> N;
	C = new int[N];
	int* stack = NULL;
	cout << "Enter the boxes of chocolates: " << endl;
	for (int i = 0; i < N; i++)
	{
		cout << "Enter the " << i + 1 << " chocolate box: ";
		cin >> C[i];
		while (C[i] < 0)
		{
			cout << "Enter the valid data: ";
			cin >> C[i];
		}
	}
	int sum = 0;
	for (int i = 0; i < N; i++)
	{
		if (C[i] > 0) {
			push(stack, C[i], top, size);

		}
		else if (C[i] == 0)
		{
			if (isEmpty(top))
				cout << "Stack is empty, we cannot sell the chocolate box" << i + 1 << endl;
			else {
				sum += stack[top];
				pop(stack, top, size);

			}
		}
	}
	cout << "The number of chocolates which are sold are: " << sum << endl;
	/*for (int i = 0; i < size; i++)
	{
		cout << stack[i] << " ";
	}*/
	delete[]stack;
	stack = NULL;
}