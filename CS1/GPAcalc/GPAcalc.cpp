//Chase Brown
//Program 4 (GPA Calculator)

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int maxc = 100;

void initem(int crhrs[], int gradevalue[], int qualpts[], char grade[],
	string dept[], string crsenum[], string name[], int& numc,
	int& totcrhrs, int& totqualpts)
{
	int i;
		for (i = 0; i < maxc; i++)
		{
			crhrs[i] = 0;
			gradevalue[i] = 0;
			qualpts[i] = 0;
			grade[i] = 'X';
			dept[i] = "XXXX";
			crsenum[i] = "999X";
			name[i] = "**No Name!!!!**";
		}
		numc = 0;
		totcrhrs = 0;
		totqualpts = 0;
}
void readem(string dept[], string crsenum[], string name[],
	int crhrs[], char grade[], int& numc)
{
	ifstream inf;
	inf.open("GPAcalc.dat");
	int i = 0;
	while (!inf.eof())
	{
		inf >> dept[i] >> crsenum[i] >> name[i]
			>> crhrs[i] >> grade[i];
		i++;
	}
	numc = i;
}
void calcpts(char grade[], int crhrs[], int gradevalue[],
	int qualpts[], int& totcrhrs, int& totqualpts)
{
	int i;
	for (i = 0; i < maxc - 1; i++)
	{
		if (grade[i] == 'A') gradevalue[i] = 4;
		else if (grade[i] == 'B') gradevalue[i] = 3;
		else if (grade[i] == 'C') gradevalue[i] = 2;
		else if (grade[i] == 'D') gradevalue[i] = 1;
		else gradevalue[i] = 0;
		qualpts[i] = gradevalue[i] * crhrs[i];
		totcrhrs += crhrs[i];
		totqualpts += qualpts[i];
	}
}
void printem1(string dept[], string crsenum[], string name[],
	int crhrs[], char grade[], int numc, int totcrhrs,
	int totqualpts, ofstream& outf)
{
	int i;
	double gpa;
	outf << setw(12) << "Course" << setw(35) << "Credit" << endl
		<< "Dept" << setw(5) << "#" << setw(20) << "Course" << setw(17) 
		<< "Hours" << setw(8) << "Grade" << endl;
	for (i = 0; i <= 70; i++) outf << '=';
	outf << endl;
	gpa = 1.0 * totqualpts / totcrhrs;
	for (i = 0; i < numc - 1; i++) outf << dept[i] << setw(7) << crsenum[i] 
		<< "  " << setw(26) << left << name[i] << right << setw(5) 
		<< crhrs[i] << setw(8) << grade[i] << endl;
	for (i = 0; i <= 70; i++) outf << '-';
	outf << endl << setw(6) << "Totals" << setw(16) << "Courses: " << numc - 1
		<< setw(20) << totcrhrs << setw(23) << "GPA: " 
		<< gpa << endl << endl;
}
void printem2(string crsenum[],int crhrs[], int numc, ofstream &outf)
{
	int i, ftot = 0, stot = 0, jtot = 0, srtot = 0,
		fcr = 0, scr = 0, jcr = 0, srcr = 0;
	outf << setw(24) << "Total" << endl
		<< setw(16) << "Total" << setw(9) << "Credit" << endl
		<< setw(6) << "Level" << setw(11) << "Courses"
		<< setw(7) << "Hours" << endl;
	for (i = 0; i <= 25; i++) outf << '=';
	outf << endl;
	for (i = 0; i < numc - 1; i++)
	{
		if (crsenum[i] < "200")
		{
			ftot++;
			fcr += crhrs[i];
		}
		else if (crsenum[i] < "300")
		{
			stot++;
			scr += crhrs[i];
		}
		else if (crsenum[i] < "400")
		{
			jtot++;
			jcr += crhrs[i];
		}
		else
		{
			srtot++;
			srcr += crhrs[i];
		}
	}
	outf << setw(8) << "Freshman" << setw(6) << ftot << setw(9) << fcr << endl
		<< setw(8) << "Sophmore" << setw(6) << stot << setw(9) << scr << endl
		<< setw(8) << "Junior" << setw(6) << jtot << setw(9) << jcr << endl
		<< setw(8) << "Senior" << setw(6) << srtot << setw(9) << srcr << endl;
}
void swapem(int& x, int& y)
{
	int temp;
	temp = x;
	x = y;
	y = temp;
}
void swapem(string& x, string& y)
{
	string temp;
	temp = x;
	x = y;
	y = temp;
}
void swapem(char& x, char& y)
{
	char temp;
	temp = x;
	x = y;
	y = temp;
}
void sortcrsenum(string dept[], string crsenum[], string name[],
	int crhrs[], char grade[])
{
	int i, j;
	for (j = 0; j < maxc - 1; j++)
		for (i = 0; i < maxc - 1; i++)
			if (crsenum[i] > crsenum[i + 1])
			{
				swapem(crsenum[i], crsenum[i + 1]);
				swapem(dept[i], dept[i + 1]);
				swapem(name[i], name[i + 1]);
				swapem(crhrs[i], crhrs[i + 1]);
				swapem(grade[i], grade[i + 1]);
			}
}
void getupper(string crsenum[], int crhrs[], ofstream &outf)
{
	int i, ud = 0;
	for (i = 0; i < maxc - 1; i++)
	{
		if (crsenum[i] >= "300") ud += crhrs[i];
	}
	outf << "**You have taken " << ud << " Upper Division Classes."
		<< endl << "A minimum of 40 are needed to graduate";
}
void main()
{
	int crhrs[maxc], gradevalue[maxc], qualpts[maxc],
		numc = 0, totcrhrs = 0, totqualpts = 0;
	char grade[maxc];
	string dept[maxc], crsenum[maxc], name[maxc];
	ofstream outf;
	outf.open("GPAcalc.ot");
	outf.setf(ios::fixed);
	outf.precision(2);

	initem(crhrs, gradevalue, qualpts, grade, dept, crsenum, 
		name, numc, totcrhrs, totqualpts);
	readem(dept, crsenum, name, crhrs, grade, numc);
	calcpts(grade, crhrs, gradevalue, qualpts, totcrhrs, totqualpts);
	printem1(dept, crsenum, name, crhrs, grade, numc,
		totcrhrs, totqualpts, outf);
	sortcrsenum(dept, crsenum, name, crhrs, grade);
	printem1(dept, crsenum, name, crhrs, grade, numc,
		totcrhrs, totqualpts, outf);
	printem2(crsenum, crhrs, numc, outf);
	getupper(crsenum, crhrs, outf);
	system("pause");
}