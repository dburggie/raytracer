
#include <raytracer.h>
#include <skies.h>

#include <cmath>
#include <cassert>

using namespace raytracer;



BasicSky::BasicSky() {
	sun.copy(0.0, 1.0, 0.0);
	color.copy(0.3, 0.3, 0.8); //blueish
	up.copy(0.0, 1.0, 0.0);
}



Vector BasicSky::getColor(const Vector & direction) const {
	if (direction.dot(sun) > 0.99) {
		return Vector(.99,.99,.99);
	}

	Vector c = color;
	double inclination = 0.25 + 0.75 * std::max(0.0,direction.dot(up));
	c.power(inclination);

	return c;
}



