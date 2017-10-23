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
protected:
	world* world;
};

