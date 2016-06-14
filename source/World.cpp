
#include <raytracer.h>
#include <skies.h>

#include <cmath>
#include <cassert>

using namespace raytracer;



World::World() {
	is_copy = false;
	body_count = 0;
	light_count = 0;
	sky = new BasicSky();
	for (int i = 0; i < ARRAY_SIZE; i++) {
		lights[i] = NULL;
		bodies[i] = NULL;
	}
}



World::World(const World & w) {
	is_copy = true;

	body_count = w.body_count;
	light_count = w.light_count;
	sky = w.sky;

	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (i < body_count) bodies[i] = w.bodies[i];
		else bodies[i] = NULL;
		if (i < light_count) lights[i] = w.lights[i];
		else lights[i] = NULL;
	}
}



World::~World() {

	if (!is_copy) {

		delete sky;

		for (int i = 0; i < body_count; i++) {
			delete bodies[i];
		}

		for (int i = 0; i < light_count; i++) {
			delete lights[i];
		}
	}

}



void World::addBody(Body * b) {
	assert(body_count < ARRAY_SIZE);
	assert(b != NULL);

	bodies[body_count++] = b;
}



void World::addLight(Light * l) {
	assert(light_count < ARRAY_SIZE);
	assert(l != NULL);

	lights[light_count++] = l;
}



void World::setSky(Sky * s) {
	assert(s != NULL);

	if (sky) delete sky;

	sky = s;
}



Vector World::sample(Ray r, int depth) {

	assert(depth >= 0);

	//find closest body
	double min = 1000.0, d = -1.0;
	Body * body = NULL;
	for (int i = 0; i < body_count; i++) {
		d = bodies[i]->getDistance(r);
		if (d > DIV_LIMIT && d < min) {
			min = d; 
			body = bodies[i];
		}
	}

	//if we didn't hit anything, return a sky color
	if (!body) {
		return sky->getColor(r.v);
	}

	//get point of intersection
	Vector p = r.p;
	p.translate(r.v, min);

	//if we're at our maximum depth, return the object color
	if (depth == 0) {
		return body->getExteriorColor(p);
	}

	//we hit something, get color here and do recursion
	//find point of contact
	double s_power = body->getReflectivity(p),
		   t_power = 1 - s_power;

	Vector t_color = Vector(0.0,0.0,0.0),
		   s_color = Vector(0.0,0.0,0.0),
		   normal  = body->getNormal(p);

	//get transmissive color
	if (body->isRefracting()) {
		double ratio = body->getRefractiveRatio(p);

		Ray refract_ray = Ray(p, r.v);
		refract_ray.v.refract(normal,ratio);

		//get color along refraction ray
		t_color = sample(refract_ray, depth-1);

		t_color.scale(t_power);
	}

	else {
		t_color = body->getExteriorColor(p);
		t_color.scale(t_power);

		//put shadow calculation here
	}

	//get specular color
	Ray reflect_ray = Ray(p, r.v);
	reflect_ray.v.reflect(normal);
	s_color = sample(reflect_ray, depth-1);
	s_color.scale(s_power);
	
	t_color.add(s_color);

	//absorb some light if we're inside this object
	if (r.v.dot(normal) > DIV_LIMIT) {
		Vector absorb = body->getColor(p);
		absorb.power(min);
		t_color.scale(absorb);
	}

	return t_color;
}









