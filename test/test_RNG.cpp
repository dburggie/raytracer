#include <raytracer.h>
#include <iostream>

using namespace raytracer;

int main() {
	
	RNG::init();
	RNG & rng = * RNG::get();
	
	for (int i = 0; i < 10; i++)
		std::cout << rng.next() << '\n';

	int counts[10] = { 0 };
	
	for (int i = 0; i < 100000; i++) {
		counts[(int) (10 * rng.next())]++;
	}

	for (int i = 0; i < 10; i++)
		std::cout << i << ": " << counts[i] << '\n';

	return 0;
}
