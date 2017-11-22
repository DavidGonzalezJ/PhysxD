#pragma once
#include "Objeto3D.h"
class CentroMasa :
	public Objeto3D
{
public:
	CentroMasa(Objeto3D* rb, PuntoVector3D posicion);
	~CentroMasa();
	Objeto3D* rigidBody;
	void giraRB();
	void posicionaRB();
	virtual void update();
};

