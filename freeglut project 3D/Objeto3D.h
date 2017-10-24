#pragma once

#include "PuntoVector3D.h"
#include "world.h"
class Objeto3D {

public:
	Objeto3D(){};
	~Objeto3D(){};
	PuntoVector3D color;
	PuntoVector3D pos;
	PuntoVector3D vel;
	PuntoVector3D acc;
	virtual void dibuja()=0;
	virtual void update(GLfloat dt) {};

	void setPos(PuntoVector3D aux){pos = aux;}
	void setVel(PuntoVector3D aux){vel = aux;}
	void aplicarFuerza(PuntoVector3D aux) { acc.sumar(&aux); }
	void setWorld(world* worlde) { world = worlde; }

	void setColor(PuntoVector3D aux){color = aux;}
	world* world;
protected:
};

