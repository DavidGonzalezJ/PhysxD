#pragma once
#include <vector>
#include "particulas.h"
#include "world.h"

class Test4
{
public:
	Test4();
	~Test4();
	void creaParticulas(int num);
	void dibuja();
private:
	Objeto3D* creaParticula();
	GLfloat lastTimeUpdate = 0;
	GLfloat frecuencia = 10;
	World* world_;
	Objeto3D * _explosion, *fireworks;
	Objeto3D** objetos;
	int numParticulas;
	bool done;
	PuntoVector3D posAux;

};


