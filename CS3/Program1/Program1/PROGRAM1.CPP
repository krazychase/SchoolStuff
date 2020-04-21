//Chase Brown
//Program 1

#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>
#include<time.h>
using namespace std;

const int maxnum = 20000;
int moves = 0, compares = 0;

void init(double a[], int num)
{
	int i;
	moves = 0;
	compares = 0;
	for (i = 0; i < num - 1; i++)
	{
		a[i] = 0;
	}
}

void readin(double a[], int num)
{
	ifstream inf("data.dat");
	int i;
	for (i = 0; i < num - 1; i++)
	{
		inf >> a[i];
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

void bubblesort(double a[], int num, ofstream &outf)
{
	int i, j;
	time_t start, end;
	start = clock();
	for (j = 0; j < num - 1; j++)
		for (i = 0; i < num - 1; i++)
		{
			if (a[i] > a[i + 1]) swap(a[i], a[i + 1]);
			compares++;
		}
	end = clock();
	outf << setw(5) << num << setw(12) << moves << setw(12) << compares 
		<< setw(10) << difftime(end, start) / CLOCKS_PER_SEC << endl;
}

void selectsort(double a[], int num, ofstream &outf)
{
	int k, small, j;
	time_t start, end;
	start = clock();
	if (num > 1)
	{
		for (k = 0; k < num - 2; k++)
		{
			small = k;
			compares++;
			for (j = k + 1; j < num; j++)
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
	end = clock();
	outf << setw(5) << num << setw(12) << moves << setw(12) << compares
		<< setw(10) << difftime(end, start) / CLOCKS_PER_SEC << endl;
}

int main()
{
	ofstream outf("output.ot");
	outf.precision(3);
	outf.setf(ios::fixed);
	double a[maxnum - 1];
	int num, incr = 2000;
	
	outf << setw(5) << "Num" << setw(12) << "Moves" << setw(12)
		<< "Compares" << setw(10) << "Time" << endl;
	outf << endl << "Bubble Sort" << endl;
	for (num = 2000; num <= maxnum; num += incr)
	{
		init(a, num);
		readin(a, num);
		bubblesort(a, num, outf);
	}

	outf << endl << "Select Sort" << endl;
	for (num = 2000; num <= maxnum; num += incr)
	{
		init(a, num);
		readin(a, num);
		selectsort(a, num, outf);
	}
	return 0;
}
