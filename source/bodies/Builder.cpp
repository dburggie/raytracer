
#include <raytracer.h>
#include <bodies.h>
#include <cassert>


using namespace raytracer;


//glass typical values
const static double glass_index = 1.46;
const static Vector glass_color = Vector(0.8,0.8,0.9);

//mirror values
const static double mirror_index = 2.5;
const static Vector mirror_color = Vector(0.75,0.75,0.75);
const static double mirror_reflectivity = 0.95;



void Builder::makeGlass(BasicBody * body) {
	body->setIndex(glass_index);
	body->setColor(glass_color);
	body->refractionOn();
}



void Builder::makeMirror(BasicBody * body) {
	body->setIndex(mirror_index);
	body->setColor(mirror_color);
	body->setReflectivity(mirror_reflectivity);
	body->refractionOff();
}



Sphere * Builder::newGlassSphere() {
	Sphere *s = new Sphere();
	makeGlass(s);
	return s;
}



Sphere * Builder::newMirrorSphere() {
	Sphere *s = new Sphere();
	makeMirror(s);
	return s;
}



Plane * Builder::newGlassPlane() {
	Plane *p = new Plane();
	makeGlass(p);
	return p;
}



Plane * Builder::newMirrorPlane() {
	Plane *p = new Plane();
	makeMirror(p);
	return p;
}

