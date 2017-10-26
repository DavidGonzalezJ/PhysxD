#pragma once
#include <vector>
#include "particulas.h"
#include "world.h"

class Test3
{
public:
	Test3();
	~Test3();
	void creaParticulas(int num);
	void dibuja();
private:
	Objeto3D* creaParticula();
	GLfloat lastTimeUpdate = 0;
	GLfloat frecuencia = 10;
	World* world_;
	Objeto3D * _explosion;
	Objeto3D** objetos;
	int numParticulas;

};


