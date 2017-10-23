#include "particulas.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>

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
	glutSolidSphere(radio_, meridiano_, paralelo_);

}

void particulas::setPos(PuntoVector3D aux)
{
	pos = aux;
}

void particulas::setVel(PuntoVector3D aux)
{
	vel = aux;
}


void particulas::setColor(PuntoVector3D aux)
{
	color = aux;
}
void particulas::update(GLfloat dt) {
	dt -= segundos_;
	dt /= 1000;
	PuntoVector3D fuerza = computeForces();
	PuntoVector3D aceleration = PuntoVector3D(fuerza.getX() / masa, fuerza.getY() / masa, fuerza.getZ() / masa,0);
	vel.sumar(&PuntoVector3D(aceleration.getX() * dt, aceleration.getY() * dt, aceleration.getZ() * dt,0));
	pos.sumar(&PuntoVector3D(vel.getX() * dt, vel.getY() * dt, vel.getZ() * dt, 0));
	if (pos.getY() <= BOTTOM_DEADZONE) {
		resetea();
	}
	
}
PuntoVector3D particulas::computeForces(){
	return PuntoVector3D(0, masa * GRAVITY, 0, 0);
}
void particulas::resetea(){
	if (pos.getY() <= BOTTOM_DEADZONE) {
		setPos(posInicial);
		segundos_ = glutGet(GLUT_ELAPSED_TIME);
		setVel(PuntoVector3D(0, 0, 0, 0));

	}
}
