#include "particulas.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>

#define TOP_DEADZONE 200
#define GRAVITY -9.81
#define BOTTOM_DEADZONE 0

particulas::particulas(int radio, int meridiano, int paralelo, PuntoVector3D pos_)
{
	pos = pos_;
	posInicial = pos;
	radio_ = radio;
	meridiano_ = meridiano;
	paralelo_ = paralelo;
	acc = PuntoVector3D(0,0, 0, 1);
	segundos_ = glutGet(GLUT_ELAPSED_TIME);
}


particulas::~particulas()
{
}
void particulas::dibuja() {
	if (activa) {
		glPushMatrix();
		glTranslated(pos.getX(), pos.getY(), pos.getZ());
		glColor3f(color.getX(), color.getY(), color.getZ());
		glutSolidSphere(radio_, meridiano_, paralelo_);
		glPopMatrix();
	}
}


void particulas::update(GLfloat dt) {
	dt -= segundos_;
	dt /= 10000;
	PuntoVector3D aceleration = computeForces();
	aceleration.mult(dt);
	vel.sumar(&aceleration);
	PuntoVector3D Velocidad(vel);
	Velocidad.mult(dt);
	pos.sumar(&Velocidad);
	//std::cout << vel.getY()<<"\n";
	acc.mult(0);
	vel.mult(0);
	if (pos.getY() <= BOTTOM_DEADZONE) {
		resetea();
	}
	
}
PuntoVector3D particulas::computeForces(){
	acc.sumar(&world->getGravity());
	return acc;
}
void particulas::resetea(){
	if (pos.getY() <= BOTTOM_DEADZONE) {
		setPos(PuntoVector3D(pos.getX(), world->dameRandom(350,300), pos.getZ(),0));
		segundos_ = glutGet(GLUT_ELAPSED_TIME);
		setVel(PuntoVector3D(0, 0, 0, 0));

	}
}
