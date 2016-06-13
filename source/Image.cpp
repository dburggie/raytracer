
#include <raytracer.h>

#include <png.h>
#include <cstdlib>
#include <cmath>
#include <cassert>




namespace raytracer {



Image::Image() {
	width = 0; height = 0;
	scanlines = NULL;
}



Image::Image(int w, int h) {
	setDims(w,h);
}



Image::Image(const Image & image) {
	scanlines = NULL;
	setDims(image.width, image.height);
	
	// copy pixels over
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			scanlines[y][x]->copy(*image.scanlines[y][x]);
		}
	}
}



Image::~Image() {
	if (scanlines) {
		for (int y = 0; y < height; y++) {
			if (scanlines[y]) {
				for (int x = 0; x < width; x++) {
					if (scanlines[y][x]) {
						delete scanlines[y][x];
					}
				}
				std::free(scanlines[y]);
			}
		}
		std::free(scanlines);
	}
}



void Image::setDims(int w, int h) {
	assert(w > 0);
	assert(h > 0);
	
	//delete old scanlines if present
	if (scanlines) {
		for (int y = 0; y < height; y++) {
			if (scanlines[y]) {
				for (int x = 0; x < width; x++) {
					if (scanlines[y][x]) {
						delete scanlines[y][x];
						scanlines[y][x] = NULL;
					}
				}
				std::free(scanlines[y]);
				scanlines[y] = NULL;
			}
		}
		
		std::free(scanlines);
		scanlines = NULL;
	}
	
	width = w;
	height = h;
	
	//allocate the array
	scanlines = (Vector***) std::malloc(height * sizeof(Vector***));
	
	for (int y = 0; y < height; y++) {
		scanlines[y] = (Vector**) std::malloc(width * sizeof(Vector**));
		for (int x = 0; x < width; x++) {
			scanlines[y][x] = new Vector(0.0,0.0,0.0);
		}
	}
}




void Image::setPixel(int x, int y, const Vector & color) {
	assert(x >= 0);
	assert(y >= 0);
	assert(x < width);
	assert(y < height);
	
	scanlines[y][x]->copy(color);
}



}//end namespace raytracer



void raytracer::Image::write(const char *filename) const {
	//go fucking mad while trying to figure out png.h
	//just look for a fucking library that makes raster drawing easy
	//jesus christ
}

