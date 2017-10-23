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
	PuntoVector3D fuerza = computeForces();
	PuntoVector3D aceleration = PuntoVector3D(fuerza.getX() / masa, fuerza.getY() / masa, fuerza.getZ() / masa,0);
	vel.sumar(&PuntoVector3D(aceleration.getX() * dt, aceleration.getY() * dt, aceleration.getZ() * dt,0));
	pos.sumar(&PuntoVector3D(vel.getX() * dt, vel.getY() * dt, vel.getZ() * dt, 0));
	//std::cout << vel.getY()<<"\n";
	if (pos.getY() <= BOTTOM_DEADZONE) {
		resetea();
	}
	
}
PuntoVector3D particulas::computeForces(){
	return PuntoVector3D(0, masa * GRAVITY, 0, 0);
}
void particulas::resetea(){
	if (pos.getY() <= BOTTOM_DEADZONE) {
		setPos(PuntoVector3D(pos.getX(), world->dameRandom(350,300), pos.getZ(),0));
		segundos_ = glutGet(GLUT_ELAPSED_TIME);
		setVel(PuntoVector3D(0, 0, 0, 0));

	}
}
