
#include <raytracer.h>

#include <iostream>

#include <cmath>
#include <cassert>

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
	return 0;
}


void test_refract() {}
void test_reflect() {}
void test_unproject() {}
void test_project() {}
void test_translate() {}
void test_subtract() {}
void test_add() {}
void test_scale() {}
void test_normalize() {}
void test_power() {}
void test_copy() {}
void test_cross() {}
void test_dot() {}



void test_random() {

	RNG::init();

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



