//Chase Brown
//Program5
#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
#include"fraccalc.h"
void main()
{
	rational x, y, z;
	ofstream outf("fraccalc.ot");
	ifstream inf("fraccalc.dat");
	while (!inf.eof())
	{
		inf >> x >> y >> ws;
		x.print(outf);
		y.print(outf);
		z = x + y;
		outf << x << " + " << y << " = " << z << endl;
		z = x - y;
		outf << x << " - " << y << " = " << z << endl;
		z = x * y;
		outf << x << " * " << y << " = " << z << endl;
		z = x / y;
		outf << x << " / " << y << " = " << z << endl << endl;
	}
	system("pause");
}