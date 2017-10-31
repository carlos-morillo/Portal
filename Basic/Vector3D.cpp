#include "Vector3D.h"
#include <math.h>

Vector3D::~Vector3D(void)
{}

float Vector3D::modulo(void)
{
	return (sqrt(x*x+y*y+z*z));
}

Vector3D Vector3D::unitario(void)
{
	return Vector3D(x/this->modulo(),y/this->modulo(),z/this->modulo());
}