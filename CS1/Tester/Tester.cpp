//Chase Brown
//Class Program 1
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;

void main()
{
	ofstream outf;
	outf.open("Tester.ot");
	ifstream inf;
	inf.open("Tester.dat");
	string str1, str2, str3, sub1, sub2, sub3;
	int len1, len2, len3 ,comma1, comma2, comma3;
	char ch1, ch2, ch3;

	//Step 1 Read in strings using getline
	getline(inf, str1);
	getline(inf, str2);
	getline(inf, str3);
	outf << "Step 1: Input Strings " << endl << str1 << endl 
		<< str2 << endl << str3 << endl << endl;

	//Step 2 Find string lengths
	len1 = str1.length();
	len2 = str2.length();
	len3 = str3.length();
	outf << "Step 2: Determine String Length: " << endl
		<< "String 1 Length: " << len1 << endl
		<< "String 2 Length: " << len2 << endl
		<< "String 3 Length: " << len3 << endl << endl;

	//Step 3 Find position of commas
	comma1 = str1.find(',');
	comma2 = str2.find(',');
	comma3 = str3.find(',');
	outf << "Step 3: Find position of ',' in each string:" << endl
		<< "String 1 comma in position: " << comma1 << endl
		<< "String 2 comma in position: " << comma2 << endl
		<< "String 3 comma in position: " << comma3 << endl << endl;

	//Step 4 Find character 2 before comma
	ch1 = str1[comma1 - 2];
	ch2 = str2[comma2 - 2];
	ch3 = str3[comma3 - 2];
	outf << "Step 4: Find character 2 before comma:" << endl
		<< "String 1 character: " << ch1 << endl
		<< "String 2 character: " << ch2 << endl
		<< "String 3 character: " << ch3 << endl << endl;

	//Step 5 Get substring 2 after comma
	sub1 = str1.substr(comma1 + 2, len1);
	sub2 = str2.substr(comma2 + 2, len2);
	sub3 = str3.substr(comma3 + 2, len3);
	outf << "Step 5: Get substring 2 after comma:" << endl
		<< sub1 << endl << sub2 << endl << sub3 << endl << endl;

	//Step 6 Delete comma
	str1 = str1.erase(comma1, 1);
	str2 = str2.erase(comma2, 1);
	str3 = str3.erase(comma3, 1);
	outf << "Step 6: Delete comma:" << endl
		<< str1 << endl << str2 << endl << str3 << endl << endl;

	//Step 7 Insert "CWH" where comma was
	str1 = str1.insert(comma1, "CWH");
	str2 = str2.insert(comma2, "CWH");
	str3 = str3.insert(comma3, "CWH");
	outf << "Step 7: Insert \"CWH\" where comma was" << endl
		<< str1 << endl << str2 << endl << str3 << endl << endl;
}