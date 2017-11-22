#pragma once

#include "world.h"
#include "TAfin.h"
class Objeto3D {

public:
	Objeto3D(){
		mt = new TAfin();
		color =  PuntoVector3D(0, 0, 0.5, 0);
	};
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
	TAfin* mt;


protected:
	int size;
	bool _activa = true;
	bool _eliminar = false;
};


