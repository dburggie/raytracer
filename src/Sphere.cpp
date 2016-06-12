
#include <raytracer.h>
#include <bodies.h>

#include <cassert>
#include <cmath>

using namespace raytracer;



Sphere::Sphere(double radius) {
	setSize(radius);
}



void Sphere::setSize(double radius) {
	assert(radius > DIV_LIMIT);
	size = radius;
	magnitude = radius * radius;
	reciprocal = 1.0 / radius;
}



Vector Sphere::getNormal(const Vector & p) const {
	Vector v = p;
	v.subtract(position);
	v.scale(reciprocal);
	assert(std::abs(v.dot() - 1.0) < DIV_LIMIT);
	return v;
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
	assert(std::abs(r.v.dot() - 1.0) < DIV_LIMIT);
	Vector v = position;
	v.subtract(r.p);

	double angle = r.v.dot(v), //DV
		   distance = v.dot(), //VV
		   radical = angle * angle + magnitude - distance; //DV*DV+RR-VV

	if (radical < DIV_LIMIT) {
		return -1.0;
	}

	else {
		radical = std::sqrt(radical);
	}

	distance = angle - radical; //DV-sqrt(DV*DV+RR-VV)

	if (distance < DIV_LIMIT) {
		distance = angle + radical; //DV+sqrt(DV*DV+RR-VV)
		if (distance < DIV_LIMIT) {
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


























