﻿#include "particulas.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>

#define TOP_DEADZONE 200
#define BOTTOM_DEADZONE 0

particulas::particulas(PuntoVector3D pos_, GLfloat gravedad, GLfloat maxVida, GLfloat minVida)
{
	pos = pos_;
	posInicial = pos;
	acc = PuntoVector3D(0,0, 0, 1);
	segundos_ = glutGet(GLUT_ELAPSED_TIME);
	vida = world->dameRandom(maxVida, minVida);
	vidaAct = vida;
	gravedad_ = gravedad;
	size = 1;
}


particulas::~particulas()
{
}
void particulas::dibuja() {
	if (activa) {
		glPushMatrix();
		
		glTranslated(pos.getX(), pos.getY(), pos.getZ());
		glColor4f(color.getX(), color.getY(), color.getZ(),color.getA() );
		glutSolidSphere(size,3,3);
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
	acc.mult(0);
	vidaAct --;
	if (pos.getY() <= BOTTOM_DEADZONE || pos.getY() >= TOP_DEADZONE || vidaAct <= 0) {
		//resetea();
		setDestroy(true);
	}
	
}
PuntoVector3D particulas::computeForces(){
	acc.sumar(&PuntoVector3D(0,gravedad_,0,0));
	return acc;
}
void particulas::resetea(){
	if (pos.getY() <= BOTTOM_DEADZONE) {
		setPos(PuntoVector3D(pos.getX(), world->dameRandom(350,300), pos.getZ(),0));
		segundos_ = glutGet(GLUT_ELAPSED_TIME);
		setVel(PuntoVector3D(0, 0, 0, 0));

	}
}
