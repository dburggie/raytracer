#include <raytracer.h>

#include <iostream>

#include <cmath>
#include <cassert>

using namespace raytracer;

int main() {
	
	RNG::init();
	RNG & rng = * RNG::get();
	
	int counts[10] = { 0 };
	
	for (int i = 0; i < 100000; i++) {
		counts[(int) (10 * rng.next())]++;
	}

	for (int i = 0; i < 10; i++)
		assert(std::abs(counts[i] - 10000) < 1000);

	std::cout << "raytracer::RNG passed all tests\n";

	return 0;
}
