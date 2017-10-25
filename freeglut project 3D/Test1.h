#pragma once
#include <vector>
#include "particulas.h"
#include "world.h"

class Test1
{
public:
	Test1();
	~Test1();
	void creaParticulas(int num);
	void dibuja();
private:
	Objeto3D* creaParticula();
	GLfloat lastTimeUpdate = 0;
	GLfloat frecuencia = 10;
	World* world_;
	Objeto3D * fuente;
	Objeto3D** objetos;
	int numParticulas;
	
};

