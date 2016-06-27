
#include <raytracer.h>
#include <bodies.h>

#include <cassert>
#include <cmath>

using namespace raytracer;



Sphere::Sphere() {
	useDefaults();
	inverted = false;
}



Body * Sphere::clone() const {
	return (Body*) new Sphere(*this);
}



void Sphere::setSize(double radius) {
	assert(ZERO < radius);
	
	size = radius;
	magnitude = radius * radius;
	reciprocal = 1.0 / radius;
}



Vector Sphere::getNormal(const Vector & p) const {
	Vector v;
	
	if (inverted) {
		v.copy(position);
		v.subtract(p);
	}
	
	else {
		v.copy(p);
		v.subtract(position);
	}
	
	v.scale(reciprocal);
	
	if (matte) {
		v.add(Vector::random(normal_delta));
		v.normalize();
	}
	
	assert(std::abs(v.dot() - 1.0) < ZERO);
	return v;
}


bool Sphere::invert() {
	inverted = !inverted;
	return inverted;
}



bool Sphere::isInterior(const Ray & incident_ray) const {

	//calculate normal vector
	Vector n;

	if (inverted) {
		n.copy(position);
		n.subtract(incident_ray.p);
	}

	else {
		n.copy(incident_ray.p);
		n.subtract(position);
	}

	if (incident_ray.v.dot(n) > ZERO)
		return true;
	else
		return false;
}



double Sphere::getDistance(const Ray & r) const {
/*
 * R = O+tD
 * R, a ray, is an origin vector plus a multiple of a direction vector
 *
 *
 * S = { v | len(v-P) = R for R scalar, P vector }
 * S, a sphere, is the points distance r from a position vector
 *
 * R intersects S when:
 * (R - P) dot (R - P) = R*R
 *
 * let's pretend our sphere is at the origin (translate ray by sphere position)
 * V = O - P
 *
 * perform the dot product above
 * VV - 2tDV + t*tDD - r*r = 0
 *
 * simplify, grouping by t terms. you get a quadratic equation
 * (DD) t^2 + (-2DV) t + (VV-rr) = 0
 *
 * solve for t usng the quadratic formula
 * t = (2DV +/- sqrt(4DV*DV - 4 DD(VV-rr))) / (2DD)
 * t = (DV +/- sqrt(DV*DV - DD*VV + DD*RR)) / DD
 *
 * remember, D is a direction, thus has length one
 * (DD = 1)
 * t = (DV +/- sqrt(DV*DV + RR - VV)
 */
	assert(std::abs(r.v.dot() - 1.0) < ZERO);
	Vector v = position;
	v.subtract(r.p);

	double angle = r.v.dot(v), //DV
		   distance = v.dot(), //VV
		   radical = angle * angle + magnitude - distance; //DV*DV+RR-VV

	if (radical < ZERO) {
		return -1.0;
	}

	else {
		radical = std::sqrt(radical);
	}

	distance = angle - radical; //DV-sqrt(DV*DV+RR-VV)

	if (distance < ZERO) {
		distance = angle + radical; //DV+sqrt(DV*DV+RR-VV)
		if (distance < ZERO) {
			return -1.0;
		}

		else {
			return distance;
		}
	}

	else {
		return distance;
	}
}


























