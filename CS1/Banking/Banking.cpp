// Chase Brown
// Program #2 (Banking)
// Sept 21, 2017

#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;

void main()
{
	int account, i;
	double minbal, oldbal, bal, inter, fee, totinter, totfee, totold, totnew;
	char acctype;
	totinter = 0;
	totfee = 0;
	totold = 0;
	totnew = 0;
	ifstream inf;
	ofstream outf;
	inf.open("Banking.dat");
	outf.open("Banking.ot");
	outf.setf(ios::fixed);
	outf.precision(2);

	outf << endl << setw(47) << "Main Street Credit Union" << endl
		<< setw(41) << "Month 9 Report" << endl << endl
		<< setw(17) << "Account" << setw(8) << "Old" << setw(13) << "Minimum" << setw(12) << "Interest" << endl
		<< setw(7) << "Account" << setw(8) << "Type" << setw(12) << "Balance" << setw(11) << "Balance"
		<< setw(11) << "Gained" << setw(8) << "Fees" << setw(10) << "Balance" << endl;

	for (i = 1; i <= 68; i++) outf << "=";
		outf << endl;

	for (i = 1; i <= 10; i++)
	{
		inf >> account >> acctype >> minbal >> bal;
		inter = 0;
		fee = 0;
		oldbal = bal;
		if (acctype == 's')
		{
			if (bal > minbal + 2500)
			{
				totold += bal;
				inter = bal * .02;
				totinter += bal * .02;
				bal *= 1.02;
				totnew += bal;
			}
			else if (bal >= minbal)
			{
				totold += bal;
				inter = bal * .015;
				totinter += bal * .015;
				bal *= 1.015;
				totnew += bal;
			}
			else if (bal < minbal)
			{
				totold += bal;
				fee = 25;
				totfee += 25;
				bal -= 25;
				totnew += bal;
			}
			else
				outf << "Error in Savings Code" << endl;
		}
		else if (acctype == 'c')
		{
			if (bal > minbal + 5000)
			{
				totold += bal;
				inter = bal * .0075;
				totinter += bal * .0075;
				bal *= 1.0075;
				totnew += bal;
			}
			else if (bal >= minbal)
			{
				totold += bal;
				inter = bal * .005;
				totinter += bal * .005;
				bal *= 1.005;
				totnew += bal;
			}
			else if (bal < minbal)
			{
				totold += bal;
				fee = 35;
				totfee += 35;
				bal -= 35;
				totnew += bal;
			}
			else
				outf << "Error in Credit Code" << endl;
		}
		else
			outf << "Error in Sorting Code" << endl;
		if (fee > 0)
			outf << setw(7) << account << setw(7) << acctype << setw(13) << oldbal << "*" << setw(10) << minbal
				<< setw(11) << inter << setw(8) << fee << setw(10) << bal << endl;
		else
			outf << setw(7) << account << setw(7) << acctype << setw(13) << oldbal << setw(11) << minbal
				<< setw(11) << inter << setw(8) << fee << setw(10) << bal << endl;
	}
	for (i = 1; i <= 68; i++) outf << "-";
	outf << endl << "Total" << setw(22) << totold << setw(22) << totinter << setw(8) << totfee << setw(10) << totnew << endl
		<< endl << "*Account Balance Below Minimum Amount, Fees Charged" << endl;
}
