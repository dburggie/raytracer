#include <raytracer.h>
#include <bodies.h>

#include <cassert>
#include <cmath>



using namespace raytracer;



void BasicBody::useDefaults() {
	transparent = false;
	index = 1.0;
	reflectivity = 0.0;
	
	matte = false;
	normal_delta = 0.0;
	
	size = 1.0;
	
	position.copy(0.0,0.0,0.0);
	orientation.copy(0.0,1.0,0.0);
	x_axis.copy(1.0,0.0,0.0);
	y_axis.copy(0.0,1.0,0.0);
	z_axis.copy(0.0,0.0,1.0);
	
	interior_color.copy(0.50,0.50,0.50);
	color.copy(interior_color);
}



bool BasicBody::isTransparent() const {
	return transparent;
}



double BasicBody::getIndex(const Vector & p) const {
	return index;
}



Vector BasicBody::getColor(const Vector & p) const {
	return color;
}



Vector BasicBody::getInteriorColor(const Vector & p) const {
	return interior_color;
}



void BasicBody::setReflectivity(double r) {
	assert(0 <= r);
	assert(r < 1.0);

	reflectivity = r;
}



double BasicBody::getReflectivity(const Vector & p) const {
	return reflectivity;
}





void BasicBody::setPosition(const Vector & p) {
	position.copy(p);
}



void BasicBody::setOrientation(const Vector & o) {
	orientation.copy(o);
	orientation.normalize();
}



void BasicBody::setOrientation(
		const Vector & X, const Vector & Y, const Vector & Z ) {
	x_axis.copy(X);
	y_axis.copy(Y);
	z_axis.copy(Z);
}



void BasicBody::setSize(double S) {
	assert(S > DIV_LIMIT);

	size = S;
}



void BasicBody::setColor(const Vector & c) {
	assert(0.0 <= c.x);
	assert(0.0 <= c.y);
	assert(0.0 <= c.z);
	assert(c.x < 1.0);
	assert(c.y < 1.0);
	assert(c.z < 1.0);

	color.copy(c);
	interior_color.copy(c);
}



void BasicBody::setInteriorColor(const Vector & c) {
	assert(0.0 <= c.x);
	assert(0.0 <= c.y);
	assert(0.0 <= c.z);
	assert(c.x < 1.0);
	assert(c.y < 1.0);
	assert(c.z < 1.0);

	interior_color.copy(c);
}


void BasicBody::refractionOff() {
	refracting = false;
}

void BasicBody::refractionOn()



void BasicBody::setIndex(double n) {
	assert(1.0 <= n);
	
	index = n;
	reflectivity = (index - 1.0) / (index);
	reflectivity = reflectivity * reflectivity;
	
	assert(0.0 <= reflectivity);
	assert(reflectivity < 1.0);
}



void BasicBody::matteOn(double delta) {
	assert(0.0 <= delta);
	assert(delta < 1.0);
	
	matte = true;
	normal_delta = delta;
}

void BasicBody::matteOff() {
	matte = false;
}


