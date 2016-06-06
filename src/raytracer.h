#ifndef __RAYTRACER_H
#define __RAYTRACER_H

#define DIV_LIMIT 0.000001

namespace raytracer {



	class Vector {
		private:
		public:
			double x, y, z;

			Vector();
			Vector(double x, double y, double z);
			Vector(const Vector & v);
			
			static double dot(const Vector & v, const Vector & w);
			double dot() const;
			double dot(const Vector & v) const;

			static Vector cross(const Vector & v, const Vector & w);
			Vector cross(const Vector & v) const;

			void copy(const Vector & v);
			void copy(double x, double y, double z);

			void power(double p);

			void normalize();
			void scale(double s);
			void add(const Vector & v);
			void add(double x, double y, double z);
			void subtract(const Vector & v);
			void subtract(double x, double y, double z);
			void translate(const Vector & v, double s);

			// reflect vector over surface defined by the normal vector
			void reflect(const Vector & normal);

			// alter direction of vector across an interface with a ratio of
			// indexes of refraction defined for a ray traveling in the
			// direction of the normal
			void refract(const Vector & normal, double index_ratio);
	};



	class Ray {
		private:
		public:
			Vector p, v;

			Ray();
			Ray(const Vector & point, const Vector & direction);
			Ray(const Ray & ray);

			//returns vector some distance along the ray (p+dv)
			Vector follow(double distance) const;
	};



	class Body {
		private:
		public:
			virtual bool isRefracting() const = 0;
			virtual double getRefractiveRatio(const Vector & p) const = 0;
			virtual Vector getColor(const Vector & p) const = 0;
			virtual Vector getExteriorColor(const Vector & p) const = 0;
			virtual Vector getNormal(const Vector & p) const = 0;
			virtual double getDistance(const Ray & r) const = 0;
			virtual double getReflectivity(const Vector & p) const = 0;
	};



	class BasicBody : public Body {
		private:
		protected:
			bool refracting;
			double index_ratio;
			double size;
			double reflectivity; // power used in specular reflection approximation.
			Vector position, x_axis, y_axis, z_axis, color, exterior_color;
		public:
			BasicBody();

			// implementing pure-virtual functions of Body
			virtual bool isRefracting() const;
			virtual double getRefractiveRatio(const Vector & p) const;
			virtual Vector getColor(const Vector & p) const;
			virtual Vector getExteriorColor(const Vector & p) const;
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
			virtual void setExteriorColor(const Vector & c);
			virtual void setReflectivity(double index);
			virtual void refractionOff();
			virtual void setRefraction(double index); //interior index over exterior 

	};

	class Sphere : public BasicBody {
		private:
		protected:
			double magnitude;
			double reciprocal;
		public:
			Sphere(double radius);

			virtual void setSize(double radius);

			virtual Vector getNormal(const Vector & p) const;
			virtual double getDistance(const Ray & r) const;
	};



	class Plane : public BasicBody {
		private:
		protected:
		public:
			Plane(const Vector & position, const Vector & normal);

			virtual Vector getNormal(const Vector & p) const;
			virtual double getDistance(const Ray & r) const;
	};

	class CheckeredPlane : public Plane {
		private:
		protected:
			Vector color2;
		public:
			virtual void setColor(const Vector & c);
			virtual void setColors(const Vector & c1, const Vector & c2);
			virtual Vector getColor(const Vector & p) const;
	};


}



#endif
