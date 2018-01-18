#pragma once
#include "RigidBody.h"
#include <vector>
#include "Malla.h"
#include "Objeto3D.h"
#include "Explosion.h"
#include "world.h"
#include "Test3.h"
#include "Fuego.h"
#include "Fuego2.h"

class Test7
{
public:
	Test7();
	~Test7();
	virtual void dibuja();
	void lanzaProyectil();
	void apagaFuego();
	PuntoVector3D* C(GLfloat t);
	PuntoVector3D* C’(GLfloat t);
	PuntoVector3D* C’’(GLfloat t);
	
private:
	GLfloat a, b,c,d,t;
	std::vector<RigidBody*> ejericito;
	GLfloat lastTimeUpdate = 0;
	GLfloat frecuencia = 20;
	GLfloat updateF;
	GLfloat frecF = 480;

	Malla kekubo;
	Malla terreno;
	Objeto3D* _explosion;
	World* world_;
	Test3* explosionn;
	PuntoVector3D* posAvion;
	std::vector<Fuego*> fuego;
	Fuego2 * estela;
	bool caida = false;
	
};


