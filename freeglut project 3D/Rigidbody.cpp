#include "Rigidbody.h"
#define BOTTOM_DEADZONE 0
#define TOP_DEADZONE 800

Rigidbody::Rigidbody(PuntoVector3D pos_, GLfloat gravedad)
{
	pos = pos_;
	posInicial = pos;
	acc = PuntoVector3D(0, 0, 0, 1);
	segundos_ = glutGet(GLUT_ELAPSED_TIME);

	gravedad_ = gravedad;
	size = 1;
	cubo = new Cubo(10);
	cubo->setColor(PuntoVector3D(1, 1, 1, 0));
}


Rigidbody::~Rigidbody()
{
}
void Rigidbody::dibuja() {

		glPushMatrix();

		
		glColor4f(color.getX(), color.getY(), color.getZ(), 1);
		cubo->dibuja();
		glPopMatrix();

}
void Rigidbody::update(GLfloat dt) {
	dt -= segundos_;
	dt /= 1000000;



	PuntoVector3D aceleration = computeForces();

	aceleration.mult(dt);
	vel.sumar(&aceleration);
	PuntoVector3D Velocidad(vel);
	Velocidad.mult(dt);
	pos.sumar(&Velocidad);
	acc.mult(0);
	cubo->mt->reinicia();
	cubo->mt->traslada(&pos);
	
	if (cubo->mt->damePos().getY() <= BOTTOM_DEADZONE || cubo->mt->damePos().getY() >= TOP_DEADZONE) {
	
		setDestroy(true);
	}
}

	PuntoVector3D Rigidbody::computeForces(){
		acc.sumar(&PuntoVector3D(0, gravedad_, 0, 0));
		return acc;
	}
