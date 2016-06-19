#include <raytracer.h>

using namespace raytracer;

int main() {
	Image image(512,512);

	Vector c(0.0,0.0,0.0);

	for (int y = 0; y < 512; y++) {
		for (int x = 0; x < 512; x++) {
			c.x = x / 512.0;
			c.y = y / 512.0;
			c.z = (x + y) / 1024.0;
			image.setPixel(x,y,c);
		}
	}

	image.write("output.png");

	return 0;
}
