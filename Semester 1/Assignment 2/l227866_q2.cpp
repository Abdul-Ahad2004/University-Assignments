#include<iostream>
using namespace std;
int main()
{
	cout << "Code\t\tMeal\t\t\tPer kg Price in Pakistani rupees\n1\t\tChicken Handi\t\t1800\n2\t\tChicken Karahi\t\t2000\n3\t\tChicken Tikka\t\t2200\n4\t\tChicken Haleem\t\t500\n5\t\tCreamy Chicken\t\t2500" << endl;
	cout << "**********************************************" << endl;
	int choice, currency, price=0;
	float quantity, meal_price, sale_tax=0, total_amount;
	cout << "Please enter your choice from the given menu's code: ";
	cin >> choice;
	if (choice > 5 || choice<1)
	{
		cout << "Please enter the right code." << endl;
	}
	else if (choice >=1 && choice <= 5)
	{
		if (choice == 1)
			price = 1800;
		else if (choice == 2)
			price = 2000;
		else if (choice == 3)
			price = 2200;
		else if (choice == 4)
			price = 500;
		else if (choice == 5)
			price = 2500;
		cout << "**********************************************\nPlease enter your quantity in kgs:";
		cin >> quantity;
		if (quantity <= 0)
		{
			cout << "Please enter the correct quantity" << endl;
		}
		else if (quantity > 0)
		{
			cout << "**********************************************\nPlease enter the currency in which you want to pay:press 1 for pkr,2 for euro,3 for Dollar: ";
			cin >> currency;
			if (currency < 1 || currency>=4)
			{
				cout << "Please enter the right currency." << endl;
			}
			else if (currency >= 1 && currency < 4)
			{
				cout << "**********************************************" << endl;
				meal_price = quantity * price;
				if (meal_price > 1000 && meal_price <= 3000)
					sale_tax = 2 / (float)100 * meal_price;
				else if (meal_price > 3000)
					sale_tax = 5 / (float)100 * meal_price;
				total_amount = meal_price + sale_tax;
				if (currency == 1)
					cout << "Meal price: " << meal_price << "rupees\nSales tax is: " << sale_tax << "rupees\nTotal Price is: " << total_amount << "rupees" << endl;
				else if (currency == 2)
				{
					meal_price = meal_price / 222.27;
					sale_tax = sale_tax / 222.27;
					total_amount = total_amount / 222.27;
					cout << "Meal price: " << meal_price << "EUR\nSales tax is: " << sale_tax << "EUR\nTotal Price is: " << total_amount << "EUR" << endl;
				}
				else if (currency == 3)
				{
					meal_price = meal_price / 221.91;
					sale_tax = sale_tax / 221.91;
					total_amount = total_amount / 221.91;
					cout << "Meal price:$" << meal_price << "\nSales tax is:$" << sale_tax << "\nTotal Price is:$" << total_amount << endl;
				}
			}
		}
	}
}