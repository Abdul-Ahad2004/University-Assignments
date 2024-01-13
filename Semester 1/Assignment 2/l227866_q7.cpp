//#include<iostream>
//using namespace std;
//int main()
//{
//	int crowns;
//	float length, width, area,totalPrice,perimeter;
//	string  typeOfFrame, colour;
//	cout << "Enter the length of picture in inches: ";
//	cin >> length;
//	cout << "Enter the width of picture in inches: ";
//	cin >> width;
//	cout << "Enter the type of frame: ";
//	cin >> typeOfFrame;
//	cout << "Enter the colour of frame: ";
//	cin >> colour;
//	cout << "Enter the number of crowns on frame: ";
//	cin >> crowns;
//	area = length * width;
//	perimeter = ((length+1) * 2) + ((width+1) * 2);
//	totalPrice = 0;
//	if (typeOfFrame == "regular" || typeOfFrame == "Regular") {
//		totalPrice = perimeter * 0.15 + totalPrice;
//		if (colour == "white" || colour == "White" && crowns >=0)
//		{
//
//			totalPrice = crowns * 0.35 + totalPrice;
//			totalPrice = totalPrice + (area * 0.02) + (area * 0.07);
//			cout << "The total costof framing the picture:$ " << totalPrice << endl;
//
//		}
//		else {
//			totalPrice = perimeter * 0.10;
//			totalPrice = crowns * 0.35 + totalPrice;
//			totalPrice = totalPrice + (area * 0.02) + (area * 0.07);
//			cout << "The total costof framing the picture:$ " << totalPrice << endl;
//		}
//
//	}
//	else if (typeOfFrame == "fancy" || typeOfFrame == "Fancy") {
//		totalPrice = perimeter * 0.25 + totalPrice;
//		if (colour == "white" || colour == "White" && crowns > 0)
//		{
//
//			totalPrice = crowns * 0.35 + totalPrice;
//			totalPrice = totalPrice + (area * 0.02) + (area * 0.07);
//			cout << "The total costof framing the picture:$ " << totalPrice << endl;
//
//		}
//		else {
//			totalPrice = perimeter * 0.10;
//			totalPrice = crowns * 0.35 + totalPrice;
//			totalPrice = totalPrice + (area * 0.02) + (area * 0.07);
//			cout << "The total costof framing the picture:$ " << totalPrice << endl;
//		}
//
//
//	}
//	else {
//		cout << "Enter fancy or regular!";
//	}
//
//
//	
//
//}