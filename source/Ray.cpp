#include <raytracer.h>

using namespace raytracer;



Ray::Ray() {
	p.copy(0.0,0.0,0.0);
	v.copy(0.0,1.0,0.0);
}



Ray::Ray(const Vector & point, const Vector & direction) {
	p.copy(point);
	v.copy(direction);
}



Ray::Ray(const Ray & ray) {
	p.copy(ray.p);
	v.copy(ray.v);
}



Vector Ray::follow(double distance) const {
	Vector vec = p;
	vec.translate(v, distance);
	return vec;
}



