#include <raytracer.h>
#include <cassert>
#include <cmath>

using namespace raytracer;



BasicBody::BasicBody() {
	refracting = false;
	index_ratio = 0.01;
	size = 1.0;
	position.copy(0.0,0.0,0.0);
	x_axis.copy(1.0,0.0,0.0);
	y_axis.copy(0.0,1.0,0.0);
	z_axis.copy(0.0,0.0,1.0);
	color.copy(0.50,0.50,0.50);
}



bool BasicBody::isRefracting() const {
	return refracting;
}



double BasicBody::getRefractiveRatio(const Vector & p) const {
	return index_ratio;
}



Vector BasicBody::getColor(const Vector & p) const {
	return color;
}



Vector BasicBody::getExteriorColor(const Vector & p) const {
	return exterior_color;
}



void BasicBody::setReflectivity(double index) {
	assert(index > DIV_LIMIT);

	reflectivity = std::pow((index - 1.0) / (index), 2.0);
}



double BasicBody::getReflectivity(const Vector & p) const {
	return reflectivity;
}





void BasicBody::setPosition(const Vector & p) {
	position.copy(p);
}



void BasicBody::setOrientation(
		const Vector & X, const Vector & Y, const Vector & Z ) {
	x_axis.copy(X);
	y_axis.copy(Y);
	z_axis.copy(Z);

	x_axis.normalize();
	y_axis.normalize();
	z_axis.normalize();
}



void BasicBody::setSize(double S) {
	assert(S > DIV_LIMIT);

	size = S;
}



void BasicBody::setColor(const Vector & c) {
	assert(c.x > 0);
	assert(c.y > 0);
	assert(c.z > 0);
	assert(c.x < 1);
	assert(c.y < 1);
	assert(c.z < 1);

	color.copy(c);
}



void BasicBody::setExteriorColor(const Vector & c) {
	assert(c.x > 0);
	assert(c.y > 0);
	assert(c.z > 0);
	assert(c.x < 1);
	assert(c.y < 1);
	assert(c.z < 1);

	exterior_color.copy(c);
}


void BasicBody::refractionOff() {
	refracting = false;
	index_ratio = 0.01;
}



void BasicBody::setRefraction(double index) {
	setReflectivity(index);
	index_ratio = index;
}





