
#include <raytracer.h>
#include <skies.h>

#include <cmath>
#include <cassert>

using namespace raytracer;



World::World() {
	body_count = 0;
	light_count = 0;
	sky = new BasicSky();
	for (int i = 0; i < ARRAY_SIZE; i++) {
		lights[i] = NULL;
		bodies[i] = NULL;
	}
}



World::World(const World & w) {
	body_count = w.body_count;
	light_count = w.light_count;
	sky = w.sky->clone();

	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (i < body_count) bodies[i] = w.bodies[i]->clone();
		else bodies[i] = NULL;
		if (i < light_count) lights[i] = w.lights[i]->clone();
		else lights[i] = NULL;
	}
}



World::~World() {

	if (sky) delete sky;

	for (int i = 0; i < body_count; i++) {
		delete bodies[i];
	}

	for (int i = 0; i < light_count; i++) {
		delete lights[i];
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
		assert(bodies[i] != NULL);
		d = bodies[i]->getDistance(r);
		if (d > ZERO && d < min) {
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
	Ray incident_ray = Ray(p,r.v);

	//if we're at our maximum depth, return the object color
	if (depth == 0) {
		return body->getColor(p);
	}

	//we hit something, get color here and do recursion
	//find point of contact
	Vector t_color = Vector(0.0,0.0,0.0),
		   s_color = Vector(0.0,0.0,0.0),
		   normal  = body->getNormal(p);

	double s_power, t_power, cosine = r.v.dot(normal);

	s_power = body->getReflectivity(p);
	s_power = s_power + (1 - s_power) * std::pow(1 - std::abs(cosine), 5.0);
	t_power = 1.0 - s_power;

	//get transmissive color
	if (body->isTransparent(p)) {
		double index = body->getIndex(p);

		Ray refract_ray = incident_ray;
		refract_ray.v.refract(normal,index);
		refract_ray.v.normalize();

		//get color along refraction ray
		t_color = sample(refract_ray, depth-1);

		t_color.scale(t_power);
	}

	else {
		t_color = body->getColor(p);
		t_color.scale(t_power);

		//put shadow calculation here
	}

	//get specular color
	Ray reflect_ray = incident_ray;
	reflect_ray.v.reflect(normal);
	reflect_ray.v.normalize();
	s_color = sample(reflect_ray, depth-1);
	s_color.scale(s_power);
	
	t_color.add(s_color);

	//absorb some light if we're inside this object
	if (body->isInterior(incident_ray)) {
		Vector absorb = body->getInteriorColor(p);
		absorb.power(min);
		t_color.scale(absorb);
	}

	return t_color;
}









