//#include<iostream>
//using namespace std;
//void MIX(int A[], int M, int B[], int N)
//{
//	for (int ind = 0; ind < M; ind++)
//	{
//		cout << "Enter the value at index " << ind << " of array A: ";
//		cin >> A[ind];
//	}
//	for (int ind = 0; ind < N; ind++)
//	{
//		cout << "Enter the value at index " << ind << " of array B: ";
//		cin >> B[ind];
//	}
//	cout << "Array A= ";
//	for (int ind = 0; ind < M; ind++)
//	{
//		cout << A[ind]<<" ";
//	}
//	cout << endl;
//	cout << "Array B= ";
//	for (int ind = 0; ind < N; ind++)
//	{
//		cout<< B[ind]<<" ";
//	}
//	cout << endl;
//	int size = M + N;
//	int s = size;
//	int C[1000] = { 0 },l=0,r=0;
//	for (int i = 0; i < M; i++)
//	{
//		if (A[i] % 2 == 0)
//		{
//			C[l] = A[i];
//			l++;
//		}
//	}
//	for (int i = 0; i <M; i++)
//	{
//		if (A[i] % 2 != 0)
//		{
//			C[size-1] = A[i];
//			size--;
//		}
//	}
//	r = size;
//	for (int i = 0; i < N; i++)
//	{
//		if (B[i] % 2 == 0)
//		{
//			C[l] = B[i];
//			l++;
//		}
//	}
//	for (int i = 0; i < N; i++)
//	{
//		if (B[i] % 2 != 0)
//		{
//			C[r-1] = B[i];
//			r--;
//		}
//	}
//	cout << "Resultant Array C= ";
//	for (int ind = 0; ind < s; ind++)
//	{
//		cout << C[ind] << " ";
//	}
//	cout << endl;
//}
//int main()
//{
//	int M,N;
//	cout << "Enter the size of array1: ";
//	cin >> M;
//	int A[1000] = { 0 };
//	cout << "Enter the size of array2: ";
//	cin >> N;
//	int B[1000] = { 0 };
//	MIX(A, M, B, N);
//}