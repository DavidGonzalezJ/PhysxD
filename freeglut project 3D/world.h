#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Objeto3D.h"
#include <vector>

class world
{
public:
	world();
	~world();
	GLfloat getGravity(){ return gravity; };
	PuntoVector3D getWorldBox(){ return worldBox; };
	//vector<Objeto3D> getObjects(){ return objetos; };
private:
	GLfloat gravity = -9.81;
	PuntoVector3D worldBox;
	std::vector<Objeto3D> objetos;
};

