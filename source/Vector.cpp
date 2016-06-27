#include <raytracer.h>

#include <cassert>
#include <cmath>

using namespace raytracer;



static const double PI  = 4.0 * std::atan(1.0);
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



Vector Vector::random(double r) {

	RNG *rng = RNG::get();
	r *= rng->next();

	double t = TAU * rng->next(),
		   p = PI * rng->next(),
		   rsinp = r * std::sin(p);

	return Vector(
			rsinp * std::cos(t),
			rsinp * std::sin(t),
			r * std::cos(p)
		);
}



Vector Vector::randunit() {
	
	RNG *rng = RNG::get();

	double t = TAU * rng->next(),
		   p = PI * rng->next(),
		   sinp = std::sin(p);

	return Vector(
			sinp * std::cos(t),
			sinp * std::sin(t),
			std::cos(p)
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
	
	assert(l >= ZERO);

	// don't divide by what is essentially zero
	if (l < ZERO) {
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

	assert(std::abs(dot() - 1.0) < ZERO); // should be a direction vector

	translate(normal, -2.0 * dot(normal));
}



//note: ratio is the ratio of the indexes of refraction across the surface
//interface for a vector traveling in the direction of the normal.
//Specifically, it is the incident index divided by the resultant index.
void Vector::refract(const Vector & normal, double index_ratio) {
	//should be working with unit vectors
	assert(std::abs(dot() - 1.0) < ZERO);
	assert(std::abs(normal.dot() - 1.0) < ZERO);

	double s = dot(normal);
	double sign = 1.0;

	//check for internal refraction
	if (s > 0.0 && index_ratio * std::sqrt(cross(normal).dot()) > 1.0) {
		reflect(normal);
		return;
	}

	//flip ratio if we're heading into surface instead of out
	if (s < 0) {
		index_ratio = 1.0 / index_ratio;
		sign = -1.0;
	}

	unproject(normal);
	scale(index_ratio);

	s = sign * std::sqrt(1.0 - dot());
	translate(normal, s);
}



void Vector::project(const Vector & v) {
	assert(std::abs(v.dot() - 1.0) < ZERO);
	double l = dot(v);
	copy(v); scale(l);
}



void Vector::unproject(const Vector & v) {
	assert(std::abs(v.dot() - 1.0) < ZERO);
	Vector p = v;
	p.scale(dot(v));
	subtract(p);
}




