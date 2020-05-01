//Chase Brown
//Program 5 (Library)
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;
const int maxbook = 50;
struct booktype
{
	int id;
	string title, author, genre;
	double price;
	int num;
	double value;
};
const booktype initrec = {0, "*No Title", "*No Author", "*No Genre", 0., 0, 0};
void initem(booktype book[], int& numb)
{
	int i;
	for (i = 0; i < maxbook; i++) book[i] = initrec;
	numb = 0;
}
void readem(booktype book[], int& numb)
{
	int i = 0;
	ifstream inf;
	inf.open("Library.dat");
	while (!inf.eof())
	{
		inf >> book[i].id >> book[i].title >> book[i].author 
			>> book[i].genre >> book[i].price >> book[i].num;
		i++;
	}
	numb = i;
}
void calcval(booktype book[], int& totbook, double& totvalue, int numb)
{
	int i;
	for (i = 0; i <= numb; i++)
	{
		book[i].value = book[i].num * book[i].price;
		totbook += book[i].num;
		totvalue += book[i].value;
	}
}
void swapem(booktype& x, booktype& y)
{
	booktype temp;
	temp = x;
	x = y;
	y = temp;
}
void sortid(booktype book[], int numb)
{
	int i, j;
	for (j = 0; j < numb - 1; j++)
		for (i = 0; i < numb - 1; i++)
			if (book[i].id > book[i + 1].id) swapem(book[i], book[i + 1]);
}
void sortauthor(booktype book[], int numb)
{
	int i, j;
	for (j = 0; j < numb - 1; j++)
		for (i = 0; i < numb - 1; i++)
			if (book[i].author > book[i + 1].author) 
				swapem(book[i], book[i + 1]);
}
void countbooks(booktype book[], int numb, ofstream& outf)
{
	int i, clasnum = 0, hornum = 0, textbnum = 0, westnum = 0;
	outf << "Classic" << setw(8) << "Horror" << setw(10) 
		<< "Textbook" << setw(9) << "Western" << endl;
	for (i = 0; i < 35; i++)outf << "-";
	outf << endl;
	for (i = 0; i < numb; i++)
	{
		if (book[i].genre == "Classic") clasnum++;
		else if (book[i].genre == "Horror") hornum++;
		else if (book[i].genre == "Textbook") textbnum++;
		else westnum++;
	}
	outf << setw(4) << clasnum << setw(9) << hornum << setw(9)
		<< textbnum << setw(9) << westnum << endl << endl;
}
void byauthor(string x, booktype book[], int numb, ofstream& outf)
{
	int i, authortot = 0;
	for (i = 0; i < numb; i++)
		if (book[i].author == x) authortot++;
	if (authortot > 0)
		outf << "We have " << authortot << " titles by " << x
		<< "." << endl;
	else
		outf << "We have 0 titles by " << x 
		<< ". Please try another author" << endl;
}
void printem(booktype book[], int numb, double totvalue,
	int totbook, ofstream& outf)
{
	int i;
	outf << setw(55) << "# of" << endl
		<< "ID#" << setw(7) << "Title" << setw(15) << "Author" << setw(12) 
		<< "Genre" << setw(10) << "Price" << setw(9) << "Copies" << endl;
	for (i = 0; i < 58; i++)outf << "=";
	outf << endl;
	for (i = 0; i < numb; i++)
		outf << book[i].id << left << "  " << setw(14) << book[i].title 
		<< setw(13) << book[i].author << setw(10) << book[i].genre << right 
		<< setw(6) << book[i].price << setw(6) << book[i].num << endl;
	for (i = 0; i < 58; i++)outf << "-";
	outf << endl;
	outf << setw(48) << totvalue << setw(6) << totbook << endl << endl;
}
void main()
{
	booktype book[maxbook];
	int totbook=0, numb;
	double totvalue=0;
	ofstream outf;
	outf.open("Library.ot");
	outf.setf(ios::fixed);
	outf.precision(2);

	initem(book, numb);
	readem(book, numb);
	calcval(book, totbook, totvalue, numb);
	sortid(book, numb);
 	printem(book, numb, totvalue, totbook, outf);
	sortauthor(book, numb);
	printem(book, numb, totvalue, totbook, outf);
	countbooks(book, numb, outf);
	byauthor("Shakespeare", book, numb, outf);
	system("pause");
}