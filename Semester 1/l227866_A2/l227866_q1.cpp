#include<iostream>
using namespace std;
int main()
{
	float weight, height, BMI;
	cout << "Enter the weight in pounds: ";
	cin >> weight;
	cout << "Enter the height in inches: ";
	cin >> height;
	if (weight <= 0 || height <= 0)
		cout << "Please enter the correct data." << endl;
	if (weight > 0 && height > 0)
	{
		BMI = weight * 703 / (height * height);
		cout << "Your body mass index(BMI) is: " << BMI << endl;
		if (BMI >= 18.5 && BMI <= 25)
			cout << "You have optimal weight. ";
		else if (BMI < 18.5)
			cout << "You are underweight.";
		else
			cout << "you are overweight.";
	}


}