#pragma once
#include <vector>
#include "particulas.h"
#include "world.h"
class Test5
{
public:
	Test5();
	~Test5();
	void dibuja();
private:
	
	GLfloat lastTimeUpdate = 0;
	GLfloat frecuencia = 10;
	World* world_;
	Objeto3D * fuente;
	Objeto3D** objetos;
	int numParticulas;
};

