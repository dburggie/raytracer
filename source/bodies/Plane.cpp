
#include <raytracer.h>
#include <bodies.h>

#include <cassert>
#include <cmath>

using namespace raytracer;



Plane::Plane() {
	setPosition(Vector(0.0,0.0,0.0));
	setOrientation(
			Vector(1.0,0.0,0.0),
			Vector(0.0,1.0,0.0),
			Vector(0.0,0.0,1.0)
		);
	setColor(Vector(0.5,0.5,0.5));
}


Plane::Plane(const Vector & position, const Vector & normal) {
	setPosition(position);
	y_axis.copy(normal);
}



Body* Plane::clone() const {
	return (Body*) new Plane(*this);
}



Vector Plane::getNormal(const Vector & p) const {
	return y_axis;
}



double Plane::getDistance(const Ray & r) const {

	double speed;
	Vector p = position; 

	p.subtract(r.p);
	p.project(y_axis);

	speed = p.dot(r.v);

	if (speed < DIV_LIMIT) {
		return -1.0;
	}

	return p.dot() / speed;
}






