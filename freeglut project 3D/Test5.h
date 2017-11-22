#pragma once
#include "world.h"
#include "RBody.h"
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
	RBody* cubo;
};

