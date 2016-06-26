#include <raytracer.h>
#include <bodies.h>

#include <cmath>
#include <cassert>

using namespace raytracer;



Cylinder::Cylinder() {
	setSize(1.0);
	setOrientation(Vector(0.0,1.0,0.0));
	setPosition(Vector(0.0,0.0,0.0));
}



Cylinder::Cylinder(const Vector & p, const Vector & v, double radius) {
	setSize(radius);
	setOrientation(v);
	setPosition(p);
}



Body * Cylinder::clone() const {
	return (Body*) new Cylinder(*this);
}



void Cylinder::setSize(double radius) {
	assert(radius > DIV_LIMIT);

	size = radius;
	magnitude = radius * radius;
	reciprocal = 1 / radius;
}



//Cylinder uses the z_axis orientation vector from BasicBody as its axis
void Cylinder::setOrientation(const Vector & v) {
	x_axis.copy(1.0,0.0,0.0);
	y_axis.copy(0.0,1.0,0.0);
	z_axis.copy(v);
}



double Cylinder::getDistance(const Ray  & r) const {
	//magnitude is radius squared
	//position and direction are vectors defining position/orientation
	Vector v = r.p, w = r.v;
	v.subtract(position);
	v = v.cross(z_axis);
	w = w.cross(z_axis);
	double vv = v.dot(), vw = v.dot(w), ww = w.dot();
	double radical = vw*vw + ww / magnitude - vv*ww;
	
	if (radical < DIV_LIMIT) return -1.0;
	else radical = std::sqrt(radical) / ww;

	double distance = -vw / ww - radical;
	if (distance < DIV_LIMIT) {
		distance = -vw / ww + radical;
		if (distance < DIV_LIMIT) {
			return -1.0;
		}
		else return distance;
	}

	else return distance;
}



Vector Cylinder::getNormal(const Vector & p) const {
	Vector result = p, projection = z_axis;
	projection.scale(projection.dot(p));
	result.subtract(projection);
	result.scale(reciprocal);
	return result;
}
