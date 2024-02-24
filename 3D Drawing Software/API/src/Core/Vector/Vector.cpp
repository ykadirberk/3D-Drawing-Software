#include "Vector.h"

namespace dra {
	Vector::Vector()
	{
		pos_x = 0.0f;
		pos_y = 0.0f;
		pos_z = 0.0f;
	}
	Vector::Vector(float v)
	{
		pos_x = v;
		pos_y = v;
		pos_z = v;
	}
	Vector::Vector(float x, float y)
	{
		pos_x = x;
		pos_y = y;
		pos_z = 0.0f;
	}
	Vector::Vector(float x, float y, float z)
	{
		pos_x = x;
		pos_y = y;
		pos_z = z;
	}
	Vector::~Vector()
	{
	}
	float Vector::x()
	{
		return pos_x;
	}
	float Vector::y()
	{
		return pos_y;
	}
	float Vector::z()
	{
		return pos_z;
	}
}
