
#include <raytracer.h>

#include <cstdio>
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



#include <png.h>
#include <cstring>



static void setpixel(
		png_bytep buf,
		png_uint_32 stride,
		int x, int y,
		const raytracer::Vector & v)
{
	assert(buf != NULL);
	assert(stride > 0);
	assert(x >= 0);
	assert(y >= 0);

	assert(0.0 < v.x);
	assert(v.x < 1.0);

	assert(0.0 < v.y);
	assert(v.y < 1.0);

	assert(0.0 < v.z);
	assert(v.z < 1.0);

	int offset = (y * stride) + (x * 3);
	buf[offset++] = 0xff & ((int)(256*v.x));
	buf[offset++] = 0xff & ((int)(256*v.y));
	buf[offset  ] = 0xff & ((int)(256*v.z));
}



void raytracer::Image::write(const char *filename) const {

	png_image img; //allocate
	std::memset(&img, 0, (sizeof img)); //memset to zero

	img.version = PNG_IMAGE_VERSION;
	img.opaque = NULL;
	img.width = width;
	img.height = height;
	img.format = PNG_FORMAT_RGB;
	img.flags = 0;
	img.colormap_entries = 0;

	png_bytep buf = NULL;
	buf = (png_bytep) std::malloc(PNG_IMAGE_SIZE(img));

	png_uint_32 stride = PNG_IMAGE_ROW_STRIDE(img);

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			setpixel(buf,stride,x,y, *scanlines[y][x]);

	png_image_write_to_file(&img, filename, 0, buf, stride, NULL);

}



