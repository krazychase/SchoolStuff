//Chase Brown
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

void main()
{
	vector<int> v;
	vector<int>::iterator viter;
	ifstream inf("vector.dat");
	ofstream outf("vector.ot");
	int x;

	//store ints in vector
	while (!inf.eof())
	{
		inf >> x;
		v.push_back(x);
	}

	//output vector
	outf << "Output vector" << endl;
	for (viter = v.begin(); viter != v.end(); viter++)
		outf << *viter << " ";

	//sort and output vector
	sort(v.begin(), v.end());
	outf << endl << endl << "Sort vector and output" << endl;
	for (viter = v.begin(); viter != v.end(); viter++)
		outf << *viter << " ";
}