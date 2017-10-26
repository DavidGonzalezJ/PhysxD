#pragma once
#include "Objeto3D.h"
class particulas : public Objeto3D
{
public:
	particulas(PuntoVector3D pos_, GLfloat gravedad= (-9.81), GLfloat maxVida = 100, GLfloat minVida = 90);
	~particulas();
	virtual	void dibuja();
	virtual void update(GLfloat dt);

	void resetea();
	PuntoVector3D computeForces();
	bool isDead() { return !viva; }
	virtual void setSize(int tam){ size = tam; }
private:

	bool viva = true;
	int segundos_;
	GLfloat gravedad_;
	GLfloat masa = 1;
	PuntoVector3D posInicial;
	bool activa;
};

