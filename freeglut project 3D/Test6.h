#pragma once
#include <vector>
#include "particulas.h"
#include "world.h"
class Test6
{
public:
	Test6();
	~Test6();
	void dibuja();
private:
	GLfloat lastTimeUpdate = 0;
	GLfloat frecuencia = 10;
	World* world_;
	Objeto3D * fuente;
	Objeto3D** objetos;
	int numParticulas;
};

