#include<fstream>
#include<cmath>
using namespace std;
#include"fraccalc.h"
rational::rational()
{
	num = 0;
	den = 1;
}
rational::rational(int n, int d)
{
	num = n;
	den = d;
}
int rational::getnum()
{
	return num;
}
int rational::getden()
{
	return den;
}
void rational::setnum(int n)
{
	num = n;
}
void rational::setden(int d)
{
	den = d;
}
void rational::print(ofstream &outf)
{
	outf << "Numerator = " << getnum() << " and Denominator = " << getden() << endl;
}
rational operator+ (rational one, rational two)
{
	rational answer;
	answer.num = (one.num * two.den) + (two.num * one.den);
	answer.den = one.den * two.den;
	reduce(answer);
	return answer;
}
rational operator- (rational one, rational two)
{
	rational answer;
	answer.num = (one.num * two.den) - (two.num * one.den);
	answer.den = one.den * two.den;
	reduce(answer);
	return answer;
}
rational operator* (rational one, rational two)
{
	rational answer;
	answer.num = one.num * two.num;
	answer.den = one.den * two.den;
	reduce(answer);
	return answer;
}
rational operator/ (rational one, rational two)
{
	rational answer;
	answer.num = one.num * two.den;
	answer.den = one.den * two.num;
	reduce(answer);
	return answer;
}
istream& operator>>(istream& ins, rational& one)
{
	char ch;
	ins >> one.num >> ch >> one.den >> ws;
	reduce(one);
	return ins;
}
ostream& operator<<(ostream& outs, rational one)
{
	reduce(one);
	if (one.den == 1)
		outs << one.num << " ";
	else if (one.den == 0)
		outs << "Division by Zero not possible";
	else
		outs << one.num << "/" << one.den << " ";
	return outs;
}
int min(rational one)
{
	if (abs(one.getnum()) < abs(one.getden()))
		return abs(one.getnum());
	else
		return abs(one.getden());
}
void reduce(rational &one)
{
	int i;
	for (i = min(one); i > 1; i--)
		if (one.num % i == 0 && one.den % i == 0)
		{
			one.num /= i;
			one.den /= i;
		}
	if (one.den < 0)
		{
			one.num *= -1;
			one.den *= -1;
		}
	if (one.num == 0) one.den = 1;	
}