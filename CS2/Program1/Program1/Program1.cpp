//Chase Brown
//Program 1 

#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;
const int maxc = 30;
struct Ctype
{
	int crn, crhrs, numstu, stucrhrs, totstucrhrs;
	string course, prof;
};
const Ctype initrec = { 0,0,0,0,0,"NoCourse","NoProf" };

void initem(Ctype c[], int &numc)
{
	int i;
	for (i = 0; i < maxc; i++) c[i] = initrec;
	numc = 0;
}
void readem(Ctype c[], int &numc)
{
	ifstream inf("Program1.dat");
	int i = 0;
	while (!inf.eof())
	{
		inf >> c[i].crn >> c[i].course >> c[i].crhrs
			>> c[i].numstu >> c[i].prof >> ws;
		i++;
	}
	numc = i;
}
void findstucrhrs(Ctype c[], int numc)
{
	int i;
	for (i = 0; i < numc; i++)
	{
		c[i].stucrhrs = c[i].crhrs * c[i].numstu;
		c[i].totstucrhrs += c[i].stucrhrs;
	}
}
void printem(Ctype c[], int numc, ofstream &outf)
{
	int i;
	outf << setw(26) << "Credit" << setw(7) << "# of" << setw(22) << "Total" << endl
		<< "Crn" << setw(10) << "Course" << setw(12) << "Hours" << setw(10) 
		<< "Students" << setw(12) << "Professor" << setw(8) << "Hours" << endl;
	for (i = 0; i < 60; i++) outf << "=";
	outf << endl;
	for (i = 0; i < numc; i++)
		outf << left << setw(7) << c[i].crn << setw(13) << c[i].course << right << setw(3)
		<< c[i].crhrs << setw(9) << c[i].numstu << left << "      " << setw(12) << c[i].prof 
		<< right << setw(5) << c[i].totstucrhrs << endl; 
	for (i = 0; i < 60; i++) outf << "-";
	outf << endl;

}
void swapem(Ctype &x, Ctype &y)
{
	Ctype temp;
	temp = x;
	x = y;
	y = temp;
}
void sort(Ctype c[], int numc)
{
	int i, j;
	for (j = 0; j < numc - 1; j++)
		for (i = 0; i < numc - 1; i++)
			if (c[i].stucrhrs < c[i + 1].stucrhrs)
				swapem(c[i], c[i + 1]);
}
void findave(Ctype c[], int numc, ofstream &outf)
{
	int i, totstu = 0, totclass = 0, ave;
	for (i = 0; i < numc; i++)
	{
		totstu += c[i].numstu;
		totclass++;
	}
	ave = totstu / totclass;
	outf << endl << "There are an average of " << ave 
		<< " students per class." << endl << endl;
}
void findtotsubj(Ctype c[], int numc, ofstream &outf)
{
	int i, algebra = 0, trig = 0, prec = 0, geo = 0;
	for (i = 0; i < numc; i++)
	{
		if (c[i].course == "Algebra") algebra++;
		else if (c[i].course == "Trigonometry") trig++;
		else if (c[i].course == "Precalculus") prec++;
		else if (c[i].course == "Geometry") geo++;
	}
	outf << "Algebra" << setw(14) << "Trigonometry" << setw(13) 
		<< "Precalculus" << setw(10) << "Geometry" << endl;
	for (i = 0; i < 45; i++) outf << "=";
	outf << endl << setw(4) << algebra << setw(12) << trig 
		<< setw(13) << prec << setw(12) << geo << endl;
}
void main()
{
	Ctype c[maxc];
	int numc;
	ofstream outf("Program1.ot");
	outf.setf(ios::fixed);
	outf.precision(2);

	initem(c, numc);
	readem(c, numc);
	findstucrhrs(c, numc);
	printem(c, numc, outf);
	sort(c, numc);
	printem(c, numc, outf);
	findave(c, numc, outf);
	findtotsubj(c, numc, outf);
	system("pause");
}