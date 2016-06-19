
#include <raytracer.h>

#include <cmath>
#include <cassert>

using namespace raytracer;



Camera::Camera() {
	position.copy(0.0, 0.0, 0.0);
	hasBlur = false;
	blur = 0.0;
}



Camera::Camera(const Vector & position) {
	this->position.copy(position);
	hasBlur = false;
	blur = 0.0;
}



Camera::Camera(const Vector & position, const Vector & focus) {
	this->position.copy(position);
	setFocus(focus);
	hasBlur = false;
	blur = 0.0;
}



void Camera::setPosition(const Vector & p) {
	position.copy(p);
}



void Camera::setBlur(double b) {
	assert(b > DIV_LIMIT);

	hasBlur = true;
	blur = b;
}



Ray Camera::getRay(int x, int y) const {
	Ray ray = Ray(position,getPixel(x,y));

	if (hasBlur) {
		ray.p.add(Vector::random(blur));
	}

	ray.v.subtract(ray.p);
	ray.v.normalize();

	return ray;
}



