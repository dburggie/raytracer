
#ifndef __LIGHTS_H
#define __LIGHTS_H

#include <raytracer.h>



namespace raytracer {



class BasicLight : public Light {
private:
	Vector direction, color, intensity;
	bool hasPenumbra;
	double penumbra;
public:
	BasicLight();
	virtual void setDirection(const Vector & p);
	virtual void setPenumbralSize(double d);
	virtual void setColor(const Vector & c);
	virtual void setIntensity(const Vector & i);

	virtual Vector getDirection(const Vector & p) const;
	virtual Vector getColor() const;
	virtual Vector getIntensity(const Vector & p) const;
}; //end of BasicLight declaration



} //end additions to namespace raytracer



#endif

