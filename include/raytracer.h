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
	
			static Vector random(double r); // returns a vector in Ball(r)
			static Vector randunit(); // return random vector of length 1

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
			void scale(const Vector & v);
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
			Body() { }
			virtual ~Body() { }

			//return a pointer to a copy of the body
			virtual Body * clone() const = 0;

			//check whether a body is transparent at a point
			virtual bool isTransparent(const Vector & p) const = 0;
			
			//get the index of refraction of a body
			virtual double getIndex(const Vector & p) const = 0;
			
			//get the percentage of light absorbed by a body per unit of
			//travel through it
			virtual Vector getInteriorColor(const Vector & p) const = 0;
			
			//return surface color at a point
			virtual Vector getColor(const Vector & p) const = 0;
			
			//get a Vector perpendicular to the surface at a point
			//must point to the exterior of the object.
			virtual Vector getNormal(const Vector & p) const = 0;
			
			//find distance to the body (negative if no hit)
			virtual double getDistance(const Ray & r) const = 0;
			
			//percent of light that reflects specularly at a point
			virtual double getReflectivity(const Vector & p) const = 0;
	};



	class Light {
		private:
		protected:
		public:
			Light() { }
			virtual ~Light() { }

			virtual Light * clone() const = 0;

			virtual Vector getDirection(const Vector & p) const = 0;
			virtual Vector getColor() const = 0;
			virtual Vector getIntensity(const Vector & p) const = 0;
	};


	
	class Sky {
		private:
		protected:
		public:
			Sky() { }
			virtual ~Sky() { }

			virtual Sky * clone() const = 0;

			virtual Vector getColor(const Vector & direction) const = 0;
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

			Vector sample(Ray r, int depth = 4);
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

			void setPosition(const Vector & p);
			void setBlur(double b);
			Ray getRay(int x, int y) const; //from position towards pixel <x,y>
	};



	class Image {
		private:
			int width, height;
			Vector ***scanlines;
		public:
			Image();
			Image(int w, int h);
			Image(const Image & image);
			~Image();
			
			void setDims(int width, int height);
			void setPixel(int x, int y, const Vector & color);
			
			void write(const char * filename) const;
	};



	class Tracer {
		private:
			const char * filename;
			Camera * camera;
			World * world;
		protected:
		public:
			Tracer();
			Tracer(const Tracer & t);
			~Tracer();

			World * getWorld();
			Camera * getCamera();

			void render(int anti_alias = 32, int depth = 4);
			void setOutputName(const char * filename);
	};


} //end additions to namespace raytracer



#endif
