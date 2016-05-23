#include <raytracer.h>

using namespace raytracer;



Ray::Ray() {
	p.setxyz(0.0,0.0,0.0);
	v.setxyz(0.0,1.0,0.0);
}



Ray::Ray(const Vector & point, const Vector & direction) {
	p.copy(point);
	v.copy(direction);
}



Ray::Ray(const Ray & ray) {
	p.copy(ray.p);
	v.copy(ray.v);
}



void Ray::reflect(const Vector & point, const Vector & normal) {
	// take the ray location to point, do some math to determine new location
	// we need to find the projection of ray direction onto the surface normal
	// subtract twice that projection from the ray direction.
	Vector proj = normal;
	proj.scale( Vector::dot(v, normal) );

	p.copy(point);
	v.translate(proj, -2.0);
	v.normalize();
}



Vector Ray::follow(double distance) {
	Vector vec = p;
	vec.translate(v, distance);
	return vec;
}



