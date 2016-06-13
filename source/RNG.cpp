
#include <raytracer.h>
#include <cassert>
#include <cmath>
#include <chrono>
#include <random>

using namespace raytracer;



RNG * RNG::singleton = NULL;
bool RNG::initialized = false;



RNG::RNG() {
	uniform = std::uniform_real_distribution<double>(0.0,1.0);
	engine = std::mt19937();

	engine.seed(std::chrono::system_clock::now().time_since_epoch().count());
}



RNG * RNG::get() {
	assert(initialized);
	assert(singleton != NULL);

	return singleton;
}



void RNG::init() {
	assert(!initialized);

	if (!initialized) {
		initialized = true;
		singleton = new RNG();
		assert(singleton != NULL);
	}
}



double RNG::next() {
	assert(initialized);

	return uniform(engine);
}




