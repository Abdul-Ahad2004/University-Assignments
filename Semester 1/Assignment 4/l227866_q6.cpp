#include<iostream>
using namespace std;
bool addElement(int set[], int& noe, int capacity, int element)
{
	if (noe < capacity)
	{
		set[noe] = element;
		noe++;
		return true;
	}
	else
	{
		return false;
	}

}
bool removeElement(int set[], int& noe, int capacity, int element)
{
	int count = 0;
	for (int i = 0; i < noe; i++)
	{
		if (set[i] == element)
		{
			noe--;
			for (int j = i ;j < noe; j++)
			{
				set[i] = set[i + 1];
			}
		
			count++;
			break;
			}
		}
	if (count == 1)
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool searchElement(int set[], int noe, int element)
{
	for (int ind = 0; ind < noe; ind++)
	{
		if (set[ind] == element)
		{
			return true;
		}
		if (ind == noe - 1 && set[ind] != element)
		{
			return false;
		}
	}

}
int searchElementPosition(int set[], int noe, int element)
{
	for (int ind = 0; ind < noe; ind++)
	{
		if (set[ind] == element)
		{
			return ind;
		}
		if (ind == noe - 1 && set[ind] != element)
		{
			cout << " (Element is not found in the set)." << endl;
		}
	}

}
bool isEmpty(int noe)
{
	if (noe == 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool isFull(int noe, int capacity)
{
	if (noe == capacity)
	{
		return true;
	}
	else
	{
		return false;
	}

}
void displaySet(int set[], int noe)
{
	cout << "Set = {";
	for (int ind = 0; ind < noe; ind++)
	{
		cout << set[ind];
		if (ind < noe-1)
		{
			cout << ",";
		}
	}
	cout << " } " << endl;

}
void intersection(int setA[], int setB[], int setANoe, int setBNoe, int newSet[], int newSetNoe)
{
	for (int ind = 0; ind <setANoe; ind++)
	{
		for (int j = 0; j < setANoe; j++)
		{
			if (setA[ind] == setB[j])
			{
				newSet[newSetNoe] =setA[ind];
				newSetNoe++;
			}
		}
	}
	cout << " Intersection = {";
	for (int ind = 0; ind < newSetNoe; ind++)
	{
		cout << newSet[ind];
		if (ind < newSetNoe)
		{
			cout << ",";
		}
	}
	cout << " } " << endl;
}
void union1(int setA[], int setB[], int setANoe, int setBNoe,int newSet[], int newSetNoe)
{
	int r = 0;
	for (int i = 0; i < setANoe; i++)
	{
		newSet[i] = setA[i];
		r++;
		newSetNoe++;
	}
	int count;
	for (int j = 0; j < setBNoe; j++)
	{
		count = 0;
		for (int i = 0; i < setANoe; i++)
		{
			if (setA[i] == setB[j])
			{
				count = 1;
				break;
			}
		}
		if (count != 1)
		{
			newSet[r] = setB[j];
			r++;
			newSetNoe++;
		}

	}
	for (int i = 0; i < newSetNoe; i++)
	{
		for (int j = i + 1; j < newSetNoe; j++)
		{
			if (newSet[i] > newSet[j])
			{
				int temp = newSet[i];
				newSet[i] = newSet[j];
				newSet[j] = temp;
			}
		}
	}
	cout << " Union= {";
	for (int ind = 0; ind < newSetNoe; ind++)
	{
		cout << newSet[ind];
		if (ind < newSetNoe-1)
		{
			cout << ",";
		}
	}
	cout << " } " << endl;
}
void difference(int setA[], int setB[], int setANoe, int setBNoe, int newSet[], int newSetNoe)
{
	for (int i = 0,r=0; i < setANoe; i++)
	{
		int count = 0;
		for (int j = 0; j < setBNoe; j++)
		{
			if (setA[i] == setB[j])
			{
				count++;
			}
		}
		if (count ==0)
		{
			newSet[r] = setA[i];
			r++;
			newSetNoe++;
		}
	}
	cout << " Difference= {";
	for (int ind = 0; ind < newSetNoe; ind++)
	{
		cout << newSet[ind];
		if (ind < newSetNoe-1)
		{
			cout << ",";
		}
	}
	cout << " } " << endl;
}
int isSubset(int setA[], int setB[], int setANoe, int setBNoe)
{
	int total = 0;
	for (int j = 0; j < setBNoe; j++)
	{
		for (int i = 0; i < setANoe; i++)
		{
			if (setB[j] == setA[i])
				total++;
		}
		if (total == setBNoe && setANoe == setBNoe)
			return 2;
		else if (total >= setBNoe)
			return 1;

	}
	if (total < setBNoe)
		return 0;
	
}
void displayCrossProduct(int setA[], int setB[], int setANoe, int setBNoe)
{
	cout << "Cross Product={ ";
	for (int i = 0; i < setANoe; i++)
	{
		for (int j = 0; j < setBNoe; j++)
		{
			cout << "(" << setA[i] << "," << setB[j] << ")";
			if (j < setBNoe-1)
			{
				cout << ",";
			}
		}
	}
	cout << "}" << endl;

}
void displayPowerSet(int set[], int noe)
{
	cout << "Power set ={";
	cout << "{},";
	for (int i = 0; i < noe; i++)
	{
		cout << "{" << set[i] << "},";
		for (int j = i + 1; j < noe; j++)
		{
			cout << "{" << set[i] << "," << set[j] << "},";
		}
	}
	if (noe >= 3) {
		cout << "{";
		for (int i = 0; i < noe; i++)
		{
			cout << set[i] << ",";
			int j = i + 1;
			for (; j < noe; j++)
			{
				cout << set[j];
				if (j < noe - 1)
					cout << ",";
			}
			if (j == noe)
				break;
		}
		cout << "}";
	}
	cout << "}" << endl;
}
void creatClone(int sourceSet[], int sourceNoe, int sourceCapacity, int targetSet[], int targetNoe, const int& targetCapacity)
{
	targetNoe = sourceNoe;
	for (int i = 0; i < sourceNoe; i++)
	{
		targetSet[i] = sourceSet[i];
	}
	cout << "Clone={ ";
	for (int i = 0; i < targetNoe; i++)
	{
		cout << targetSet[i];
		if (i < targetNoe - 1)
			cout << ",";
	}
	cout << "}" << endl;

}
int main()
{
	const int setAcapacity = 10;
	int setAnoe = 0;
	int setA[setAcapacity] = { 0 };
	const int setBcapacity = 7;
	int setBnoe = 0;
	int setB[setBcapacity] = { 0 };
	cout<< "For add element: " << addElement(setA, setAnoe, setAcapacity, 5)<<endl;
	cout << "Set A elements are: ";
	for (int ind = 0; ind <setAnoe; ind++)
	{
		cout << setA[ind] << " ";
	}
	cout << endl;
	cout << "For remove element: " << removeElement(setA, setAnoe, setAcapacity, 9) << endl;
	cout << "Set A elements are: ";
	for (int ind = 0; ind < setAnoe; ind++)
	{
		cout << setA[ind] << " ";
	}
	cout << endl;
	cout <<"For add element: "<< addElement(setB, setBnoe, setBcapacity, 1) << endl;
	cout << "Set B elements are: ";
	for (int ind = 0; ind < setBnoe; ind++)
	{
		cout << setB[ind] << " ";
	}
	cout << endl;
	cout << "For remove element: " << removeElement(setB, setBnoe, setBcapacity, 4) << endl;
	cout << "Set B elements are: ";
	for (int ind = 0; ind < setBnoe; ind++)
	{
		cout << setB[ind] << " ";
	}
	cout << endl;
	cout << "For search element: " << searchElement(setA, setAnoe, 9) << endl;
	cout << "For search element position: " << searchElementPosition(setA, setAnoe, 9)<<endl;
	cout << "For empty: " << isEmpty(setAnoe) << endl;
	cout << "For full : " << isFull(setAnoe, setAcapacity) << endl;
	displaySet(setA,setAnoe);
	int newSet[1000] = { 0 };
	int newnoe = 0;
	intersection(setA, setB, setAnoe, setBnoe, newSet, newnoe);
	union1(setA, setB, setAnoe, setBnoe, newSet, newnoe);
	difference(setA, setB, setAnoe, setBnoe, newSet, newnoe);
	cout << "For subset: " << isSubset(setA, setB, setAnoe, setBnoe) << endl;
	displayCrossProduct(setA,setB,setAnoe,setBnoe);
	displayPowerSet(setA,setAnoe);
	const int targetCapacity =10;
	int targetnoe = 0;
	int targetSet[targetCapacity] = { 0 };
	creatClone(setA, setAnoe, setAcapacity, targetSet, targetnoe, targetCapacity);
}