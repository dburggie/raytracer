
#include <raytracer.h>

#include <cmath>
#include <cassert>

#include <iostream>

#define COMPARE(X,Y) std::abs((X) - (Y)) < 0.000001

using namespace raytracer;



static void test_constructors();
static void test_follow();



int main() {

	RNG::init();

	test_constructors();
	test_follow();

	std::cout << "raytracer::Ray passed all tests.\n";

	return 0;

}



void test_constructors() {
	for (int i = 0; i < 10000; i++) {
		Ray rb = Ray(Vector::random(1.0),Vector::randunit()),
			rc = Ray(rb);

		assert(COMPARE(rb.p.dot(rc.p), rb.p.dot()));
		assert(COMPARE(rb.v.dot(rc.v), rb.v.dot()));
		assert(rb.p.dot() < 1.0);
		assert(COMPARE(std::sqrt(rb.v.dot()), 1.0));
	}
}



void test_follow() {
	RNG *rng = RNG::get();
	for (int i = 0; i < 10000; i++) {
		Ray ray = Ray(Vector::random(1.0),Vector::randunit());
		double distance = rng->next();
		Vector f = ray.follow(distance);

		f.subtract(ray.p);
		assert(COMPARE(f.dot(ray.v),distance));
	}
}



