// Chase Brown
// Program 3 (Test Calculator)

#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;

void printtitles(ofstream &outf)
{
	int i;
	outf << endl << setw(39) << "Report Card" << endl << setw(38) << "2017-2018" << endl << endl
		<< setw(28) << "Quiz" << setw(27) << "Program" << endl
		<< "Name" << setw(9) << "Quiz 1" << setw(8) << "Quiz 2" << setw(9) << "Average" << setw(8) << "Prog 1"
		<< setw(8) << "Prog 2" << setw(9) << "Average" << setw(7) << "Final" << setw(7) << "Grade" << endl;
	for (i = 0; i <= 70; i++) outf << "=";
		outf << endl;
}

double getave(int x,int y)
{
	double average = (x + y) / 2.0;
	return average;
}

void getstudentave(double x, double y, int z, double &studentave)
{
	studentave = (x*.4) + (y*.4) + (z*.2);
}

char getgrade(double stave)
{
	char grade;
	if (stave >= 90)
		grade = 'A';
	else if (stave >= 80)
		grade = 'B';
	else if (stave >= 70)
		grade = 'C';
	else if (stave >= 60)
		grade = 'D';
	else
		grade = 'F';
	return grade;
}

void main()
{
	string name;
	int n = 0, quiz1, quiz2, prog1, prog2, final;
	double quizave, progave, studenttot = 0, studentave = 0, q1tot = 0, q2tot = 0,
		q1ave = 0, q2ave, p1tot = 0, p2tot = 0, p1ave, p2ave,
		finaltot = 0, finalave, classtot = 0, classave;
	char grade;
	ifstream inf;
	ofstream outf;
	inf.open("TestCalc.dat");
	outf.open("TestCalc.ot");
	outf.setf(ios::fixed);
	outf.precision(1);

	printtitles(outf);

	while (!inf.eof())
	{
		inf >> name >> quiz1 >> quiz2 >> prog1 >> prog2 >> final;

		quizave = getave(quiz1, quiz2);
		progave = getave(prog1, prog2);
		getstudentave(quizave, progave, final, studentave);
		grade = getgrade(studentave);
		q1tot += quiz1;
		q2tot += quiz2;
		p1tot += prog1;
		p2tot += prog2;
		finaltot += final;
		studenttot += studentave;

		outf << left << setw(5) << name << right << setw(6) << quiz1 << setw(8) << quiz2 << setw(10) << quizave
			<< setw(7) << prog1 << setw(8) << prog2 << setw(10) << progave << setw(6) << final
			<< setw(4) << grade << " (" << studentave << ")" << endl;

		n++;
	}

	q1ave = q1tot / n;
	q2ave = q2tot / n;
	p1ave = p1tot / n;
	p2ave = p2tot / n;
	finalave = finaltot / n;
	classave = studenttot / n;
	int i;
	for (i = 0; i <= 70; i++) outf << "-";
	outf << endl << "Average" << setw(6) << q1ave << setw(8) << q2ave << setw(17) << p1ave << setw(8) << p2ave
		<< setw(16) << finalave << setw(8) << classave;
	cout << "done";
}