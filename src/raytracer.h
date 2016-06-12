#ifndef __RAYTRACER_H
#define __RAYTRACER_H


#include <random>


#define DIV_LIMIT 0.000001
#define ZERO 0.000001
#define ARRAY_SIZE 1000

namespace raytracer {



	class RNG {
		private:
			static RNG * singleton;
			static bool initialized;

			std::mt19937 engine;
			std::uniform_real_distribution<double> uniform;

			RNG();

		public:
			static RNG * get();
			static void init();
			double next();
	};



	class Vector {
		private:
		protected:
		public:
			double x, y, z;

			Vector();
			Vector(double x, double y, double z);
			Vector(const Vector & v);
	
			static void seed();
			static Vector random(double r); // returns a vector in Ball(r)

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

			void project(const Vector & v);
			void unproject(const Vector & v);

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



	class Light {
		private:
		protected:
		public:
			virtual Vector getDirection(const Vector & p) const = 0;
			virtual Vector getColor() const = 0;
			virtual Vector getIntensity(const Vector & p) const = 0;
	};


	
	class BasicLight : public Light {
		private:
			Vector direction, color, intensity;
			bool hasPenumbra;
			double penumbra;
		protected:
		public:
			BasicLight();
			virtual void setDirection(const Vector & p);
			virtual void setPenumbralSize(double d);
			virtual void setColor(const Vector & c);
			virtual void setIntensity(const Vector & i);

			virtual Vector getDirection(const Vector & p) const;
			virtual Vector getColor() const;
			virtual Vector getIntensity(const Vector & p) const;
	};



	class Sky {
		private:
		protected:
		public:
			virtual Vector getColor(const Vector & direction) const = 0;
	};



	class BasicSky {
		private:
			Vector sun, color, up;
			double power;
		protected:
		public:
			virtual Vector getColor(const Vector & direction) const;
	};



	class World {
		private:
			int body_count;
			int light_count;
			Sky *sky;
			Light *lights[ARRAY_SIZE];
			Body *bodies[ARRAY_SIZE];
		protected:
		public:
			World();
			~World();
			World(const World & w);

			void addBody(Body * b);
			void addLight(Light * l);
			void setSky(Sky * s);

			Vector sample(Ray r);
	};



	class Window {
		private:
			bool initialized;
			Vector center, up, down, right, left, origin;
			double width, height, pixel_size, pixels_per_unit;
			int x_count, y_count;
		protected:
			RNG * rng;
		public:
			Window();

			void setFocus(const Vector & p);
			void setOrientation(const Vector & right, const Vector & up);
			void setSize(double width, double height);
			void setResolution(int vertical_pixel_count);

			void init(); //returns true if settings fail

			int getWidth() const;  // in pixels
			int getHeight() const; // in pixels

			Vector getPixel(int x, int y) const; // <0,0> is top left corner
	};



	class Camera : public Window {
		private:
			Vector position;
			bool hasBlur;
			double blur;
		protected:
		public:
			Camera();
			Camera(const Vector & position);
			Camera(const Vector & position, const Vector & focus);

			void setBlur(double b);
			Ray getRay(int x, int y) const; //from position towards pixel <x,y>
	};



	class Tracer {
		private:
		protected:
		public:
	};



	/* ########## Body Classes ########## */



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



	class Cylinder : public BasicBody {
		private:
		protected:
			double magnitude;
			double reciprocal;
		public:
			Cylinder();
			Cylinder(const Vector & p, const Vector & v, double radius);

			virtual void setSize(double radius);
			virtual void setOrientation(const Vector & axis);
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
