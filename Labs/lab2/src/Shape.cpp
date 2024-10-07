#include "Shape.h"

Shape::Shape(float x, float y, float z) : cord_x(x), cord_y(y), cord_z(z) {}

void Shape::set_cord(float new_x, float new_y, float new_z)
{
	cord_x = new_x;
	cord_y = new_y;
	cord_z = new_z;
}