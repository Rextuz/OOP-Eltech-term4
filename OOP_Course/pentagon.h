#pragma once
#include "shape.h"
class Pentagon :public Shape
{
private:
	double x[6];
	double y[6];
public:
	Pentagon(double new_x[], double new_y[]);
	~Pentagon();
	void turn(double angle);
	void move(double new_x, double new_y);
	void draw();
};