
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

	if ( ((int) (std::floor(p.dot(x_axis)) + std::floor(p.dot(z_axis)))) % 2) {
		return color;
	}

	else {
		return color2;
	}
}






