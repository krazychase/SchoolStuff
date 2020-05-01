#pragma once
class rational
{
	friend rational operator+ (rational one, rational two);
	friend rational operator- (rational one, rational two);
	friend rational operator* (rational one, rational two);
	friend rational operator/ (rational one, rational two);
	friend istream& operator>>(istream& ins, rational& one);
	friend ostream& operator<<(ostream& outs, rational one);
	friend void reduce(rational &one);
private:
	int num, den;
public:
	rational();
	rational(int num, int den);
	int getnum();
	int getden();
	void setnum(int num);
	void setden(int den);
	void print(ofstream &outf);
};
rational operator+ (rational one, rational two);
rational operator- (rational one, rational two);
rational operator* (rational one, rational two);
rational operator/ (rational one, rational two);
istream& operator>>(istream& ins, rational& one);
ostream& operator<<(ostream& outs, rational one);
void reduce(rational &one);