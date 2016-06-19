
#include <raytracer.h>
#include <bodies.h>

#include <cassert>
#include <cmath>



using namespace raytracer;



CheckeredPlane::CheckeredPlane() {
	setPosition(Vector(0.0,0.0,0.0));
	setOrientation(
			Vector(1.0,0.0,0.0),
			Vector(0.0,1.0,0.0),
			Vector(0.0,0.0,1.0)
		);
	setColors(
			Vector(0.9,0.9,0.9),
			Vector(0.1,0.1,0.1)
		);
}


Body * CheckeredPlane::clone() const {
	return (Body*) new CheckeredPlane(*this);
}



void CheckeredPlane::setColor(const Vector & c) {

	assert(0.0 < c.x);
	assert(c.x < 1.0);
	assert(0.0 < c.y);
	assert(c.y < 1.0);
	assert(0.0 < c.z);
	assert(c.z < 1.0);

	color2 = color;
	color = c;
}



void CheckeredPlane::setColors(const Vector & c1, const Vector & c2) {

	assert(0.0 < c1.x);
	assert(c1.x < 1.0);
	assert(0.0 < c1.y);
	assert(c1.y < 1.0);
	assert(0.0 < c1.z);
	assert(c1.z < 1.0);

	assert(0.0 < c2.x);
	assert(c2.x < 1.0);
	assert(0.0 < c2.y);
	assert(c2.y < 1.0);
	assert(0.0 < c2.z);
	assert(c2.z < 1.0);

	color = c1;
	color2 = c2;
}




Vector CheckeredPlane::getColor(const Vector & p) const {

	Vector tmp = p;
	tmp.subtract(position);

	int x = (int) std::floor(tmp.dot(x_axis)),
		y = (int) std::floor(tmp.dot(y_axis));

	if ( (x+y) % 2 == 0) {
		return color;
	}

	else {
		return color2;
	}
}

Vector CheckeredPlane::getExteriorColor(const Vector & p) const {
	double d;
	int x,y;

	Vector tmp = p;
	tmp.subtract(position);

	d = tmp.dot(x_axis);
	if (d < 0.0) d -= 1;
	x = (int) d;

	d = tmp.dot(z_axis);
	if (d < 0.0) d -= 1;
	y = (int) d;

	if ( (x+y) % 2 == 0) {
		return color;
	}

	else {
		return color2;
	}
}






