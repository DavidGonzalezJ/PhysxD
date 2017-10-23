#pragma once
#include "world.h"
#include "PuntoVector3D.h"

class Objeto3D {

public:
	Objeto3D();
	~Objeto3D();
	world * world_;
protected:
	PuntoVector3D pos;
	PuntoVector3D vel;
	PuntoVector3D color;
};

