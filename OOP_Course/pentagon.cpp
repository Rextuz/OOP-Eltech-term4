#include "pentagon.h"
#include <iostream>
using std::cout;
using std::endl;
#include <math.h>
Pentagon::Pentagon(double* new_x, double* new_y)
{
	for (int i = 0; i < 6; i++)
	{
		this->x[i] = new_x[i];
		this->y[i] = new_y[i];
	}
	cout << "Created a Pentagon with ID =" << this->id << endl;
}
Pentagon::~Pentagon()
{
	cout << "Deleted a Pentagon with ID =" << this->id << endl;
}
void Pentagon::turn(double angle)
{
	for (int i = 0; i < 6; i++)
	{
		double new_x = this->x[i] * cos(angle) - this->y[i] * sin(angle);
		double new_y = this->x[i] * sin(angle) + this->y[i] * cos(angle);
		this->x[i] = new_x;
		this->y[i] = new_y;
	}
	cout << "a Pentagon with ID =" << this->id << "rotated angle" << (int)((180
		* angle) / 3.141592653) << "degrees" << endl;
}
void Pentagon::move(double new_x, double new_y)
{
	double delta_x = abs(new_x - this->x[0]);
	double delta_y = abs(new_y - this->y[0]);
	for (int i = 0; i < 5; i++)
	{
		this->x[i] += delta_x;
		this->y[i] += delta_y;
	}
	cout << "a Pentagon with ID =" << this->id << " is moved to coordinates (" <<
		new_x << ", " << new_y << ")" << endl;
}
void Pentagon::draw()
{
	cout << "Drawn Pentagon with center (" << this->x[0] << ", " << this->y[0]
		<< ") and coordinates" << endl;
	cout << " [ ";
	for (int i = 1; i < 6; i++)
	{
		cout << "(" << this->x[i] << ", " << this->y[i] << ") ";
	}
	cout << "]" << endl;
}