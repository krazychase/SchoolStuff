//Chase Brown
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;

template <class mytype>
void swapem(mytype &x, mytype &y)
{
	mytype temp;
	temp = x;
	x = y;
	y = temp;
}
struct legendtype
{
	int id;
	string name;
};
//void main()
{
	ofstream outf("swap.ot");

	int x = 3, y = 5;
	outf << "Swap 2 Integers" << endl
		<< x << " " << y << endl;
	swapem(x, y);
	outf << x << " " << y << endl << endl;

	string a = "John", b = "Jane";
	outf << "Swap 2 strings" << endl
		<< a << " " << b << endl;
	swapem(a, b);
	outf << a << " " << b << endl << endl;

	legendtype L, Z;
	L.id = 1234;
	L.name = "Link";
	Z.id = 9894;
	Z.name = "Zelda";
	outf << "Swap 2 Structs" << endl
		<< L.id << " " << L.name << " " << Z.id << " " << Z.name << endl;
	swapem(L, Z);
	outf << L.id << " " << L.name << " " << Z.id << " " << Z.name << endl << endl;
	system("pause");
}