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
	
	Vector p = r.p, v = r.v;
	p.subtract(position);
	p.unproject(orientation);
	v.unproject(orientation);

	assert(std::abs(p.dot(orientation)) < ZERO);
	assert(std::abs(v.dot(orientation)) < ZERO);
	
	double PP = p.dot(p) - magnitude,
		   PV = p.dot(v),
		   VV = v.dot(v);
	
	double radical = PV*PV - PP*VV;
	
	if (radical < ZERO) {
		return -1.0;
	}

	radical = std::sqrt(radical);

	double distance = (-1.0 * PV - radical) / VV;

	if (distance < ZERO) {
		
		distance = (-1.0 * PV + radical) / VV;
		
		if (distance < ZERO) {
			return -1.0;
		}
	}

	return distance;
}



Vector Cylinder::getNormal(const Vector & p) const {
	
	Vector result;

	if (inverted) {
		result.copy(position);
		result.subtract(p);
	}

	else {
		result.copy(p);
		result.subtract(position);
	}

	result.unproject(orientation);
	result.scale(reciprocal);
	
	assert(std::abs(result.dot() - 1.0) < ZERO);
	assert(std::abs(result.dot(orientation)) < ZERO);

	if (matte) {
		result.add(Vector::random(normal_delta));
		result.normalize();
	}
	
	return result;
}



bool Cylinder::isInterior(const Ray & incident_ray) const {
	//get normal vector
	Vector n = incident_ray.p;
	n.subtract(position);
	if (inverted) n.scale(-1.0);
	n.unproject(orientation);
	n.scale(reciprocal);
	
	if (n.dot(incident_ray.v) > ZERO) return true;
	else return false;
}



