#pragma once
#include "RigidBody.h"
#include <vector>
class Test7
{
public:
	Test7();
	~Test7();
	virtual void dibuja();
private:
	std::vector<RigidBody*> ejericito;
	GLfloat lastTimeUpdate = 0;
	GLfloat frecuencia = 20;
};

