#pragma once
#include <vector>
#include "particulas.h"
#include "world.h"

class Test0
{
public:
	Test0();
	~Test0();
	void creaParticulas(int num);
	void dibuja();
private:
	Objeto3D* creaParticula();
	GLfloat lastTimeUpdate = 0;
	GLfloat frecuencia = 10;
	World* world_;
	Objeto3D * lluviaP;
	Objeto3D** objetos;
	int numParticulas;

};

