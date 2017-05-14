#pragma once
#include <iostream>
class Shape
{
private:
	static int next_id;
protected:
	int id;
public:
	Shape();
	virtual void move(double new_x, double new_y) = 0;
	virtual void turn(double angle) = 0;
	virtual void draw() = 0;
};