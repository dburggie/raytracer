#ifndef __BODIES_H
#define __BODIES_H

#include <raytracer.h>



namespace raytracer {



/* ########## Body Classes ########## */



class BasicBody : public Body {
protected:
	bool transparent;
	bool matte;
	double normal_delta;
	double index;
	double size;
	double reflectivity;
	Vector position, orientation, x_axis, y_axis, z_axis;
	Vector color, interior_color;
	
public:
	BasicBody();

	// implementing pure-virtual functions of Body
	virtual bool isTransparent(const Vector & p) const;
	virtual double getIndex(const Vector & p) const;
	virtual Vector getInteriorColor(const Vector & p) const;
	virtual Vector getColor(const Vector & p) const;
	virtual double getReflectivity(const Ray & incident_ray) const;

	// remaining pure-virtual
	virtual Vector getNormal(const Vector & p) const = 0;
	virtual double getDistance(const Ray & r) const = 0;
	virtual bool isInterior(const Ray & incident_ray) const = 0;

	// new to BasicBody

	virtual void useDefaults();
	
	//probably obvious settings
	virtual void setPosition(const Vector & p);
	virtual void setOrientation(const Vector & o);
	virtual void setOrientation(
			const Vector & X,
			const Vector & Y,
			const Vector & Z
		);
	virtual void setSize(double S);
	virtual void setInteriorColor(const Vector & c);
	virtual void setColor(const Vector & c);
	
	//index of refraction also calculates a surface reflectivity
	virtual void setIndex(double n);
	virtual void setReflectivity(double r); // 0.0 <= r < 1.0
	
	//refracting surfaces are transparent
	virtual void refractionOn();
	virtual void refractionOff();
	
	//matte surfaces have small changes to the perfect surface normal
	virtual void matteOn(double delta);
	virtual void matteOff();
}; //end BasicBody declaration



class Sphere : public BasicBody {
protected:
	double magnitude;
	double reciprocal;
	bool inverted;
public:
	Sphere();
	Sphere(double radius);

	virtual Body * clone() const;

	virtual void setSize(double radius);

	virtual Vector getNormal(const Vector & p) const;
	virtual double getDistance(const Ray & r) const;
	virtual bool invert(); //changes body material to exterior and back
}; //end Sphere declaration



class Cylinder : public Sphere {
public:
	Cylinder();

	virtual Body * clone() const;

	virtual Vector getNormal(const Vector & p) const;
	virtual double getDistance(const Ray & r) const;
}; //end Cylinder declaration



class Plane : public BasicBody {
public:
	Plane();

	virtual Body * clone() const;

	virtual Vector getNormal(const Vector & p) const;
	virtual double getDistance(const Ray & r) const;
}; //end Plane declaration



class CheckeredPlane : public Plane {
protected:
	Vector color2;
public:
	CheckeredPlane();

	virtual Body * clone() const;

	virtual void setOrientation(const Vector & x, const Vector & y);
	
	virtual void setColor(const Vector & c);
	virtual void setColors(const Vector & c1, const Vector & c2);
	
	virtual Vector getColor(const Vector & p) const;
}; //end CheckeredPlane declaration




class Builder {
protected:
	Builder();
public:
	static virtual void makeGlass(BasicBody * body);
	static virtual void makeMirror(BasicBody * body);
	
	static Sphere * newGlassSphere();
	static Sphere * newMirrorSphere();
	
	static Plane * newGlassPlane();
	static Plane * newMirrorPlane();
	
	static Cylinder * newGlassCylinder();
	static Cylinder * newMirrorCylinder();
};

} //end additions to namespace raytracer



#endif
