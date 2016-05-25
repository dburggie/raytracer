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



double Vector::dot(const Vector & v) const {
	return x * v.x + y * v.y + z * v.z;
}



Vector Vector::cross(const Vector & v, const Vector & w) {
	return Vector(
			v.y * w.z - v.z * w.y,
			v.z * w.x - v.x * w.z,
			v.x * w.y - v.y * w.x
		);
}



Vector Vector::cross(const Vector & v) const {
	return Vector(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		);
}



void Vector::copy(const Vector & v) {
	x = v.x; y = v.y; z = v.z;
}



void Vector::copy(double x, double y, double z) {
	this->x = x; this->y = y; this->z = z;
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

void Vector::reflect(const Vector & normal) {
	this->translate(normal, -2.0 * this->dot(normal));
}

//note: ratio is the ratio of the indexes of refraction across the surface
//interface for a vector traveling in the direction of the normal.
//Specifically, it is the incident index divided by the resultant index.
void Vector::refract(const Vector & normal, double index_ratio) {

	double s = this->dot(normal);
	double sign = 1.0;

	if (s < 0) {
		index_ratio = 1.0 / index_ratio;
		sign = -1.0;
	}

	this->translate(normal, -1.0 * s);
	this->scale(index_ratio);

	s = sign * std::sqrt(1.0 - this->dot(*this));
	this->translate(normal, s);
}



