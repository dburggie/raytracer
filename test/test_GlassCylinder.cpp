
#include <raytracer.h>
#include <bodies.h>

using namespace raytracer;


const Vector x_axis = Vector(1.0,0.0,0.0);
const Vector y_axis = Vector(0.0,1.0,0.0);
const Vector z_axis = Vector(0.0,0.0,1.0);
const Vector zero   = Vector(0.0,0.0,0.0);

const Vector red   = Vector(0.800,0.200,0.200);
const Vector green = Vector(0.200,0.800,0.200);
const Vector blue  = Vector(0.200,0.200,0.800);
const Vector white = Vector(0.900,0.900,0.900);
const Vector black = Vector(0.100,0.100,0.100);
const Vector glass = Vector(0.7,0.7,0.9);

const char * filename = "GlassCylinder.png";


int main() {

	RNG::init();

	Tracer t;

	Vector f = Vector(0.0,1.0,0.0),
		   p = Vector(0.0, 3.0, 12.0),
		   right = Vector(1.0,0.0,0.0),
		   up = f;

	up.subtract(p); up.normalize();
	up = right.cross(up); up.normalize();

	//set up camera
	Camera * c = t.getCamera();
	c->setSize(3.0,3.0);
	c->setFocus(f);
	c->setPosition(p);
	c->setOrientation(right, up);
	c->setResolution(512);
	c->init();

	//set up world
	World * w = t.getWorld();

	//add a checkered plane
	CheckeredPlane *cp = new CheckeredPlane();
	cp->setPosition(zero);
	cp->setNormal(y_axis);
	cp->setOrientation(x_axis,z_axis);
	cp->setSize(1.0);
	cp->setIndex(1.8);
	cp->setColors(green, red);
	w->addBody(cp);
	cp = NULL;

	//add a Glass Cylinder
	Cylinder * gc = new Cylinder();
	gc->setSize(1.0);
	gc->setPosition(zero);
	Builder::makeGlass(gc);
	w->addBody(gc);
	gc = NULL;

	//render
	t.setOutputName(filename);
	t.render(4);

	return 0;
}




