#pragma once
#include "shape.h"
class Circle : public Shape
{
private:
	double x;
	double y;
	double r;
public:
	Circle(double new_x, double new_y, double new_r);
	~Circle();
	void turn(double angle);
	void move(double new_x, double new_y);
	void draw();
};