//Chase Brown
//Program 2 (Sets)

#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

const int maxs = 'z' + 1;

void emptyset(bool s[])
{
	int i;
	for (i = 'A'; i <= 'Z'; i++) s[i] = false;
}

void init(bool universal[], bool vowel[], bool myname[])
{
	ifstream inf("data.dat");
	int i;
	char ch;
	emptyset(universal);
	emptyset(vowel);
	emptyset(myname);
	for (i = 'A'; i <= 'Z'; i++) universal[i] = true;
	vowel['A'] = true;
	vowel['E'] = true;
	vowel['I'] = true;
	vowel['O'] = true;
	vowel['U'] = true;
	while(!inf.eof())
	{
		inf >> ch;
		myname[ch] = true;
	}
}

void print(bool s[], ofstream &outf)
{
	int i;
	for (i = 'A'; i <= 'Z'; i++) if (s[i]) outf << setw(2) << (char) i;
	outf << endl;
}

void setunion(bool set1[], bool set2[], bool s[], ofstream &outf)
{
	int i;
	for (i = 'A'; i <= 'Z'; i++)
		if (set1[i] == true || set2[i] == true) s[i] = true;
	print(s, outf);
	emptyset(s);
}

void intersect(bool set1[], bool set2[], bool s[], ofstream &outf)
{
	int i;
	for (i = 'A'; i <= 'Z'; i++)
		if (set1[i] == true && set2[i] == true) s[i] = true;
	print(s, outf);
	emptyset(s);
}

void difference(bool set1[], bool set2[], bool s[], ofstream &outf)
{
	int i;
	for (i = 'A'; i <= 'Z'; i++)
	{
		if (set1[i] == true) s[i] = true;
		if (set2[i] == true) s[i] = false;
	}
	print(s, outf);
	emptyset(s);
}

int cardinality(bool set[])
{
	int i, num = 0;
	for (i = 'A'; i <= 'Z'; i++)
		if (set[i] == true) num++;
	return num;
}

string equality(bool set1[], bool set2[], bool s[], ofstream &outf)
{
	int i;
	string ans = "True";
	for (i = 'A'; i <= 'Z'; i++)
		if (set1[i] == set2[i]) s[i] = true;
	i = 'A';
	for (i = 'A'; i <= 'Z'; i++)
		if(s[i] == false) ans = "False";
	emptyset(s);
	return ans;
}

int main()
{
	ofstream outf("output.ot");
	bool s[maxs], universal[maxs], vowel[maxs], myname[maxs];

	init(universal, vowel, myname);
	emptyset(s);
	outf << "Universal set: " << endl;
	print(universal, outf);
	outf << "Vowel set: " << endl;
	print(vowel, outf);
	outf << "My Name set: " << endl;
	print(myname, outf);
	outf << "Vowel union My Name: " << endl;
	setunion(vowel, myname, s, outf);
	outf << "My Name intersect Vowel: " << endl;
	intersect(vowel, myname, s, outf);
	outf << "My Name difference Vowel: " << endl;
	difference(myname, vowel, s, outf);
	outf << endl << "Number of elements in My Name: " << cardinality(myname) << endl;
	outf << "Number of elements in Universal: " << cardinality(universal) << endl;
	outf << endl << "My Name equals Vowel? " << equality(myname, vowel, s, outf) << endl;
	outf << "My Name equals My Name? " << equality(myname, myname, s, outf) << endl;
	return 0;
}
