
#ifndef __SKIES_H
#define __SKIES_H

#include <raytracer.h>



namespace raytracer {



class BasicSky : public Sky {
private:
	Vector sun, color, up;
public:
	BasicSky();
	virtual Vector getColor(const Vector & direction) const;
}; //end of BasicSky declaration



} //end of additions to namespace raytracer



#endif

