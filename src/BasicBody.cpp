#include <raytracer.h>
#include <cassert>

using namespace raytracer;

/*
	class BasicBody : public Body {
		private:
		protected:
			bool refracting;
			double index_ratio;
			double size;
			double reflectivity; // power used in specular reflection approximation.
			Vector position, x_axis, y_axis, z_axis, color;
		public:
			// implementing pure-virtual functions of Body
			virtual bool isRefracting() const;
			virtual double getRefractiveRatio(const Vector & p) const;
			virtual Vector getColor(const Vector & p) const;
			virtual double getReflectivity(const Vector & p) const;

			// remaining pure-virtual
			virtual Vector getNormal(const Vector & p) const = 0;
			virtual double getDistance(const Ray & r) const = 0;

			// new to BasicBody
			virtual void setPosition(const Vector & p);
			virtual void setOrientation(
					const Vector & X, 
					const Vector & Y, 
					const Vector & Z
				);
			virtual void setSize(double S); // asserts S>0?
			virtual void setColor(const Vector & c); // don't crucify me for reusing Vector for color
			virtual void refractionOff();
			virtual void setRefraction(double ratio); //interior index over exterior 
	};
 */



BasicBody::BasicBody() {
	refracting = false;
	index_ratio = 0.01;
	size = 1.0;
	position.copy(0.0,0.0,0.0);
	x_axis.copy(1.0,0.0,0.0);
	y_axis.copy(0.0,1.0,0.0);
	z_axis.copy(0.0,0.0,1.0);
	color.copy(0.50,0.50,0.50);
}



bool BasicBody::isRefracting() const {
	return refracting;
}



double BasicBody::getRefractiveRatio(const Vector & p) const {
	return index_ratio;
}



Vector BasicBody::getColor(const Vector & p) const {
	return color;
}



void BasicBody::setReflectivity(double r) {
	assert(r > 0);

	reflectivity = r;
}



double BasicBody::getReflectivity(const Vector & p) const {
	return reflectivity;
}





void BasicBody::setPosition(const Vector & p) {
	position.copy(p);
}



void BasicBody::setOrientation(
		const Vector & X, const Vector & Y, const Vector & Z ) {
	x_axis.copy(X);
	y_axis.copy(Y);
	z_axis.copy(Z);

	x_axis.normalize();
	y_axis.normalize();
	z_axis.normalize();
}



void BasicBody::setSize(double S) {
	assert(S > DIV_LIMIT);

	size = S;
}



void BasicBody::setColor(const Vector & c) {
	assert(c.x > 0);
	assert(c.y > 0);
	assert(c.z > 0);
	assert(c.x < 1);
	assert(c.y < 1);
	assert(c.z < 1);

	color.copy(c);
}



void BasicBody::refractionOff() {
	refracting = false;
	index_ratio = 0.01;
}



void BasicBody::setRefraction(double ratio) {
	assert(ratio >= DIV_LIMIT);
	index_ratio = ratio;
}




