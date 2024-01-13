#include<iostream>
using namespace std;
class pointType
{
private:
	int x_coordinate;
	int y_coordinate;
public:
	pointType(int x=0,int y=0)
	{
		x_coordinate = x;
		y_coordinate = y;
	}
	void setter()
	{
		cout << "Enter the x-coordinate of the point: ";
		cin >> x_coordinate;
		cout << "Enter the y-coordinate of the point: ";
		cin >> y_coordinate;
	}
	int getter_x()
	{
		return x_coordinate;
	}
	int getter_y()
	{
		return y_coordinate;
	}
	void print()
	{
		cout << "(" << x_coordinate << "," << y_coordinate << ")" << endl;
	}
	pointType(const pointType& obj)
	{
		this->x_coordinate = obj.x_coordinate;
		this->y_coordinate = obj.y_coordinate;
	}
	friend void calcDistance(pointType p1, pointType p2)
	{
		float d = sqrt(pow(p1.x_coordinate - p2.x_coordinate, 2) + pow(p1.y_coordinate - p2.y_coordinate, 2));
		cout << "The distance between two points is: " << d << endl;
	}
	~pointType()
	{

	}
};
int main()
{
	pointType p1, p2;
	cout << "Enter the coordinates for point1: "<<endl;
	p1.setter();
	cout << "Enter the coordinates for point2: "<<endl;
	p2.setter();
	cout << "point1: ";
	p1.print();
	cout << "point2: ";
	p2.print();
	calcDistance(p1, p2);
}