#include "circle.h"
#include <iostream>
using std::cout;
using std::endl;
Circle::Circle(double new_x, double new_y, double new_r)
{
	this->x = new_x;
	this->y = new_y;
	this->r = new_r;
	cout << "circle Created with ID =" << this->id << endl;
}
Circle::~Circle()
{
	cout << "circle Removed, ID =" << this->id << endl;
}
void Circle::turn(double angle)
{
	cout << "Circle with ID =" << this->id << "rotated angle" << (int)((180 *
		angle) / 3.141592653) << "degrees" << endl;
}
void Circle::move(double new_x, double new_y)
{
	this->x = new_x;
	this->y = new_y;
	cout << "Circle with ID =" << this->id << " is moved to coordinates (" <<
		new_x << ", " << new_y << ")" << endl;
}
void Circle::draw()
{
	cout << "Drawn the circle with coordinates (" << this->x << ", " << this->y <<
		") and radius " << this->r << endl;
}

double * Circle::getXY()
{
	double * res = new double[2];
	res[0] = x;
	res[1] = y;
	return res;
}
