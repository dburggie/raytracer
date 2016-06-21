
#include <raytracer.h>

#include <iostream>
#include <cmath>
#include <cassert>

using namespace raytracer;



Tracer::Tracer() {
	camera = new Camera();
	world = new World();
	filename = "output.png";
}



Tracer::Tracer(const Tracer & t) {
	camera = new Camera(*t.camera);
	world = new World(*t.world);
	filename = t.filename;
}



Tracer::~Tracer() {
	if (world)  delete world;
	if (camera) delete camera;
}



World * Tracer::getWorld() {
	assert(world != NULL);
	return world;
}



Camera * Tracer::getCamera() {
	assert(camera != NULL);
	return camera;
}



void Tracer::render(int anti_alias, int depth) {

	assert(anti_alias > 0);

	int max_x = camera->getWidth(),
		max_y = camera->getHeight();

	Ray r;
	Vector c;
	Image image = Image(max_x, max_y);

	for (int y = 0; y < max_y; y++) {
		for (int x = 0; x < max_x; x++) {

			c.copy(0.0,0.0,0.0);

			for (int i = 0; i < anti_alias; i++) {
				r = camera->getRay(x,y);
				c.add(world->sample(r,depth));
			}

			c.scale(1.0/anti_alias);

			assert(0.0 <= c.x);
			assert(0.0 <= c.y);
			assert(0.0 <= c.z);
			assert(c.x < 1.0);
			assert(c.y < 1.0);
			assert(c.z < 1.0);

			image.setPixel(x,y,c);
		}
		if ((y+1) % 25 == 0)
			std::cerr << "raytracer::Tracer::render(): "
				<< "finished rendering scanline " << y+1 
				<< " of " << max_y << "\n";
	}

	image.write(filename);
}



void Tracer::setOutputName(const char * filename) {
	assert(filename != NULL);
	if (filename) this->filename = filename;
}













