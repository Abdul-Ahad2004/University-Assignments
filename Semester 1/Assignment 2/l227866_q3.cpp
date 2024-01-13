//#include <iostream>
//using namespace std;
//int main()
//{
//	int gallons, units;
//	float miles, no_of_miles, total_cost;
//	cout << "Enter the maximum number of gallons that a car can hold: ";
//	cin >> gallons;
//	cout << "Enter the no.of miles which can be covered on full tank: ";
//	cin >> miles;
//	no_of_miles = miles / gallons;
//	cout << "The number of miles that may be driven per gallon of gas: " << no_of_miles << endl;
//	cout << "**********************************************" << endl;
//	cout << "\n\nEnter the number of units that sold: ";
//	cin >> units;
//	total_cost = units * 99;
//	if (units == 0)
//	{
//		cout << "The total cost of the purchae is 0." << endl;
//	}
//	else if (units < 0)
//		cout << "Please enter the valid digit." << endl;
//	else if (units>0)
//	{
//		if (units < 10)
//		{
//			cout << "The total cost of the purchase:$ " << total_cost << endl;
//		}
//		else if (units >= 10 && units <= 19)
//		{
//			total_cost = (20 / (float)100 * total_cost);
//			total_cost = (units * 99) - total_cost;
//			cout << "The total cost of the purchase: $" << total_cost << endl;
//		}
//		else if (units >= 20 && units <= 49)
//		{
//			total_cost = (30 / (float)100 * total_cost);
//			total_cost = (units * 99) - total_cost;
//			cout << "The total cost of the purchase: $" << total_cost << endl;
//		}
//		else if (units >= 50 && units <= 99)
//		{
//			total_cost = (40 / (float)100 * total_cost);
//			total_cost = (units * 99) - total_cost;
//			cout << "The total cost of the purchase: $" << total_cost << endl;
//
//		}
//		else if(units>=100)
//		{
//			total_cost = (50 / (float)100 * total_cost);
//			total_cost = (units * 99) - total_cost;
//			cout << "The total cost of the purchase: $" << total_cost << endl;
//		}
//	}
//	
//
//}
