//Chase Brown
//Roman Numeral Conversion
#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
const int maxn = 8;
void initem(string r[])
{
	int i ;
	for (i = 0; i < maxn; i++) r[i] = "*NoNumber";
}
void readem(string r[])
{
	int i = 0;
	ifstream inf;
	inf.open("RomanNumeral.dat");
	while (!inf.eof())
	{
		inf >> r[i];
		i++;
	}
}
int value(char x)
{
	if (x == 'I')
		return 1;
	if (x == 'V')
		return 5;
	if (x == 'X')
		return 10;
	if (x == 'L')
		return 50;
	if (x == 'C')
		return 100;
	if (x == 'D')
		return 500;
	if (x == 'M')
		return 1000;
	else return -1;
}
void convert(string r[], ofstream &outf)
{
	string roman;
	int i, j, value1, value2, numb;

	for (j = 0; j < maxn; j++)
	{
		numb = 0;
		roman = r[j];
		for (i = 0; i < roman.length(); i++)
		{
			value1 = value(roman[i]);
			if (i + 1 < roman.length())
			{
				value2 = value(roman[i + 1]);
				if (value1 >= value2)
					numb += value1;
				else
				{
					numb += value2 - value1;
					i++;
				}
			}

			else
			{
				numb += value1;
				i++;
			}
		}
		outf << roman << " = " << numb << endl;
	}

}
void main()
{
	ofstream outf;
	outf.open("RomanNumeral.ot");
	string r[maxn], roman;
	initem(r);
	readem(r);
	convert(r, outf);
}