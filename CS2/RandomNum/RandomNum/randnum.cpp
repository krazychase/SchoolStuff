//Chase Brown
//Random Number Generator

#define _USE_MATH_DEFINES
#include<iomanip>
#include<fstream>
#include<math.h>
#include<time.h>
using namespace std;

const int maxnum = 25000;
const double bound = 100000.0;

void main()
{
	ofstream outf("data.ot");
	outf.precision(3);
	outf.setf(ios::fixed);
	int i = 0;
	double num;
	srand(time(NULL));
	while (i < maxnum)
	{
		num = rand();
		num *= (cos(i % 10) * M_PI);
		if (abs(num) < bound)
		{
			outf << setw(14) << num << endl;
			i++;
		}
	}
}