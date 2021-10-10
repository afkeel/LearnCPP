#ifndef VECTOR3D_H
#define VECTOR3D_H
#include "point3D.h"

class Vector3D
{
private:
	double m_x, m_y, m_z;

public:
	Vector3D(double x, double y, double z);
	void print();	
	friend void Point3D::moveByVector(const Vector3D &v);
};
#endif

