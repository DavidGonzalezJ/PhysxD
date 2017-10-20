#pragma once
#include "PuntoVector3D.h"
class esfera
{
public:
	esfera(int radio, int meridiano, int paralelo);
	~esfera();
	void dibuja();
	void update();
	void setPos(PuntoVector3D aux);
	void setDir(PuntoVector3D aux);
	void setAce(PuntoVector3D aux);
	PuntoVector3D pos;
	PuntoVector3D dir;
	PuntoVector3D ace;
private:
	int radio_, meridiano_, paralelo_;
};

