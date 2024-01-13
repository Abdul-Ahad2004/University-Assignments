#include<iostream>
#include<string>
using namespace std;
class Customer
{
	int id;
	string name;
	int discount;
public:
	Customer()
	{
		id = 0;
		name = "";
		discount = 0;
	}
	Customer(int id, string name, int discount)
	{
		this->id = id;
		this->name = name;
		this->discount = discount;
	}
	int getid()
	{
		return id;
	}
	string getname()
	{
		return name;
	}
	int getdiscount()
	{
		return discount;
	}
	void setdiscount(int d)
	{
		discount = d;
	}
	string tostring()
	{
		string s = "";
		s += name;
		s += "(";
		s += to_string(id);
		s += ")";
		s += "(";
		s += to_string(discount);
		s += "%)";
		return s;
	}
};
class invoice
{
	int id;
	Customer* customer;
	double amount;
public:
	invoice(int id, Customer* customer, double amount)
	{
		this->customer = new Customer();
		this->id = id;
		this->customer = customer;
		this->amount = amount;
	}
	int getid()
	{
		return id;
	}
	Customer* getcustomer()
	{
		return customer;
	}
	void setcustomer(Customer* customer)
	{
		this->customer = customer;
	}
	double getamount()
	{
		return amount;
	}
	void setamount(double amount)
	{
		this->amount = amount;
	}
	int getcustomerid()
	{
		return customer->getid();
	}
	string getcustomername()
	{
		return customer->getname();
	}
	int getcustomerdiscount()
	{
		return customer->getdiscount();
	}
	double getamountafterdiscount()
	{
		double dis= (customer->getdiscount()/(float)100)*amount;
		amount -= dis;
		return amount;
	}
	string tostring()
	{
		string s = "invoice[id=";
		s += to_string(id);
		s += ",customer=";
		s += customer->tostring();
		s += ",amount=";
		s += to_string(getamountafterdiscount());
		s += "]";
		return s;
	}
};
int main()
{
	Customer C1(111, "Abdul Ahad", 20);
	cout << C1.tostring() << endl<<endl;
	invoice obj(112, &C1, 15000);
	cout << obj.tostring() << endl<<endl;
}