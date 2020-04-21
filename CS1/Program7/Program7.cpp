//Program 7
//Chase Brown
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
class BoxClass
{
public:
	BoxClass();
	BoxClass(double l, double w, double h);
	void printem(ofstream &outf);
	double getl();
	double getw();
	double geth();
	void setl(double l);
	void setw(double w);
	void seth(double h);
	double getvolin(double l, double w, double h);
	double getvolft(double l, double w, double h);
	double getareain(double l, double w, double h);
	double getareaft(double l, double w, double h);
private:
	double length, width, height;
};
void main()
{
	//Step 1: Create 2 boxs and print dimensions of each 
	BoxClass box1;
	BoxClass box2(5.0, 7.5, 3.625);
	ofstream outf("Program7.ot");
	outf << "Step 1: Create 2 boxs and print dimensions of each" << endl 
		<< "Box 1" << endl;
	box1.printem(outf);
	outf << "Box 2" << endl;
	box2.printem(outf);

	//Step 2: Set Dimensions of box 1
	box1.setw(14.6);
	box1.setl(16.125);
	box1.seth(10.0);
	outf << "Step 2: Set Dimensions of box 1" << endl << "New Box 1" << endl;
	box1.printem(outf);

	//Step 3: Get Volume in cubic inches
	outf << "Step 3: Get Volume in cubic inches" << endl << "Box 1 volume = " 
		<< box1.getvolin(box1.getl(), box1.getw(), box1.geth()) 
		<< " cubic inches" << endl << "Box 2 volume = " 
		<< box2.getvolin(box2.getl(), box2.getw(), box2.geth()) 
		<< " cubic inches" << endl << endl;

	//Step 4: Get volume in cubic feet
	outf << "Step 4: Get volume in cubic feet" << endl << "Box 1 volume = "
		<< box1.getvolft(box1.getl(), box1.getw(), box1.geth())
		<< " cubic feet" << endl << "Box 2 volume = "
		<< box2.getvolft(box2.getl(), box2.getw(), box2.geth())
		<< " cubic feet" << endl << endl;

	//Step 5: Get surface area in square inches
	outf << "Step 5: Get surface area in square inches" << endl
		<< "Box 1 surface area = "
		<< box1.getareain(box1.getl(), box1.getw(), box1.geth())
		<< " square inches" << endl << "Box 2 surface area = "
		<< box2.getareain(box2.getl(), box2.getw(), box2.geth())
		<< " square feet" << endl << endl;

	//Step 6: Get surface area in square feet
	outf << "Step 6: Get surface area in square feet" << endl
		<< "Box 1 surface area = "
		<< box1.getareaft(box1.getl(), box1.getw(), box1.geth())
		<< " square feet" << endl << "Box 2 surface area = "
		<< box2.getareaft(box2.getl(), box2.getw(), box2.geth())
		<< " square feet" << endl << endl;

	//Step 7: Determine total surface area of boxs
	double totarea;
	totarea = box1.getareaft(box1.getl(), box1.getw(), box1.geth())
		+ box2.getareaft(box2.getl(), box2.getw(), box2.geth());
	outf << "Step 7: Determine total surface area of boxs for wrapping paper" 
		<< endl << "Total wrapping paper needed = " << totarea 
		<< " square feet" << endl << endl;

	//Step 8: Determine total volume of boxs
	double totvol;
	totvol = box1.getvolft(box1.getl(), box1.getw(), box1.geth())
		+ box2.getvolft(box2.getl(), box2.getw(), box2.geth());
	outf << "Step 8: Determine total volume of boxs for filling with soil"
		<< endl << "Total amount of soil needed = " << totvol
		<< " cubic feet" << endl << endl; 
}
BoxClass::BoxClass()
{
	length = 0;
	width = 0;
	height = 0;
}
BoxClass::BoxClass(double l, double w, double h)
{
	length = l;
	width = w;
	height = h;
}
void BoxClass::printem(ofstream &outf)
{
	outf << "The Object has the following dimensions: " << endl << "Length = " 
		<< length << " inches" << endl << "Width = " << width << " inches" 
		<< endl << "Height = " << height << " inches" << endl << endl;
}
double BoxClass::getl()
{
	return length;
}
double BoxClass::getw()
{
	return width;
}
double BoxClass::geth()
{
	return height;
}
void BoxClass::setl(double l)
{
	length = l;
}
void BoxClass::setw(double w)
{
	width = w;
}
void BoxClass::seth(double h)
{
	height = h;
}
double BoxClass::getvolin(double l, double w, double h)
{
	double volume;
	volume = l * w * h;
	return volume;
}
double BoxClass::getvolft(double l, double w, double h)
{
	double volume;
	volume = l * w * h / 12.0;
	return volume;
}
double BoxClass::getareain(double l, double w, double h)
{
	double area;
	area = 2.0*(h * w) + 2.0*(h * l) + 2.0*(w * l);
	return area;
}
double BoxClass::getareaft(double l, double w, double h)
{
	double area;
	area = 2.0*(h * w) + 2.0*(h * l) + 2.0*(w * l) / 12.0;
	return area;
}