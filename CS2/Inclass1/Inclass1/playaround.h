#pragma once
class playclass1
{
public:
	double length, width;
	void print(ofstream &outf);
	playclass1();
	playclass1(double l, double w);
};
class playclass2
{
private:
	double length, width;
public:
	void setlength(double l);
	void setwidth(double w);
	double getlength();
	double getwidth();
	void print(ofstream &outf);
	playclass2();
	playclass2(double l, double w);
};