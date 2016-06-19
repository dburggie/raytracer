
#include <raytracer.h>
#include <bodies.h>

using namespace raytracer;





const Vector x_axis = Vector(1.0,0.0,0.0);
const Vector y_axis = Vector(0.0,1.0,0.0);
const Vector z_axis = Vector(0.0,0.0,1.0);
const Vector zero   = Vector(0.0,0.0,0.0);





const Vector red   = Vector(0.999,0.001,0.001);
const Vector green = Vector(0.001,0.999,0.001);
const Vector blue  = Vector(0.001,0.001,0.999);
const Vector white = Vector(0.999,0.999,0.999);
const Vector black = Vector(0.001,0.001,0.001);





int main() {

	RNG::init();

	Tracer t;

	Vector f = Vector(0.0,1.0,0.0),
		   p = Vector(0.0,1.0,5.0),
		   up = Vector(0.0,1.0,0.0),
		   right = Vector(1.0,0.0,0.0);


	//set up camera
	Camera * c = t.getCamera();
	c->setSize(2.0,2.0);
	c->setFocus(f);
	c->setPosition(p);
	c->setOrientation(right, up);
	c->setResolution(512);
	c->init();

	//set up world
	World * w = t.getWorld();

	//add a checkered plane
	CheckeredPlane *cp = new CheckeredPlane();
	cp->setReflectivity(1.8);
	cp->setColors(blue, white);
	w->addBody(cp);
	cp = NULL;

	//add a sphere
	Sphere *s = new Sphere(1.0);
	s->setPosition(y_axis);
	s->setColor(red);
	s->setReflectivity(1.3);
	w->addBody(s);
	s = NULL;

	//render
	t.render(4);

	return 0;
}




