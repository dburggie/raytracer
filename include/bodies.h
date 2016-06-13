#ifndef __BODIES_H
#define __BODIES_H

#include <raytracer.h>



namespace raytracer {



/* ########## Body Classes ########## */



class BasicBody : public Body {
protected:
	bool refracting;
	double index_ratio;
	double size;
	double reflectivity; // power used in specular reflection approximation.
	Vector position, x_axis, y_axis, z_axis, color, exterior_color;
public:
	BasicBody();

	virtual Body * clone() const;

	// implementing pure-virtual functions of Body
	virtual bool isRefracting() const;
	virtual double getRefractiveRatio(const Vector & p) const;
	virtual Vector getColor(const Vector & p) const;
	virtual Vector getExteriorColor(const Vector & p) const;
	virtual double getReflectivity(const Vector & p) const;

	// remaining pure-virtual
	virtual Vector getNormal(const Vector & p) const;
	virtual double getDistance(const Ray & r) const;

	// new to BasicBody
	virtual void setPosition(const Vector & p);
	virtual void setOrientation(
			const Vector & X, 
			const Vector & Y, 
			const Vector & Z
		);
	virtual void setSize(double S); // asserts S>0?
	virtual void setColor(const Vector & c); // don't crucify me for reusing Vector for color
	virtual void setExteriorColor(const Vector & c);
	virtual void setReflectivity(double index);
	virtual void refractionOff();
	virtual void setRefraction(double index); //interior index over exterior 
}; //end BasicBody declaration



class Sphere : public BasicBody {
protected:
	double magnitude;
	double reciprocal;
public:
	Sphere(double radius);

	virtual Body * clone() const;

	virtual void setSize(double radius);

	virtual Vector getNormal(const Vector & p) const;
	virtual double getDistance(const Ray & r) const;
}; //end Sphere declaration



class Cylinder : public BasicBody {
protected:
	double magnitude;
	double reciprocal;
public:
	Cylinder();
	Cylinder(const Vector & p, const Vector & v, double radius);

	virtual Body * clone() const;

	virtual void setSize(double radius);
	virtual void setOrientation(const Vector & axis);
	virtual Vector getNormal(const Vector & p) const;
	virtual double getDistance(const Ray & r) const;
}; //end Cylinder declaration



class Plane : public BasicBody {
public:
	Plane(const Vector & position, const Vector & normal);

	virtual Body * clone() const;

	virtual Vector getNormal(const Vector & p) const;
	virtual double getDistance(const Ray & r) const;
}; //end Plane declaration



class CheckeredPlane : public Plane {
protected:
	Vector color2;
public:

	virtual Body * clone() const;

	virtual void setColor(const Vector & c);
	virtual void setColors(const Vector & c1, const Vector & c2);
	virtual Vector getColor(const Vector & p) const;
}; //end CheckeredPlane declaration



} //end additions to namespace raytracer



#endif
