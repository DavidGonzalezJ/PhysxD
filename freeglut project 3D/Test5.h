#pragma once
#include <vector>
#include "world.h"
#include "RBody.h"

class Test5
{
public:
	Test5();
	~Test5();
	void creaParticulas(int num);
	void dibuja();
private:
	Objeto3D* creaParticula();
	GLfloat lastTimeUpdate = 0;
	GLfloat frecuencia = 10;
	World* world_;
	Objeto3D * rb;
	Objeto3D** objetos;
	int numParticulas;

};


