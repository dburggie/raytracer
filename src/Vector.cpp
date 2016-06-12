#include <raytracer.h>

#include <cassert>
#include <cmath>

using namespace raytracer;



static const double PI  = 4.0 * atan(1.0);
static const double TAU = 2.0 * PI;

Vector::Vector() {
	x = 0.0; y = 1.0; z = 0.0;
}



Vector::Vector(double x, double y, double z) {
	this->x = x; this->y = y; this->z = z;
}



Vector::Vector(const Vector & v) {
	x = v.x; y = v.y; z = v.z;
}


void Vector::seed() {
	std::srand(std::time(NULL));
}


Vector Vector::random(double r) {

	r *= std::rand();

	double t = TAU * std::rand(),
		   p = PI * std::rand(),
		   rcosp = r * std::sin(p);

	return Vector(
			rcosp * std::cos(t),
			rcosp * std::sin(t),
			r * std::sin(p)
		);
}



double Vector::dot(const Vector & v, const Vector & w) {
	return v.x * w.x + v.y * w.y + v.z * w.z;
}



double Vector::dot() const {
	return x * x + y * y + z * z;
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



void Vector::power(double p) {
	x = std::pow(x,p);
	y = std::pow(y,p);
	z = std::pow(z,p);
}



void Vector::normalize() {
	double l = std::sqrt(x * x + y * y + z * z);
	
	assert(l >= DIV_LIMIT);

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



void Vector::scale(const Vector & v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
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

	assert(std::abs(dot() - 1.0) < DIV_LIMIT); // should be a direction vector

	translate(normal, -2.0 * dot(normal));
}



//note: ratio is the ratio of the indexes of refraction across the surface
//interface for a vector traveling in the direction of the normal.
//Specifically, it is the incident index divided by the resultant index.
void Vector::refract(const Vector & normal, double index_ratio) {

	assert(std::abs(dot() - 1.0) < DIV_LIMIT); // should be a direction vector

	double s = dot(normal);
	double sign = 1.0;

	if (s < 0) {
		index_ratio = 1.0 / index_ratio;
		sign = -1.0;
	}

	translate(normal, -1.0 * s);
	scale(index_ratio);

	s = sign * std::sqrt(1.0 - dot());
	translate(normal, s);
}



void Vector::project(const Vector & v) {
	double l = dot(v);
	copy(v); scale(l);
}



void Vector::unproject(const Vector & v) {
	Vector p = v;
	p.scale(dot(v));
	subtract(p);
}




