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
			static Vector cross(const Vector & v, const Vector & w);

			void copy(const Vector & v);

			void normalize();
			void scale(double s);
			void add(const Vector & v);
			void add(double x, double y, double z);
			void subtract(const Vector & v);
			void subtract(double x, double y, double z);
			void translate(const Vector & v, double s);
	};

	class Ray {
		private:
		public:
	};

	class Body {
		private:
		public:
	};
}

#endif
