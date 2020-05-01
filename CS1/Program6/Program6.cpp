//Chase Brown
//Program 6
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;
const int maxp = 50;
struct proftype
{
	string whole, first;
	char mi;
	string last, department;
	int salary;
};
const proftype initrec = 
{"*No Whole", "*No First", '$', "*No Last", "*No Dept", 0};
void initem(proftype p[], int& nump)
{
	int i;
	for (i = 0; i < maxp; i++) p[i] = initrec;
	nump = 0;
}
void readem(proftype p[], int& nump)
{
	int i = 0;
	ifstream inf;
	inf.open("Program6.dat");
	while (!inf.eof())
	{
		getline(inf, p[i].whole, '|');
		getline(inf, p[i].department, '|');
		inf >> p[i].salary >> ws;
		i++;
	}
	nump = i;
}
void swapem(proftype& x, proftype& y)
{
	proftype temp;
	temp = x;
	x = y;
	y = temp;
}
void sortdept(proftype p[], int nump)
{
	int i, j;
	for (j = 0; j < nump - 1; j++)
		for (i = 0; i < nump - 1; i++)
			if (p[i].department > p[i + 1].department)
				swapem(p[i], p[i + 1]);
}
void sortlast(proftype p[], int nump)
{
	int i, j;
	for (j = 0; j < nump - 1; j++)
		for (i = 0; i < nump - 1; i++)
			if (p[i].last > p[i + 1].last)
				swapem(p[i], p[i + 1]);
}
void separate(proftype p[], int nump)
{
	int i, period;
	for (i = 0; i < nump; i++)
	{
		period = p[i].whole.find('.');
		p[i].first = p[i].whole.substr(0, period - 2);
		p[i].mi = p[i].whole[period - 1];
		p[i].last = p[i].whole.substr(period + 2);
	}
}
void convert()
{
	cout << "Convert to string" << endl;
}
void printem(proftype p[], int nump, ofstream& outf)
{
	int i;
	outf << setw(11) << "Name" << setw(21) << "Department" 
		<< setw(22) << "Salary" << endl;
	for (i = 0; i <= 62; i++) outf << "=";
	outf << endl;
	for (i = 0; i < nump; i++)
		outf << left << setw(22) << p[i].whole << setw(22) << p[i].department 
		<< right << setw(10) << p[i].salary << endl;
	for (i = 0; i <= 62; i++) outf << "-";
	outf << endl << endl;
}
void printem2(proftype p[], int nump, ofstream& outf)
{
	int i, totsal = 0;
	string temp;
	for (i = 0; i < nump; i++)
		totsal += p[i].salary;
	outf << setw(11) << "Name" << setw(21) << "Department"
		<< setw(22) << "Salary" << endl;
	for (i = 0; i <= 62; i++) outf << "=";
	outf << endl;
	for (i = 0; i < nump; i++)
	{
		temp = p[i].last + " " + p[i].first + " " + p[i].mi + ".";
		outf << left << setw(22) << temp << setw(22) << p[i].department
			<< setw(10) << right << p[i].salary << endl;
	}
	for (i = 0; i <= 62; i++) outf << "-";
	outf << endl << "Total" << setw(49) << totsal << endl;
}
void main()
{
	proftype p[maxp];
	int nump;
	ofstream outf;
	outf.open("Program6.ot");

	initem(p, nump);
	readem(p, nump);
	printem(p, nump, outf);
	sortdept(p, nump);
	printem(p, nump, outf);
	separate(p, nump);
	sortlast(p, nump);
	printem2(p, nump, outf);
//	convert();
//	printem();
	system("pause");
}