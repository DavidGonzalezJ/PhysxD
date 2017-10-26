#pragma once
#include <vector>
#include "Objeto3D.h"
#include "particulas.h"
class FireWork :
	public Objeto3D
{
public:
	FireWork();
	virtual ~FireWork();
	virtual void dibuja(){
		cohete->dibuja();
	}
	virtual void update(GLfloat dt);

	virtual void reiniciar(){
		delete cohete;
		cohete = new particulas(PuntoVector3D(0, 1, 0,1));
		cohete->setVel(PuntoVector3D(0, 50, 0, 1));
		cohete->setWorld(world);
		estadoCohete = LANZADO;
		vidaAct = 1;

	}
	bool Ended(){
		return estadoCohete == TERMINADO;
	}
	enum ENUM_ESTADO
	{
		LANZADO, EXPLOTADO, TERMINADO
	};
private:
	ENUM_ESTADO estadoCohete;
	
	Objeto3D * cohete;
};

