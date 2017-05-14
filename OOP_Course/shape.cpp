#include "shape.h"
int Shape::next_id = 0;
Shape::Shape()
{
	this->id = this->next_id;
	this->next_id++;
}