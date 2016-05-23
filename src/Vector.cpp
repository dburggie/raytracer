#include <raytracer.h>
#include <cmath>



using namespace raytracer;



Vector::Vector() {
	x = 0.0; y = 1.0; z = 0.0;
}



Vector::Vector(double x, double y, double z) {
	this->x = x; this->y = y; this->z = z;
}



Vector::Vector(const Vector & v) {
	x = v.x; y = v.y; z = v.z;
}



double Vector::dot(const Vector & v, const Vector & w) {
	return v.x * w.x + v.y * w.y + v.z * w.z;
}



Vector Vector::cross(const Vector & v, const Vector & w) {
	return Vector(
			v.y * w.z - v.z * w.y,
			v.z * w.x - v.x * w.z,
			v.x * w.y - v.y * w.x
		);
}



void Vector::copy(const Vector & v) {
	x = v.x; y = v.y; z = v.z;
}



void Vector::normalize() {
	double l = std::sqrt(x * x + y * y + z * z);
	
	// don't divide by what is essentially zero
	if (l < DIV_LIMIT) {
		x = 0.0;
		y = 1.0;
		z = 0.0;
	}

	else {
		x /= l;
		y /= l;
		z /= l;
	}
}



void Vector::scale(double s) {
	x *= s; y *= s; z *= s;
}



void Vector::add(const Vector & v) {
	x += v.x; y += v.y; z += v.z;
}



void Vector::add(double x, double y, double z) {
	this->x += x; this->y += y; this->z += z;
}



void Vector::subtract(const Vector & v) {
	x -= v.x; y -= v.y; z -= v.z;
}



void Vector::subtract(double x, double y, double z) {
	this->x -= x; this->y -= y; this->z -= z;
}



void Vector::translate(const Vector & v, double s) {
	x += s * v.x; y += s * v.y; z += s * v.z;
}



