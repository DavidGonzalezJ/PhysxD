#pragma once
#include "PuntoVector3D.h"

class world 
{
public:
	world();
	~world();
	virtual GLfloat getGravity(){ return gravity; };
	virtual PuntoVector3D getWorldBox(){ return worldBox; };
	//vector<Objeto3D> getObjects(){ return objetos; };
private:
	GLfloat gravity = -9.81;
	PuntoVector3D worldBox;
};

