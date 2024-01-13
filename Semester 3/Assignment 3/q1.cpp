#include<iostream>
#include<conio.h>
#include <cmath>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
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
	void enqueue(const T& data) //push elements/data into queue
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
	T dequeue() //remove data/element from a queue
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
	T getfront()
	{
		return (front->getNext()->get());
	}
	~queue() //destructor
	{
		while (!isEmpty())
			dequeue();
	}
	void graphics(int s) 
	{
		RenderWindow window(VideoMode(900, 700), "Soldier Circle");
		window.setFramerateLimit(60); // Limit the frame rate for smooth animation


		// Draw the soldier circle first
		CircleShape soldiersCircle(210); // Radius of 210 (adjust as needed)
		soldiersCircle.setFillColor(Color::Transparent);
		soldiersCircle.setOutlineColor(Color::White);
		soldiersCircle.setOutlineThickness(2);
		soldiersCircle.setOrigin(200, 200); // Change the origin to be outside of the main circle

		soldiersCircle.setPosition(450, 350); // Center the circle in the window

		// Draw the soldiers
		Texture soldierTexture;
		if (!soldierTexture.loadFromFile("soldier.png")) 
		{
			// Handle the error, for example:
			cout << "Failed to load the soldier image." << endl;
		}

		vector<Sprite> soldiers;
		int n = s; // Number of soldiers
		for (int i = 0; i < n; ++i) {
			float angle = i * (360.0f / n); // Evenly distribute soldiers
			float radians = angle * 3.14159 / 180; // Convert degrees to radians
			float x = 450 + 210 * cos(radians); // Center the circle and adjust the radius as needed
			float y = 350 + 210 * sin(radians);

			Sprite soldierSprite(soldierTexture);
			soldierSprite.setOrigin(soldierTexture.getSize().x / 2.0f, soldierTexture.getSize().y / 2.0f); // Center the origin
			soldierSprite.setPosition(x, y);
			soldiers.push_back(soldierSprite);
		}

		while (window.isOpen()) 
		{
			Event event;
			while (window.pollEvent(event)) 
			{
				if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Key::Space) {
					window.close();
				}
			}

			window.clear();

			// Draw the soldier circle
			window.draw(soldiersCircle);

			// Draw the soldiers
			for (const Sprite& soldier : soldiers)
			{
				window.draw(soldier);
			}
			window.display();
		}
	}
	void Josephus(int k, int n) //function to solve Josephus problem
	{
		for (int i = 1; i <= n; i++) //insert the number of soldiers
		{
			enqueue(i);
		}
		srand(time(0));
		int s = (rand() % n) + 1;
		cout << "Random variable(from where count is start) is : " << s << endl;
		for (int i = 0; i < s - 1; i++)
		{
			enqueue(dequeue());
		}
		while (size != 1)
		{
			cout << endl;
			Node<T>* temp = front;
			cout << "Soldiers Survived: ";
			for (int i = 1; i <= size; i++) // print the survived soldier numbers
			{
				cout <<getfront() << "  ";
				front = front->getNext();
			}
			front = temp;
			cout << endl;
			//print soldiers on console
			graphics(size);
			for (int i = 0; i < k; i++)// passing k soldiers
			{
				enqueue(dequeue());
			}
			cout << endl ;
			cout << dequeue() << " has been eliminated" << endl;//remove k soldier
			_getch();
		}
		T num = dequeue();// survivor at the end
		cout << "\n"<< num << " is freed." << endl;// survivor soldier number
		graphics(1);
	}
};
int main()
{
	queue<int> q;
	int k, n;
	cout << "Enter the value of N: ";
	cin >> n;
	while (n <= 1)
	{
		cout << "Please enter the number greater than 1: ";
		cin >> n;
	}
	cout << "Enter the value of k: ";
	cin >> k;
	while (k < 0)
	{
		cout << "Please enter the number greater than 0: ";
		cin >> k;
	}
	q.Josephus(k, n);
}