#include <raytracer.h>
#include <bodies.h>

#include <cmath>
#include <cassert>

using namespace raytracer;



Cylinder::Cylinder() {
	useDefaults();
}



Body * Cylinder::clone() const {
	return (Body*) new Cylinder(*this);
}



double Cylinder::getDistance(const Ray  & r) const {
	//magnitude is radius squared
	//position and direction are vectors defining position/orientation
	Vector v = r.p, w = r.v;
	v.subtract(position);
	v.cross(orientation);
	w.cross(orientation);
	double vv = v.dot(), vw = v.dot(w), ww = w.dot();
	double radical = vw*vw + ww / magnitude - vv*ww;
	
	if (radical < ZERO) return -1.0;
	else radical = std::sqrt(radical) / ww;

	double distance = -vw / ww - radical;
	if (distance < ZERO) {
		distance = -vw / ww + radical;
		if (distance < ZERO) {
			return -1.0;
		}
		else return distance;
	}

	else return distance;
}



Vector Cylinder::getNormal(const Vector & p) const {
	Vector result = p, projection = orientation;
	projection.dot(p);
	result.subtract(projection);
	result.scale(reciprocal);
	
	if (matte) {
		result.add(Vector::random(normal_delta));
		result.normalize();
	}
	
	assert(std::abs(result.dot() - 1.0) < ZERO);
	
	return result;
}


