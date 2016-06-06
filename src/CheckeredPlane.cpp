
#include <raytracer.h>
#include <cassert>
#include <cmath>

using namespace raytracer;

/*
	class CheckeredPlane : public Plane {
		private:
		protected:
			Vector color2;
		public:
			CheckeredPlane(const Vector & c1, const Vector & c2);

			virtual void setColor(const Vector & c);
			virtual void setColors(const Vector & c1, const Vector & c2);
			virtual Vector getColor(const Vector & p) const;
	};
 */



CheckeredPlane::CheckeredPlane(const Vector & c1, const Vector & c2) {
	setColors(c1,c2);
}



void CheckeredPlane::setColor(const Vector & c) {

	assert(0.0 < c1.x);
	assert(c1.y < 1.0);
	assert(0.0 < c1.x);
	assert(c1.y < 1.0);
	assert(0.0 < c1.x);
	assert(c1.y < 1.0);

	color2 = color;
	color = c;
}



void CheckeredPlane::setColors(const Vector & c1, const Vector & c2) {

	assert(0.0 < c1.x);
	assert(c1.y < 1.0);
	assert(0.0 < c1.x);
	assert(c1.y < 1.0);
	assert(0.0 < c1.x);
	assert(c1.y < 1.0);

	assert(0.0 < c2.x);
	assert(c2.y < 1.0);
	assert(0.0 < c2.x);
	assert(c2.y < 1.0);
	assert(0.0 < c2.x);
	assert(c2.y < 1.0);

	color = c1;
	color2 = c2;
}




Vector CheckeredPlane::getColor(const Vector & p) const {

	assert(p.dot(z_axis) < 0.01);

	if (std::floor(p.dot(x_axis)) + std::floor(p.dot(y_axis)) % 2) {
		return color;
	}

	else {
		return color2;
	}
}






