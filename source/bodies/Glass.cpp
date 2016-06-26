
#include <raytracer.h>
#include <bodies.h>

#include <cassert>
#include <cmath>



using namespace raytracer;

const static double glass_index = 1.3;
const static Vector glass_color = Vector(0.8,0.8,0.9);



GlassSphere::GlassSphere() {
	setSize(1.0);
	setRefraction(glass_index);
	setColor(glass_color);
}



GlassSphere::GlassSphere(double radius) {
	setSize(radius);
	setRefraction(glass_index);
	setColor(glass_color);
}



Body * GlassSphere::clone() const {
	return (Body*) new GlassSphere(*this);
}





GlassBubble::GlassBubble() {
	setSize(0.5);
	setRefraction(glass_index);
	setColor(glass_color);
}



GlassBubble::GlassBubble(double radius) {
	setSize(radius);
	setRefraction(glass_index);
	setColor(glass_color);
}



Body * GlassBubble::clone() const {
	return (Body*) new GlassBubble(*this);
}



Vector GlassBubble::getNormal(const Vector & p) const {
	Vector n = position;
	n.subtract(p);
	n.scale(reciprocal);
	assert(std::abs(n.dot() - 1.0) < DIV_LIMIT);
	return n;
}



GlassCylinder::GlassCylinder() {
	setSize(1.0);
	setRefraction(glass_index);
	setColor(glass_color);
}



GlassCylinder::GlassCylinder(const Vector & p, const Vector & v, double radius) {
	setSize(radius);
	setRefraction(glass_index);
	setColor(glass_color);
	setOrientation(v);
	setPosition(p);
}



Body * GlassCylinder::clone() const {
	return (Body*) new GlassCylinder(*this);
}


