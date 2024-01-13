//#include<iostream>
//using namespace std;
//int main()
//{
//	string person;
//	float weight, wrist_m, waist_m, hip_m, forearm_m, body_fat, body_fat_percentage, B;
//	cout << "Enter your gender: ";
//	cin >> person;
//     if (person == "male" || person == "Male" || person == "Men" || person == "men")
//	{
//		cout << "Enter your body weight: ";
//		cin >> weight;
//		cout << "Enter your wrist measurement: ";
//		cin >> wrist_m;
//		if (weight <= 0 || wrist_m <= 0)
//			cout << "Please enter the crrect data." << endl;
//		else
//		{
//
//
//			B = ((weight * 1.082) + 94.42) - (wrist_m * 4.15);
//			body_fat = weight - B;
//			body_fat_percentage = body_fat * 100 / weight;
//			cout << "Your body fat is: " << body_fat << endl;
//			cout << "Your body fat percentage is: " << body_fat_percentage<<"%" << endl;
//		}
//
//	}
//	else
//	{
//		cout << "Enter your body weight: ";
//		cin >> weight;
//		cout << "Enter your wrist measurement(at fullest point): ";
//		cin >> wrist_m;
//		cout << "Enter your waist measurement(at navel): ";
//		cin >> waist_m;
//		cout << "Enter your hip measurement(at fullest point): ";
//		cin >> hip_m;
//		cout << "Enter your forearm measurement(at fullest point): ";
//		cin >> forearm_m;
//		if (weight <= 0 || wrist_m <= 0 || waist_m <= 0 || hip_m <= 0 || forearm_m <= 0)
//			cout << "Please enter the crrect data." << endl;
//		else
//		{
//
//
//			B = ((weight * 0.732) + 8.987) + (wrist_m / 3.140) - (waist_m * 0.157) - (hip_m * 0.249) + (forearm_m * 0.434);
//			body_fat = weight - B;
//			body_fat_percentage = body_fat * 100 / weight;
//			cout << "Your body fat is: " << body_fat << endl;
//			cout << "Your body fat percentage is: " << body_fat_percentage <<"%" << endl;
//		}
//
//	}
//}