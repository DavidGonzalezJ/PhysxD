#include "RBody.h"


RBody::RBody(float masa, float tam) : time(0), pasos(10)
{
	std::vector<float>aux(3);
	for (size_t i = 0; i < 3; i++)
	{
		tensorInercia.push_back(aux);
		for (size_t j = 0; j < 3; j++)
		{
			tensorInercia[i][j] = 1;
		}
	}
}


RBody::~RBody()
{
}

void RBody::CalculaPos(float deltaTime){
	PuntoVector3D *k1, *k2, *k3, *k4;
	PuntoVector3D* aux;
	//Calcular suma de fuerzas que actuan sobre el cuerpo pdte

	k1 = calculak(&pos, &vel, deltaTime);
	aux = k1->clonar();

	aux->mult(0.5);
	aux->sumar(&pos);
	k2 = calculak(aux, &vel, deltaTime * 0.5);
	delete aux;
	aux = k2->clonar();

	aux->mult(0.5);
	aux->sumar(&pos);
	k3 = calculak(aux, &vel, deltaTime * 0.5);
	delete aux;
	aux = k3->clonar();

	aux->sumar(&pos);
	k4 = calculak(aux, &vel, deltaTime);
	delete aux;

	k1->mult(1.0 / 6.0);
	k2->mult(1.0 / 3.0);
	k3->mult(1.0 / 3.0);
	k4->mult(1.0 / 6.0);

	pos.sumar(k1);	pos.sumar(k2); pos.sumar(k3); pos.sumar(k4);
}

void RBody::CalculaTensorInercia(float deltaTime){
	float   Ixx, Iyy, Izz, Ixy, Ixz, Iyz;
	Ixx = 0;  Iyy = 0;  Izz = 0;
	Ixy = 0;  Ixz = 0;  Iyz = 0;
	//for (i = 0; i<_NUMELEMENTS; i++)
	//{
	Ixx += 1 + masa * correctedPos.getY() * correctedPos.getY() + correctedPos.getZ() *correctedPos.getZ();
	Iyy += 1 + masa * correctedPos.getZ() * correctedPos.getZ() + correctedPos.getX() *correctedPos.getX();
	Izz += 1 + masa * correctedPos.getX() * correctedPos.getX() + correctedPos.getY() *correctedPos.getY();
	Ixy += masa * correctedPos.getX() *correctedPos.getY();
	Ixz += masa * correctedPos.getX() *correctedPos.getZ();
	Iyz += masa * correctedPos.getY() *correctedPos.getX();
	//}
	// e11 stands for element on row 1 column 1, e12 for row 1 column 2, etc.
	tensorInercia[0][0] = Ixx;
	tensorInercia[0][1] = -Ixy;
	tensorInercia[0][2] = -Ixz;
	tensorInercia[1][0] = -Ixy;
	tensorInercia[1][1] = Iyy;
	tensorInercia[1][2] = -Iyz;
	tensorInercia[2][0] = -Ixz;
	tensorInercia[2][1] = -Iyz;
	tensorInercia[2][2] = Izz;
}

void RBody::update(float deltaTime, PuntoVector3D fuerzas = PuntoVector3D(0.0f, 9.81f, 0.0f,0)){
	time += deltaTime;
	delete sumFuerzas;
	sumFuerzas = fuerzas.clonar();

	fuerzas.mult(deltaTime);
	vel.sumar(&fuerzas);

	CalculaPos(deltaTime);
	centroGravedad = pos.clonar(); // pendiente de meter objetos dependientes dentro del rigid body para darle formas complejas
	correctedPos = *(pos.clonar());

	PuntoVector3D* aux = centroGravedad->clonar();
	aux->escalar(-1);
	correctedPos.sumar(aux);
	delete aux;

	CalculaTensorInercia(deltaTime);
}

PuntoVector3D* RBody::calculak(PuntoVector3D* x, PuntoVector3D* v, float deltaTime){
	PuntoVector3D *aux;
	PuntoVector3D *aux2;
	PuntoVector3D *aux3;

	aux = sumFuerzas->clonar();
	aux3 = v->clonar();
	aux2 = x->clonar();

	aux->mult((deltaTime*deltaTime) / 2);
	aux3->mult(deltaTime);

	aux2->sumar(aux); aux2->sumar(aux3);

	delete aux; delete aux3;
	return aux;
}