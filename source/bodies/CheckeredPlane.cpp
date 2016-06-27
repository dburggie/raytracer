
#include <raytracer.h>
#include <bodies.h>

#include <cassert>
#include <cmath>



using namespace raytracer;



CheckeredPlane::CheckeredPlane() {
	useDefaults();
	setColors(
			Vector(0.9,0.9,0.9),
			Vector(0.1,0.1,0.1)
		);
}


Body * CheckeredPlane::clone() const {
	return (Body*) new CheckeredPlane(*this);
}



void CheckeredPlane::setOrientation(const Vector & x, const Vector & y) {
	x_axis.copy(x);
	y_axis.copy(y);
	x_axis.normalize();
	y_axis.normalize();
}


void CheckeredPlane::setColor(const Vector & c) {

	assert(0.0 < c.x);
	assert(0.0 < c.y);
	assert(0.0 < c.z);
	assert(c.x < 1.0);
	assert(c.y < 1.0);
	assert(c.z < 1.0);

	color2.copy(color);
	color.copy(c);
}



void CheckeredPlane::setColors(const Vector & c1, const Vector & c2) {

	assert(0.0 < c1.x);
	assert(0.0 < c1.y);
	assert(0.0 < c1.z);
	assert(c1.x < 1.0);
	assert(c1.y < 1.0);
	assert(c1.z < 1.0);

	assert(0.0 < c2.x);
	assert(0.0 < c2.y);
	assert(0.0 < c2.z);
	assert(c2.x < 1.0);
	assert(c2.y < 1.0);
	assert(c2.z < 1.0);

	color.copy(c1);
	color2.copy(c2);
}




Vector CheckeredPlane::getColor(const Vector & p) const {

	double d;
	int x,y;

	Vector tmp = p;
	tmp.subtract(position);

	d = tmp.dot(x_axis) / size;
	if (d < 0.0) d -= 1;
	x = (int) d;

	d = tmp.dot(y_axis) / size;
	if (d < 0.0) d -= 1;
	y = (int) d;

	if ( (x+y) % 2 == 0) {
		return color;
	}

	else {
		return color2;
	}
}






