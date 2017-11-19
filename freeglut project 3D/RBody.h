#pragma once
#include "Objeto3D.h"
#include "Quaternion.h"
#include <vector>
#include "Lib\MATH3D.H"

class RBody :
	public Objeto3D
{
public:
	RBody(float masa, float tam);
	virtual ~RBody();
	void update(float deltaTime, PuntoVector3D fuerzas = PuntoVector3D(0.0f, 9.81f, 0.0f, 0));
	virtual void dibuja();
private:
	long float time; // tiempo desde que se creo el objeto
	int pasos; // numero de pasos que realiza el metodo de integracion


	PuntoVector3D* velAngular;
	PuntoVector3D* centroGravedad;
	PuntoVector3D* sumFuerzas;
	matrix_3x3* orientation;
	PuntoVector3D* velCM;
	PuntoVector3D* angularMomentum;
	PuntoVector3D* torque;
	matrix_3x3 inverseWorldInertiaTensor;
	matrix_3x3 inverseBodyInertiaTensor;


	PuntoVector3D correctedPos;
	std::vector<std::vector<float>> tensorInercia;
	float masa;
	PuntoVector3D* calculak(PuntoVector3D* x, PuntoVector3D* v, float deltaTime);
	void CalculaPos(float deltaTime);
	void CalculaTensorInercia(float deltaTime);
};

