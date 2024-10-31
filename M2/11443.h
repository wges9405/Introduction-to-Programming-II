#ifndef SHAPE_H
#define SHAPE_H

namespace oj
{
class Shape3D
	{
		double volume;

	public:
		double getVolume();

	protected:
		void setVolume(double volume);
	};

class Sphere : public Shape3D
	{
		double radius;
		double pi;

	public:
		Sphere(double, double);
	};

class Cone : public Shape3D
	{
		double radius;
		double height;
		double pi;

	public:
		Cone(double, double, double);
	};

class Cuboid : public Shape3D
	{
		double length;
		double width;
		double height;

	public:
		Cuboid(double, double, double);
	};

class Cube : public Cuboid
	{
	public:
		Cube(double);
	};
}
oj::Sphere::Sphere(double r, double p) {
	double v;
    if (r<0 || p<0)  v = 0;
    else v = (double) 4.0/3.0*p*r*r*r;
    setVolume(v);
}
oj::Cone::Cone(double r, double h, double p) {
	double v;
    if (h<0 || r<0 || p<0) v = 0;
    else v = (double) 1.0/3.0*p*r*r*h;
    setVolume(v);
}
oj::Cuboid::Cuboid(double l, double w, double h) {
	double v;
    if (l<0 || w<0 || h<0) v = 0;
    else v = (double) l*w*h;
    setVolume(v);
}
oj::Cube::Cube(double a) : Cuboid(a, a, a) {}

#endif
