#include <iostream>
#include "vector3D.h"

Vector3D::Vector3D(double x = 0.0, double y = 0.0, double z = 0.0)
	: m_x(x), m_y(y), m_z(z){};

void Vector3D::print()
{
	std::cout << "Vector(" << m_x << " , " << m_y << " , " << m_z << ")\n";
}
