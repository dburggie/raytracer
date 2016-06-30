
#include <raytracer.h>
#include <bodies.h>

using namespace raytracer;

class OneWayPlane : public Plane {
public:
	OneWayPlane() { useDefaults(); }
	virtual double getDistance(const Ray & ray) const;
};

double OneWayPlane::getDistance(const Ray & ray) const {
	if (ray.v.dot(orientation) > ZERO)
		return -1.0;
	else
		return ((Plane*)this)->getDistance(ray);
}

static const int height_pixels = 900;
static const double aspect_ratio = 1.6; //1440x900

static const int anti_alias = 32;
static const int recursion_depth = 8;

static const char * filename = "askew.png";

static Plane * newWall();

int main() {
	
	double window_h = 4.0;
	double window_w = window_h * aspect_ratio;
	
	RNG::init();
	Tracer t;
	World * world = t.getWorld();
	Camera * cam = t.getCamera();
	
	//init cam
	cam->setFocus(Vector(0.0,1.0,0.0));
	cam->setPosition(Vector(5.0,2.5,10.0));
	cam->setSize(window_w,window_h);
	cam->setResolution(height_pixels);
	cam->init();
	
	//init ball
	Sphere * ball = new Sphere();
	ball->setPosition(Vector(0.0,0.2,0.0));
	ball->setSize(1.0);
	ball->setColor(Vector(0.2,0.1,0.1));
	ball->setReflectivity(0.6);
	world->addBody(ball);
	
	//init floor
	CheckeredPlane * floor = new CheckeredPlane();
	floor->setSize(1.0);
	floor->setNormal(Vector(0.0,1.0,0.0));
	floor->setOrientation(Vector(1.0,0.0,0.0), Vector(0.0,0.0,1.0));
	floor->setColors(Vector(0.1,0.1,0.2),Vector(0.99,0.99,0.99));
	floor->setReflectivity(0.0);
	world->addBody(floor);
	
	//init all walls (and ceiling)
	Plane * p = NULL;
	p = newWall();
	p->setPosition(Vector(0.0,0.0,6.0));
	p->setOrientation(Vector(1.0,0.0,-3.0));
	world->addBody(p);
	p = NULL;
	p = newWall();
	p->setPosition(Vector(0.0,0.0,-6.0));
	p->setOrientation(Vector(-1.0,0.0,3.0));
	world->addBody(p);
	p = NULL;
	p = newWall();
	p->setPosition(Vector(6.0,0.0,0.0));
	p->setOrientation(Vector(-3.0,0.0,-1.0));
	world->addBody(p);
	p = NULL;
	p = newWall();
	p->setPosition(Vector(-6.0,0.0,0.0));
	p->setOrientation(Vector(3.0,0.0,1.0));
	world->addBody(p);
	p = NULL;
	p = newWall();
	p->setPosition(Vector(0.0,6.0,0.0));
	p->setOrientation(Vector(0.0,-1.0,0.0));
	world->addBody(p);
	p = NULL;
	
	t.setOutputName(filename);
	t.render(anti_alias,recursion_depth);
	
	return 0;
}


static Plane * newWall() {
	OneWayPlane * p = new OneWayPlane();
	p->setReflectivity(0.6);
	p->setColor(Vector(0.01,0.01,0.01));
	return (Plane*)p;
}
