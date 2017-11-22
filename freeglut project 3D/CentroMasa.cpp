#include "CentroMasa.h"


CentroMasa::CentroMasa(Objeto3D* rb, PuntoVector3D posicion) :rigidBody(rb)
{
}


CentroMasa::~CentroMasa()
{
}

void CentroMasa::giraRB(){
	PuntoVector3D aux = { 1, 1, 1, 0 };
	rigidBody->mt->rota(&aux,50);
}

void CentroMasa::posicionaRB(){
	rigidBody->mt[12] = this->mt[12];
	rigidBody->mt[13] = this->mt[13];
	rigidBody->mt[14] = this->mt[14];
}

void CentroMasa::update(){
	/*dt -= segundos_;
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
	}*/
}
