//Chase Brown
//In Class 1
#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
#include"playaround.h"

void main()
{
	playclass1 a;
	playclass2 b;
	playclass1 x(5.125, 3.05);
	playclass2 y(15.125, 21.375);
	double area;
	ofstream outf("Inclass1.ot");
	outf << "Object has w = " << a.width << " l = " << a.length << endl
		<< "Object has w = " << b.getwidth() << " l = " << b.getlength() << endl;
	outf << "Step 3A - Print x and y" << endl;
	x.print(outf);
	y.print(outf);
	outf << "Step 3B - Print area of x and y" << endl;
	area = x.length * x.width;
	outf << "Object x has area of " << area << endl;
	area = y.getwidth() * y.getlength();
	outf << "Object y has area of " << area << endl;
	outf << "Step 3C - Change a, get area" << endl;
	a.length = 10.0;
	a.width = 2.638;
	area = a.length * a.width;
	outf << "Object a has area of " << area << endl;
	outf << "Step 3D - change b, get area" << endl;
	b.setlength(25.25);
	b.setwidth(11.125);
	area = b.getwidth() * b.getlength();
	outf << "Object b has area of " << area << endl;
	system("pause");
}
