#ifndef POINT3D_H
#define POINT3D_H

class Vector3D;

class Point3D
{
private:
	double m_x, m_y, m_z;

public:
	Point3D(double x, double y, double z);
	void print();
	void moveByVector(const Vector3D &v);
};
#endif

