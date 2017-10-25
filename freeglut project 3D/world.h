#pragma once
#include "PuntoVector3D.h"
#define GRAVITY -9.81f
class World 
{
public:
	World() { gravity = PuntoVector3D(0, GRAVITY, 0, 1); };
	~World() {};
	virtual PuntoVector3D getGravity(){ return gravity; };
	virtual PuntoVector3D getWorldBox(){ return worldBox; };
	GLfloat dameRandom(GLfloat max, GLfloat min) {
		return min + static_cast <GLfloat> (rand()) / (static_cast <GLfloat> (RAND_MAX / (max - min)));
	}
	//vector<Objeto3D> getObjects(){ return objetos; };
private:
	PuntoVector3D gravity;
	PuntoVector3D worldBox;
};

