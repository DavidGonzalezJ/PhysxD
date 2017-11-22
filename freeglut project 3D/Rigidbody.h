#pragma once
#include "Objeto3D.h"
#include "Cubo.h"

class Rigidbody: public Objeto3D
{
public:
	Rigidbody(PuntoVector3D pos_, GLfloat gravedad = (-9.81));
	~Rigidbody();
	virtual	void dibuja();
	virtual void update(GLfloat dt);

	void resetea();
	PuntoVector3D computeForces();
	virtual void setSize(int tam){ size = tam; }
private:
	Objeto3D* cubo;
	int segundos_;
	GLfloat gravedad_;
	GLfloat masa = 1;
	PuntoVector3D posInicial;
	bool activa;
};

