//Chase Brown
//Program 6
#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

const int maxnum = 10000; 
int moves = 0, compares = 0;

void init(double a[])
{
	int i = 0;
	moves = 0;
	compares = 0;
	for (i = 0; i < maxnum - 1; i++)
	{
		a[i] = 0;
	}
}
void readin(double a[])
{
	ifstream inf("data.dat");
	int i = 0;
	while (!inf.eof())
	{
		inf >> a[i];
		i++;
	}
}
void swap(double &x, double &y)
{
	double temp;
	temp = x;
	x = y;
	y = temp;
	moves += 3;
}
void bubblesort(double a[])
{
	int i, j;
	for (j = 0; j < maxnum - 1; j++)
		for (i = 0; i < maxnum - 1; i++)
		{
			if (a[i] > a[i + 1]) swap(a[i], a[i + 1]);
			compares++;
		}
}
void selectsort(double a[])
{
	int k, small, j;
	if (maxnum > 1)
	{
		for (k = 0; k < maxnum - 1; k++)
		{
			small = k;
			compares++;
			for (j = k + 1; j < maxnum; j++)
			{
				compares++;
				if (a[j] < a[small])
				{
					small = j;
					compares++;
				}
			}
			if (k != small)
			{
				swap(a[k], a[small]);
				compares++;
			}
		}
	}
}
void insertsort(double a[])
{
	int j, k;
	double save;
	for (k = maxnum - 1; k >= 0; k--)
	{
		j = k + 1;
		save = a[k];
		moves++;
		a[maxnum] = save;
		moves++;
		while (save > a[j])
		{
			a[j - 1] = a[j];
			j++;
			compares++;
		}
		a[j - 1] = save;
		moves++;
	}
}
void quicksort(double a[], int left, int right)
{
	int j, k;
	if (left < right)
	{
		j = left;
		k = right + 1;
		do
		{
			do
			{
				j++;
				compares++;
			} while (a[j] < a[left] && j <= k);
			do
			{
				k--;
				compares++;
			} while (a[k] > a[left] && k >= 0);
			if (j < k) swap(a[j], a[k]);
		} while (j <= k);
		swap(a[left], a[k]);
		quicksort(a, left, k - 1);
		quicksort(a, k + 1, right);
	}
}
void improvebs(double a[])
{
	int i = 1, j;
	bool sorted = false;
	while (sorted == false)
	{
		sorted = true;
		for (j = 0; j <= maxnum - i; j++)
			if (a[j] > a[j + 1])
			{
				sorted = false;
				swap(a[j], a[j + 1]);
				compares++;
			}
		i++;
	}
}
void print(double a[], string sortname, ofstream &outf)
{
	int i, j = 1, incr = 1000;
	outf << sortname << "  N = " << maxnum << endl;
	for (i = 0; i < maxnum; i += incr)
	{
		outf << setw(12) << a[i];
		j++;
		if (j > 5)
		{
			outf << endl;
			j = 1;
		}
	}
	outf << "Number of compares: " << compares << "   Number of Moves: " 
		<< moves << endl
		<< "Relative compares: " << 1.0 * compares / maxnum 
		<< "   Relative moves: " << 1.0 * moves / maxnum << endl << endl;
}
void main()
{
	ofstream outf("output.ot");
	outf.precision(3);
	outf.setf(ios::fixed);
	double a[maxnum + 1];
	int sloop = 0;
	string sortname;
	for (sloop = 0; sloop < 5; sloop++)
	{
		init(a);
		readin(a);
		switch (sloop)
		{
		case 0:  bubblesort(a);
			sortname = "Bubble Sort";
			break;
		case 1: selectsort(a);
			sortname = "Select Sort";
			break;
		case 2: insertsort(a);
			sortname = "Insert Sort";
			break;
		case 3: quicksort(a, 0, maxnum - 1);
			sortname = "Quick Sort";
			break;
		case 4: improvebs(a);
			sortname = "Improved Bubble Sort";
			break;
		}
		print(a, sortname, outf);
	}
	system("pause");
}