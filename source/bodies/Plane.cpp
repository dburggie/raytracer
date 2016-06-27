
#include <raytracer.h>
#include <bodies.h>

#include <cassert>
#include <cmath>

using namespace raytracer;



Plane::Plane() {
	useDefaults();
}



Body* Plane::clone() const {
	return (Body*) new Plane(*this);
}



void Plane::setNormal(const Vector & n) {
	orientation.copy(n);
	orientation.normalize();
}



Vector Plane::getNormal(const Vector & p) const {
	
	if (matte) {
		Vector result = orientation;
		result.add(Vector::random(normal_delta));
		result.normalize();
		return result;
	}
	
	return orientation;
}



double Plane::getDistance(const Ray & r) const {

	double speed;
	Vector p = position; 

	p.subtract(r.p);
	p.project(orientation);

	speed = p.dot(r.v);

	if (speed < ZERO) {
		return -1.0;
	}

	return p.dot() / speed;
}



bool Plane::isInterior(const Ray & incident_ray) const {
	return (incident_ray.v.dot(orientation) > 0.0) ? true : false;
}





