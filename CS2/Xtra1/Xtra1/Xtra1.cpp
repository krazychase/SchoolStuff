//Chase Brown
//Xtra Credit 1
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
const int maxlist = 50;
struct listtype
{
	string last, first;
	int id;
};
void createlist(listtype l[], int &numlist)
{
	int i;
	for (i = 0; i < maxlist-1; i++)
	{
		l[i].last = "NoLast";
		l[i].first = "NoFirst";
		l[i].id = -1;
	}
	numlist = 0;
}
bool emptylist(int numlist)
{
	return numlist <= 0;
}
bool fulllist(int numlist)
{
	return numlist >= maxlist;
}
void insert(listtype l[], int &numlist, string last, 
	string first, int id, ofstream &outf)
{
	int i, where;
	if (!fulllist(numlist))
	{
		where = 0;
		while (where < numlist && last > l[where].last) where++;
		for (i = numlist - 1; i >= where; i--)
		{
			l[where].last = last;
			l[where].first = first;
			l[where].id = id;
			numlist++;
		}
	}
	else outf << "List is full" << endl;
}
void read(listtype l[], int numlist, ofstream &outf)
{
	ifstream inf("Xtra1.dat");
	string first, last;
	int id;
	while (!inf.eof())
	{
		inf >> last >> first >> id;
		last.erase(last.find(","));
		insert(l, numlist, last, first, id, outf);
	}
}
void printlist(listtype l[], int numlist, ofstream &outf)
{
	int i;
	if (!emptylist(numlist))
	{
		outf << "ID #     Name" << endl;
		for (i = 0; i <= 35; i++) outf << "=";
		outf << endl;
		for (i = 0; i < numlist; i++)
			cout << l[i].id << "     " << l[i].first << " " << l[i].last << endl;
	}
	else outf << "List is empty" << endl;
	outf << endl;
}
void main()
{
	listtype l[maxlist];
	ofstream outf("Xtra1.ot");
	int numlist=0;
	createlist(l, numlist);
	read(l, numlist, outf);
	printlist(l, numlist, outf);
	system("pause");
}