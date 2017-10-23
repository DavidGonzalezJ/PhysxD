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
	GLfloat lastTimeUpdate = 0;
	GLfloat frecuencia = 10;
	world* world_;
	Objeto3D** objetos;
	int numParticulas;
	
};

