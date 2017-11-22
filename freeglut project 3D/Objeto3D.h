#ifndef OBJETO3D_H


#define OBJETO3D_H

#include "PuntoVector3D.h"
#include "world.h"
class Objeto3D {

public:
	Objeto3D(){};
	~Objeto3D(){};
	PuntoVector3D pos;
	PuntoVector3D vel;
	PuntoVector3D acc;
	PuntoVector3D color;
	GLfloat vida;

	virtual void dibuja() {}
	virtual void update(GLfloat dt) {};


	void setPos(PuntoVector3D aux){pos = aux;}
	void setVel(PuntoVector3D aux){vel = aux;}
	virtual void setSize(int tam){};
	void aplicarFuerza(PuntoVector3D aux) { acc.sumar(&aux); }
	void setWorld(World* worlde) { world = worlde; }
	GLfloat getVidaAct() { return vidaAct; };

	void setColor(PuntoVector3D aux){color = aux;}
	World* world;
	
	bool getActive() { return _activa; }
	bool getDestroy() { return _eliminar; }

	void setActive(bool b) { _activa = b; }
	void setDestroy(bool b) { _eliminar = b; }

	bool operator==(const Objeto3D & obj) {
		return this==&obj;
	}

	virtual void reiniciar(){};
	GLfloat vidaAct;

protected:
	int size;
	bool _activa = true;
	bool _eliminar = false;
};
#endif


