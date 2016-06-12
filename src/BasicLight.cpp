#include <raytracer.h>

#include <cmath>
#include <cassert>

using namespace raytracer;



BasicLight::BasicLight() {
	direction.copy(0.0, 1.0, 0.0);
	color.copy(0.999, 0.999, 0.999);
	intensity.copy(1.0, 1.0, 1.0);

	hasPenumbra = false;
	penumbra = 0.0;
}



void BasicLight::setDirection(const Vector & p) {
	assert(p.dot() > DIV_LIMIT);

	direction.copy(p);
	direction.normalize();
}


void BasicLight::setPenumbralSize(double d) {
	assert(d > DIV_LIMIT);

	hasPenumbra = true;
	penumbra = d;
}



void BasicLight::setColor(const Vector & c) {
	assert(c.x >= 0.0);
	assert(c.y >= 0.0);
	assert(c.z >= 0.0);
	assert(c.x <= 1.0);
	assert(c.y <= 1.0);
	assert(c.z <= 1.0);

	color.copy(c);
}



void BasicLight::setIntensity(const Vector & p) {
	assert(p.x >= 0.0);
	assert(p.y >= 0.0);
	assert(p.z >= 0.0);
	assert(p.x <= 1.0);
	assert(p.y <= 1.0);
	assert(p.z <= 1.0);

	intensity.copy(p);
}



Vector BasicLight::getDirection(const Vector & p) const {
	Vector v = direction;

	if (hasPenumbra) {
		v.add(Vector::random(penumbra));
		v.normalize();
	}

	return v;
}



Vector BasicLight::getColor() const {
	return color;
}



Vector BasicLight::getIntensity(const Vector & p) const {
	return intensity;
}


