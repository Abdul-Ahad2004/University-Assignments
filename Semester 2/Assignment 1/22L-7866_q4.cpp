#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>


using namespace std;
ifstream f1;
ofstream f2;

#define MaxRows 50
#define MaxCols 50

class grayImage {

public:
	unsigned short setPixel(unsigned short value, int r, int c) {
		if (r >= Rows || c >= Cols || r < 0 || c < 0)
			return -1;
		Image[r][c] = value;
		return value;
	}

	/*Function for getting a single pixel at rth Row & cth Column*/
	int getPixel(int r, int c) {
		if (r >= Rows || c >= Cols || r < 0 || c < 0)
			return -1;
		return Image[r][c];
	}

	int setRows(int rows) {
		if (rows < 1 || rows > MaxRows)
			return -1;
		Rows = rows;
		return Rows;
	}

	int getRows() {
		return Rows;
	}

	int setCols(int cols) {
		if (cols < 1 || cols > MaxCols)
			return -1;
		Cols = cols;
		return Cols;
	}

	int getCols() {
		return Cols;
	}

	bool saveImage(string File_Name)
	{
		f2.open(File_Name + ".txt");
		f2 << "P2" << endl << "4 4"<<endl << "255" << endl;
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				f2 << Image[i][j] << " ";
			}
			f2 << endl;
		}
		f2.close();
		/*
		* Here write the code to save an image in .pgm format
		* The function will return true if the image is saved successfully
		*/
		return true;
	}

	bool loadImage(string File_Name)
	{
		Rows = 0,Cols=0;
		f1.open(File_Name + ".txt");
		if (f1.fail()) {
			return false;
		}
		string s, s1;
		while (getline(f1, s))
		{
			Rows++;
		}
		Rows -= 3; 
		f1.close();
		f1.open(File_Name + ".txt");
		for (int i = 0; i <= 3; i++)
		{
			getline(f1, s1);
			if (i == 3)
			{
				for (int j= 0; s1[j] != '\0'; j++)
				{
					if(s1[j]==' ')
					   Cols++;
					
				}
			}
		}
		Cols++;
		f1.close();
		f1.open(File_Name + ".txt");
		string s2 ="",temp;
		int st;
		for (int i = 0,l=0; i < Rows+3 &&l<Rows; i++)
		{
			getline(f1, temp);
			if (i < 3)
				continue;
			
			for (int j = 0, k = 0; j < Cols; k++)
			{

				if (temp[k] != ' ' && temp[k] != '\0')
					s2 += temp[k];
				else {
					st = stoi(s2);
					Image[l][j] = st;
					s2 ="";
					j++;
				}
			}
			l++;
		}
		f1.close();

		/*
		* Here write the code to load an image which is in .pgm format
		* into the struct member "Image"
		* The function will return true if the image is loaded successfully
		*/
		return true;
	}

	void Negative()
	{
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				Image[i][j] = 255-Image[i][j];
			}
			cout << endl;
		}
		/*
		* Here write the code to convert the grayscale image into negative form
		* Tip: You need to blacken the pixels at every index
		*/
	}


	void changeBrightness(int amount)
	{

		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				Image[i][j] += amount;
			}
			cout << endl;
		}
		/*
		* Here write the code to brighten the grayscale image by the provided amount.
		* The range of amount is from -255 till +255
		* Tip: You need to brighten the pixels at every index
		*/
	}
	void sort(int*& temp,int s)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = i+1; j < 9; j++)
			{
				if (temp[i] > temp[j]) {
					int x = temp[i];
					temp[i] = temp[j];
					temp[j] = x;
				}
			}
		}
	}

	void medianFilter(int filterSize = 3)
	{
		int* temp = new int[9];
		int* temp1 = new int[4];
		int n = 0;
		for (int l = 0; l < Rows / 2; l++) {
			for (int m = 0; m < Cols/2; m++)
			{
				int k = 0;
				for (int i = l; i < 3+l; i++)
				{
					for (int j = m; j < 3+m; j++)
					{
						temp[k++] = Image[i][j];
					}
				}
				sort(temp, 9);
				int a = temp[4];
				temp1[n] = a;
				n++;
			}
		}
		
		n = 0;
		for (int l = 0; l < Rows / 2; l++) {
			for (int m = 0; m < Cols / 2; m++)
			{
				for (int i = l; i < 3; i++)
				{
					for (int j = m; j < 3; j++)
					{
						if (i == (l + 1) && j == (m + 1)) {
							Image[i][j] = temp1[n];
							n++;
						}
					}
				}
			}
		}
		delete[]temp;
		temp = NULL;
		delete[]temp1;
		temp1 = NULL;

		/*
		* Here write the code to apply the median filter on an image
		* This will reduce the noise in the image
		* Tip:
		* Here filtersize states the size of the matrix grid that will be created upon Image 2D Array i.e 3x3 by default
		* Find median of this array.
		* Then replace neighbouring pixels with the median value.
		* The following image can help you understand the concept: https://i.stack.imgur.com/P6Moj.png
		*/
	}

	void combineSideBySide(grayImage& Two, int fillValue)
	{
		int r1,c1, r2, c2;
		r2 = Two.getRows();
		c2 = Two.getCols();
		int totalc=Cols + 1 + c2;
		r1= Rows;
		c1 = Cols;
		Cols += c2 + 1;
		for (int i = 0; i < Rows; i++)
		{
			for (int j = c1,k=0; k>=0; k--)
			{
				Image[i][j]=fillValue;
			}
		}
		for (int i = 0; i < Rows; i++)
		{
			for (int k= c1+1,j=0;j<c2; j++,k++)
			{
				Image[i][k] =Two.Image[i][j] ;
			}
		}

		/*
		* Here write the code to combine the second image aside to the current image
		  Tip: Adding two 2D arrays, increasing the resultant image size
		*/
	}

	void FlipHorizontally()
	{
		int* temp = new int[Rows];
		for (int i = 0; i < Cols/ 2; i++)
		{
			for (int j = 0; j < Rows; j++)
			{
				temp[j] = Image[j][i];
				Image[j][i] = Image[j][Cols-1-i];
				Image[ j][Cols - 1 - i] = temp[j];
			}
		}
		delete[]temp;
		temp = NULL;
		/*
		* Here write the code to flip the image horizontally
		  Tip: swapping image pixels
		*/
	}

	void FlipVertically()
	{
		int*temp=new int [Cols] ;
		for (int i = 0; i < Rows / 2; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				temp[j] = Image[i][j];
				Image[i][j] = Image[Rows - 1 - i][j];
				Image[Rows - 1 - i][j] = temp[j];
			}
		}
		delete[]temp;
		temp = NULL;
		/*
		* Here write the code to flip the image vertically
		  Tip: swapping image pixels
		*/
	}

	/* BONUS TASK */
	void Filter(double Mask[][3], int ro, int co)
	{
		/*
		* Here write the code to apply a filter of user's choice on the image
		  Tip: Use the mask array and enhance each pixel with index of 3x3 mask array
		*/

		int l = 0, r = 0, z = 0, s = 0, x = 0, summ = 0;
		int n = ro / 2;

		cout << endl;
		cout << "Enter the Elements of Mask Filter Array " << endl;
		for (int q = 0; q < ro; q++)
		{
			for (int w = 0; w < co; w++)
				cin >> Mask[q][w];
		}

	}

private:
	unsigned short Image[MaxRows][MaxCols]; //Use this 2D array to store pixels of Image
	int Rows, Cols;	//Total Rows, Columns of image
	char format[3];	//This is the magic number (The first row of pgm image)
};

int main()
{
	grayImage GM;
	string outputFile;
	string image1;

	cout << "Enter name of image 1: " << endl;
	getline(cin, image1);
	GM.loadImage(image1);


	system("CLS");


	int option = 0;

	while (option != -1)
	{
		cout << "Choose an option:\n" << endl;
		cout << " 1. Combine Two images side by side " << endl;
		cout << " 2. Change Brightness of Image" << endl;
		cout << " 3. Find Negative of an Image " << endl;
		cout << " 4. Flip an image Vertically" << endl;
		cout << " 5. Flip an image Horizontally" << endl;
		cout << " 6. Apply Median Filter (Remove Noise)" << endl;
		cout << " 7. Apply your own Filter (Bonus)" << endl;
		cout << "ENTER -1 TO EXIT" << endl;
		cin >> option;
		cout << endl;
		GM.loadImage(image1);
		while (option < -1 && option == 0 && option>7)
		{
			cout << "Please enter the valid option: ";
			cin >> option;
		}
		if (option == 1) //sidebyside
		{
			grayImage GM2;
			string image2;

			cout << "Enter name of image 2: " << endl;
			cin.ignore();
			getline(cin, image2);
			GM2.loadImage(image2);

			int fillVal;
			cout << "Enter the gray fill Value: " << endl;
			cin >> fillVal;
			GM.combineSideBySide(GM2, fillVal);
			cout << "Enter the output file name: ";
			cin >> outputFile;
			GM.saveImage(outputFile);
		}

		else if (option == 2) { //brightness
			int amount;
			cout << "Enter the amount for brightness: " << endl;
			cin >> amount;
			while (amount < -255 && amount>255)
			{
				cout << "Please enter the number in range between -255 and 255: ";
				cin >> amount;
			}
			cout << endl;
			GM.changeBrightness(amount);
			cout << "Enter the output file name: ";
			cin >> outputFile;
			cout << endl;
			GM.saveImage(outputFile);
			cout << endl;
			cout << "Files Saved successfully in the output folder" << endl;
		}

		else if (option == 3) { //negative
			GM.Negative();
			cout << "Enter the output file name: ";
			cin >> outputFile;
			GM.saveImage(outputFile);
			cout << endl;
			cout << "Files Saved successfully in the output folder" << endl;
		}

		else if (option == 4) { //flip v
			GM.FlipVertically();
			cout << "Enter the output file name: ";
			cin >> outputFile;
			GM.saveImage(outputFile);
			cout << endl;
			cout << "Files Saved successfully in the output folder" << endl;
		}

		else if (option == 5) { //flip h
			GM.FlipHorizontally();
			cout << "Enter the output file name: ";
			cin >> outputFile;
			GM.saveImage(outputFile);
			cout << endl;
			cout << "Files Saved successfully in the output folder" << endl;
		}

		else if (option == 6) { //median

			int filtersize;
			cout << "Enter filter size: " << endl;
			cin >> filtersize;
			GM.medianFilter(filtersize);
			cout << "Enter the output file name: ";
			cin >> outputFile;
			cout << endl;
			GM.saveImage(outputFile);
			cout << endl;
			cout << "Files Saved successfully in the output folder" << endl;
		}

		else if (option == 7) { //Filter
			double b[3][3];
			int r = 3, c = 3;
			GM.Filter(b, r, c);
			cout << "Enter the output file name: ";
			cin >> outputFile;
			cout << endl;
			GM.saveImage(outputFile);
		}
		else if (option == -1)
			break;
	}

	return 0;
}