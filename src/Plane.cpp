
#include <raytracer.h>
#include <bodies.h>

#include <cassert>
#include <cmath>

using namespace raytracer;



Plane::Plane(const Vector & position, const Vector & normal) {
	setPosition(position);
	z_axis = normal;
}



Body* Plane::clone() const {
	return (Body*) new Plane(*this);
}



Vector Plane::getNormal(const Vector & p) const {
	return z_axis;
}



double Plane::getDistance(const Ray & r) const {

	Vector p = r.p; p.subtract(position);
	double speed = z_axis.dot(r.v), distance;

	if (speed < DIV_LIMIT) {
		return -1.0;
	}

	distance = p.dot() / speed;

	if (distance < DIV_LIMIT) {
		return -1.0;
	}

	else {
		return distance;
	}

}






