#include<iostream>
using namespace std;
class Polynomial
{
	int totalTerms;
	int* coeff;
	int* exp;
public:
	Polynomial()	{
		totalTerms = 0;
		coeff = NULL;
		exp = NULL;
	}
	Polynomial(int t,int*arr,int*arr1)
	{
		totalTerms = t;
		coeff = new int[t];
		exp = new int[t];
		for (int i = 0; i < t; i++)
		{
			coeff[i] = arr[i];
		}
		for (int i = 0; i < t; i++)
		{
			exp[i] = arr1[i];
		}
	}
	friend ostream& operator <<(ostream&, const Polynomial&);
	bool operator ! ()
	{
		if (totalTerms == 1 && coeff[0] == 0 && exp[0] == 0)
			return true;
		return false;
	}
	bool operator != (Polynomial obj)
	{
		int count1 = 0, count2 = 0;
		if (totalTerms == obj.totalTerms)
		{
			for (int i = 0; i < totalTerms; i++)
			{
				if (coeff[i] == obj.coeff[i])
					count1++;
			}
			for (int i = 0; i < totalTerms; i++)
			{
				if (exp[i] == obj.exp[i])
					count2++;
			}
			if (count1 == totalTerms && count2 == totalTerms)
				return false;
		}
		return true;
	}
	Polynomial(const Polynomial& obj)
	{
		totalTerms = obj.totalTerms;
		coeff = new int[totalTerms];
		exp = new int[totalTerms];
		for (int i = 0; i < totalTerms; i++)
		{
			coeff[i] = obj.coeff[i];
		}
		for (int i = 0; i < totalTerms; i++)
		{
			exp[i] = obj.exp[i];
		}
	}
	Polynomial operator +(Polynomial obj)
	{
		int count = 0;
		for (int i = 0; i < totalTerms && i< obj.totalTerms; i++)
		{
			for (int j = 0; j < obj.totalTerms; j++)
			{
				if (exp[i] == obj.exp[j])
					count++;
			}
		}
		int t = (totalTerms + obj.totalTerms) - count;
		int* c = new int[t];
		int* e = new int[t];
		int k=0;
		for (int i = 0; i < totalTerms && i< obj.totalTerms; i++)
		{
			count = 0;
			for (int j = 0; j < obj.totalTerms; j++)
			{
				if (exp[i] == obj.exp[j])
					count++;
			}
			if (count == 0) {
				c[k] = coeff[i];
				e[k] = exp[i];
				k++;
			}
			else
			{
				for (int j = 0; j < obj.totalTerms; j++)
				{
					if (exp[i] == obj.exp[j])
					{
						c[k] = coeff[i] + obj.coeff[j];
						e[k] = this->exp[i];
						k++;
					}
				}
			}
			count = 0;
			for (int j = 0; j < totalTerms; j++)
			{
				if (obj.exp[i] == exp[j])
					count++;
			}
			if (count == 0) {
				c[k] = obj.coeff[i];
				e[k] = obj.exp[i];
				k++;
			}

		}
		if (totalTerms > obj.totalTerms)
		{
			for (int i = obj.totalTerms; i < totalTerms; i++)
			{
				c[k] = coeff[i];
				e[k] = exp[i];
				k++;
			}
		}
		else {
			for (int i = totalTerms; i < obj.totalTerms; i++)
			{
				c[k] = obj.coeff[i];
				e[k] = obj.exp[i];
				k++;
			}
		}
		for (int i = 0; i < t; i++)
		{
			for (int j = i + 1; j < t; j++)
			{
				if (e[i] < e[j])
				{
					int temp = e[i];
					e[i] = e[j];
					e[j] = temp;
					temp = c[i];
					c[i] = c[j];
					c[j] = temp;
				}
			}
		}
		return Polynomial(t, c, e);
	}
	Polynomial& operator ++()
	{
		for (int i = 0; i < totalTerms; i++)
		{
			coeff[i] += 1;
		}
		return *this;
	}
	Polynomial operator ++(int)
	{
		Polynomial temp = *this;
		for (int i = 0; i < totalTerms; i++)
		{
			coeff[i] += 1;
		}
		return temp;
	}
	friend Polynomial operator +(int n, Polynomial& obj)
	{
		for (int i = 0; i < obj.totalTerms; i++)
		{
			if (obj.exp[i] == 0)
				obj.coeff[i] += n;
		}
		return obj;

	}
	~Polynomial()
	{
		delete[]coeff;
		coeff = NULL;
		delete[]exp;
		exp = NULL;
	}
	void operator =(Polynomial obj)
	{
		totalTerms = obj.totalTerms;
		coeff = new int[totalTerms];
		exp = new int[totalTerms];
		for (int i = 0; i < totalTerms; i++)
		{
			coeff[i] = obj.coeff[i];
		}
		for (int i = 0; i < totalTerms; i++)
		{
			exp[i] = obj.exp[i];
		}
	}
};
ostream& operator <<(ostream& out, const Polynomial& obj)
{
	for (int i = 0; i < obj.totalTerms; i++)
	{
		if (obj.exp[i]==0) {
			out << obj.coeff[i];
		}
		else
		{
			if (obj.coeff[i] == 1)
			{
				cout << "x^" << obj.exp[i];
			}
			else
			    out << obj.coeff[i] << "x^" << obj.exp[i];
		}
		if (i < obj.totalTerms - 1)
			out << "+";
	}
	return out;

}
int main()
{
	int coeff_P1[] = { 1,2,5 };
	int exp_P1[] = { 4,2,0 };
	int coeff_P2[] = { 4,3 };
	int exp_P2[] = { 6,2 };
	Polynomial P1(3, coeff_P1, exp_P1);
	Polynomial P2(2, coeff_P2, exp_P2);
	cout << "P1= " << P1 << endl;
	cout << "P2= " << P2 << endl;
	if (!P1)
		cout << "P1 is zero" << endl;
	if (P1 != P2)
		cout << "P1 is not equal to P2." << endl;
	Polynomial P3 = P1 + P2;
	cout << "P3= " << P3 << endl;
	cout << ++P1 << endl;
	cout << P1 << endl;
	cout <<P1++ << endl;
	cout << P1 << endl;
	P3 = 2+P1;
	cout << "P3= " << P3 << endl;
	system("pause");
}