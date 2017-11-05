#include "RBody.h"


RBody::RBody() : time(0), pasos(10)
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

void RBody::update(float deltaTime, PuntoVector3D fuerzas = PuntoVector3D(0.0f, 9.81f, 0.0f,0)){
	time += deltaTime;
	delete sumFuerzas;
	sumFuerzas = fuerzas.clonar();

	CalculaPos(deltaTime);
	centroGravedad = pos.clonar();



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