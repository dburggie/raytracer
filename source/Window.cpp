
#include <raytracer.h>

#include <cmath>
#include <cassert>

using namespace raytracer;



Window::Window() {
	initialized = false;
	rng = RNG::get();
	center.copy(0.0,0.0,0.0);
	up.copy(0.0,1.0,0.0);
	down.copy(0.0,-1.0,0.0);
	right.copy(1.0,0.0,0.0);
	left.copy(-1.0,0.0,0.0);
	origin.copy(0.0,0.0,0.0);
	width = 0.0; height = 0.0; pixel_size = 0.0; pixels_per_unit = 0.0;
	x_count = 0;
	y_count = 0;
}



void Window::setFocus(const Vector & p) {
	center.copy(p);
}



void Window::setOrientation(const Vector & right, const Vector & up) {
	assert(std::abs(right.dot(up)) < DIV_LIMIT);

	this->right.copy(right);
	this->right.normalize();
	
	left.copy(this->right);
	left.scale(-1.0);

	this->up.copy(up);
	this->up.normalize();

	down.copy(this->up);
	down.scale(-1.0);
}



void Window::setSize(double width, double height) {
	this->width = width;
	this->height = height;
}



void Window::setResolution(int vertical_pixel_count) {
	y_count = vertical_pixel_count;
}



void Window::init() {
	assert(width > DIV_LIMIT);
	assert(height > DIV_LIMIT);
	assert(y_count > 0);
	assert(std::abs(right.dot(down)) < DIV_LIMIT);

	origin = center;
	origin.translate(up, height / 2.0);
	origin.translate(left, width / 2.0);

	pixel_size = height / y_count;
	pixels_per_unit = 1.0 / pixel_size;
	x_count = (int) (width * pixels_per_unit);
	initialized = true;
}



int Window::getWidth() const {
	assert(initialized);
	return x_count;
}



int Window::getHeight() const {
	assert(initialized);
	return y_count;
}



Vector Window::getPixel(int x, int y) const {

	assert(initialized);

	//assert pixel is in window
	assert(x >= 0);
	assert(y >= 0);
	assert(x < x_count);
	assert(y < y_count);

	// get a random position within the pixel
	double dx = pixel_size * (x + rng->next()), 
		   dy = pixel_size * (y + rng->next());

	// calculate vector
	Vector v = origin;
	v.translate(right,dx);
	v.translate(down,dy);

	return v;
}



