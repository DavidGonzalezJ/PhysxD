#pragma once
#include <math.h>
#include <GL/freeglut.h>

class PuntoVector3D
{
private:
	GLfloat x, y, z;
	int pv;
public:
	PuntoVector3D(GLfloat x, GLfloat y, GLfloat z, int pv);
	PuntoVector3D() :x(0), y(0), z(0), pv(1) {};
	~PuntoVector3D();
	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();
	bool esPunto();
	bool esVector();
	void escalar(GLfloat factor);
	void normalizar();
	void sumar(PuntoVector3D* pv);
	PuntoVector3D* clonar();
	GLfloat productoEscalar(PuntoVector3D* vector);
	PuntoVector3D* productoVectorial(PuntoVector3D* vector);
	PuntoVector3D operator&=(PuntoVector3D vector2) {
		x = vector2.getX(); y = vector2.getY(); z = vector2.getZ();
		return *this;
	}
	void setVector(GLfloat x1, GLfloat y1, GLfloat z1) { x = x1; y = y1; z = z1; }
};

