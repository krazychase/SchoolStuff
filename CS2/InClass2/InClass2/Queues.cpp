//Chase Brown
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;

void main()
{
	queue<string> q;
	ifstream inf("queue.dat");
	ofstream outf("queue.ot");
	string x,y;

	//Step 1 read in data
	while (!inf.eof())
	{
		inf >> x >> y;
		q.push(x);
		q.push(y);
	}

	//step 2 output queue size
	outf << "Output queue size: " << q.size() << endl << endl;

	//step 3 output/format queue
	outf << "Output data:" << endl;
	outf << setw(15) << "Class   #" << endl
		<< "----------------" << endl;
	while (!q.empty())
	{
		string temp;
		temp = q.front();
		q.pop();
		outf << setw(11) << q.front() << "  " << temp << endl;
		q.pop();
	}
}