
#include <raytracer.h>

#include <iostream>

#include <cmath>
#include <cassert>

#define DBL_CMP(X,Y) (std::abs((X) - (Y)) < 0.000001)

using namespace raytracer;


static void test_random();
static void test_dot();
static void test_cross();
static void test_copy();
static void test_power();
static void test_normalize();
static void test_scale();
static void test_add();
static void test_subtract();
static void test_translate();
static void test_project();
static void test_unproject();
static void test_reflect();
static void test_refract();

int main() {

	RNG::init();

	test_random();
	test_dot();
	test_cross();
	test_copy();
	test_power();
	test_normalize();
	test_scale();
	test_add();
	test_subtract();
	test_translate();
	test_project();
	test_unproject();
	test_reflect();
	test_refract();

	std::cout << "raytracer::Vector passed all tests\n";

	return 0;
}


void test_refract() {}
void test_reflect() {}
void test_unproject() {}
void test_project() {}
void test_translate() {}



void test_subtract() {
	for (int i = 0; i < 10000; i++){
		Vector u = Vector::random(1.0),
			   v = Vector::random(1.0),
			   w = u;
		w.subtract(v);
		assert(DBL_CMP(u.x-v.x,w.x));
		assert(DBL_CMP(u.y-v.y,w.y));
		assert(DBL_CMP(u.z-v.z,w.z));

		w.copy(u); w.subtract(u);
		assert(DBL_CMP(w.dot(),0.0));
	}
}



void test_add() {
	for (int i = 0; i < 10000; i++) {
		Vector u = Vector::random(1.0),
			   v = Vector::random(1.0),
			   w = u;
		w.add(v);
		assert(DBL_CMP(u.x+v.x,w.x));
		assert(DBL_CMP(u.y+v.y,w.y));
		assert(DBL_CMP(u.z+v.z,w.z));

		w.copy(u); w.add(u);
		assert(DBL_CMP(w.dot(), 4.0*u.dot()));
	}
}



void test_scale() {
	RNG *rng = RNG::get();

	for (int i = 0; i < 10000; i++) {
		Vector v = Vector::random(1.0),
			   w = v;

		double s = rng->next();
		w.scale(s);

		assert(DBL_CMP(v.dot(w),s*v.dot()));
		assert(DBL_CMP(w.dot(w),s*s*v.dot()));
		assert(DBL_CMP(v.cross(w).dot(),0.0));
	}
}



void test_normalize() {
	for (int i = 0; i < 10000; i++) {
		Vector v = Vector::random(1.0),
			   w = v;
		w.normalize();
		assert(DBL_CMP(w.dot(),1.0));
		assert(DBL_CMP(v.cross(w).dot(),0.0));
	}
}



void test_power() {
	for (int i = 0; i < 10000; i++) {
		Vector v = Vector::random(1.0),
			   w = v;
		v.power(2.0);
		assert(DBL_CMP(v.x+v.y+v.z, w.dot()));
	}
}



void test_copy() {
	for (int i = 0; i < 10000; i++) {
		Vector v = Vector::random(1.0),
			   w;
		
		w.copy(v);
		assert(DBL_CMP(v.dot(),w.dot()));
		assert(DBL_CMP(v.dot(w),v.dot()));

		w.subtract(v);
		assert(DBL_CMP(w.dot(),0.0));

		w.copy(v.x,v.y,v.z);
		assert(DBL_CMP(v.dot(),w.dot()));
		assert(DBL_CMP(v.dot(w),v.dot()));

		w.subtract(v);
		assert(DBL_CMP(w.dot(),0.0));
	}
}



void test_cross() {
	for (int i = 0; i < 10000; i++) {
		Vector v = Vector::random(1.0),
			   w = Vector::random(1.0),
			   a = v.cross(w),
			   b = Vector::cross(v,w);

		assert(a.dot() < 1.0);
		assert(b.dot() < 1.0);
		assert(DBL_CMP(a.dot(),b.dot()));
		assert(DBL_CMP(a.dot(v),0.0));
		assert(DBL_CMP(a.dot(w),0.0));
		assert(DBL_CMP(b.dot(v),0.0));
		assert(DBL_CMP(b.dot(w),0.0));
		
		a.add(w.cross(v));
		assert(DBL_CMP(a.dot(),0.0));

		b.add(Vector::cross(w,v));
		assert(DBL_CMP(b.dot(),0.0));
	}
}



void test_dot() {
	for (int i = 0; i < 10000; i++) {
		Vector v = Vector::random(1.0);
		Vector w = Vector::random(1.0);

		double vl = std::sqrt(v.dot()),
			   wl = std::sqrt(w.dot());

		assert(v.dot(w) < vl*wl);
		assert(w.dot(v) < vl*wl);
		assert(v.dot() < 1.0);
		assert(w.dot() < 1.0);
		assert(v.dot(v) < 1.0);
		assert(w.dot(w) < 1.0);
		assert(Vector::dot(v,v));
		assert(Vector::dot(w,w));

		assert(DBL_CMP(v.dot(w),w.dot(v)));
		assert(DBL_CMP(v.dot(w),Vector::dot(v,w)));
		assert(DBL_CMP(w.dot(v),Vector::dot(v,w)));
		assert(DBL_CMP(v.dot(w),Vector::dot(w,v)));
	}
}



void test_random() {


	int x = 0, y = 0, z = 0;

	for (int i = 0; i < 10000; i++) {
		Vector v = Vector::random(1.0);
		assert(v.dot() < 1.0);
		if (v.x < 0.0)
			x--;
		else
			x++;
		if (v.y < 0.0)
			y--;
		else
			y++;
		if (v.z < 0.0)
			z--;
		else
			z++;
	}

	assert(std::abs(x) < 1000);
	assert(std::abs(y) < 1000);
	assert(std::abs(z) < 1000);
}



