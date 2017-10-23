#pragma once
#include "Objeto3D.h"
class particulas : public Objeto3D
{
public: 
	particulas(int radio, int meridiano, int paralelo, PuntoVector3D pos_);
	~particulas();
	void dibuja();
	void update(GLfloat dt);
	void setPos(PuntoVector3D aux);
	void setVel(PuntoVector3D aux);
	void setColor(PuntoVector3D aux);
	void resetea();
	PuntoVector3D computeForces();
	
private:
	int radio_, meridiano_, paralelo_, segundos_;
	GLfloat masa=1;
	PuntoVector3D posInicial;
};

