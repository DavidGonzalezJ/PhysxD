#pragma once
#include "Objeto3D.h"
class particulas : public Objeto3D
{
public:
	particulas(PuntoVector3D pos_, GLfloat gravedad= (-9.81));
	~particulas();
	virtual	void dibuja();
	virtual void update(GLfloat dt);

	void resetea();
	PuntoVector3D computeForces();
	bool isDead() { return !viva; }
private:

	bool viva = true;
	int segundos_;
	GLfloat gravedad_;
	GLfloat masa = 1;
	PuntoVector3D posInicial;
	bool activa;
};

