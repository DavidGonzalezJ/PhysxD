#include "RBody.h"
#include <iostream>

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

	inverseBodyInertiaTensor = matrix_3x3();
	inverseWorldInertiaTensor = matrix_3x3();
	velAngular = new PuntoVector3D();
	sumFuerzas = new PuntoVector3D();
	centroGravedad = new PuntoVector3D();
	velCM = new PuntoVector3D();
	angularMomentum = new PuntoVector3D();
	torque = new PuntoVector3D();

	pos.setY(200);

	tam_ = tam;
	modo = true;

	numeroVertices = 8;
	vertice = new PuntoVector3D*[numeroVertices];
	numeroNormales = 6;
	normal = new PuntoVector3D*[numeroNormales];
	numeroCaras = 6;
	cara = new Cara*[numeroCaras];


	// Vértices  
	vertice[0] = new PuntoVector3D(-tam_ / 2, -tam_ / 2, tam_ / 2, 1);
	vertice[1] = new PuntoVector3D(tam_ / 2, -tam_ / 2, tam_ / 2, 1);
	vertice[2] = new PuntoVector3D(tam_ / 2, tam_ / 2, tam_ / 2, 1);
	vertice[3] = new PuntoVector3D(-tam_ / 2, tam_ / 2, tam_ / 2, 1);

	vertice[4] = new PuntoVector3D(-tam_ / 2, -tam_ / 2, -tam_ / 2, 1);
	vertice[5] = new PuntoVector3D(tam_ / 2, -tam_ / 2, -tam_ / 2, 1);
	vertice[6] = new PuntoVector3D(tam_ / 2, tam_ / 2, -tam_ / 2, 1);
	vertice[7] = new PuntoVector3D(-tam_ / 2, tam_ / 2, -tam_ / 2, 1);

	// Normales  
	normal[0] = new PuntoVector3D(0.0f, 0.0f, 1.0f, 0);
	normal[1] = new PuntoVector3D(1.0f, 0.0f, 0.0f, 0);
	normal[2] = new PuntoVector3D(0.0f, 0.0f, -1.0f, 0);
	normal[3] = new PuntoVector3D(-1.0f, 0.0f, 0.0f, 0);
	normal[4] = new PuntoVector3D(0.0f, 1.0f, 0.0f, 0);
	normal[5] = new PuntoVector3D(0.0f, -1.0f, 0.0f, 0);

	// Caras
	VerticeNormal** aVN = new VerticeNormal*[4];
	aVN[0] = new VerticeNormal(0, 0);
	aVN[1] = new VerticeNormal(1, 0);
	aVN[2] = new VerticeNormal(2, 0);
	aVN[3] = new VerticeNormal(3, 0);
	cara[0] = new Cara(4, aVN);

	aVN = new VerticeNormal*[4];
	aVN[0] = new VerticeNormal(1, 1);
	aVN[1] = new VerticeNormal(5, 1);
	aVN[2] = new VerticeNormal(6, 1);
	aVN[3] = new VerticeNormal(2, 1);
	cara[1] = new Cara(4, aVN);

	aVN = new VerticeNormal*[4];
	aVN[0] = new VerticeNormal(5, 2);
	aVN[1] = new VerticeNormal(4, 2);
	aVN[2] = new VerticeNormal(7, 2);
	aVN[3] = new VerticeNormal(6, 2);
	cara[2] = new Cara(4, aVN);

	aVN = new VerticeNormal*[4];
	aVN[0] = new VerticeNormal(4, 3);
	aVN[1] = new VerticeNormal(0, 3);
	aVN[2] = new VerticeNormal(3, 3);
	aVN[3] = new VerticeNormal(7, 3);
	cara[3] = new Cara(4, aVN);

	aVN = new VerticeNormal*[4];
	aVN[0] = new VerticeNormal(2, 4);
	aVN[1] = new VerticeNormal(6, 4);
	aVN[2] = new VerticeNormal(7, 4);
	aVN[3] = new VerticeNormal(3, 4);
	cara[4] = new Cara(4, aVN);

	aVN = new VerticeNormal*[4];
	aVN[0] = new VerticeNormal(0, 5);
	aVN[1] = new VerticeNormal(1, 5);
	aVN[2] = new VerticeNormal(5, 5);
	aVN[3] = new VerticeNormal(4, 5);
	cara[5] = new Cara(4, aVN);

	orientation = new matrix_3x3();

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

void RBody::update(float deltaTime, PuntoVector3D fuerzas){
	time += deltaTime;
	//delete sumFuerzas;
	sumFuerzas = fuerzas.clonar();

	PuntoVector3D* aux = vel.clonar();

	//Actualiza posicion
	sumFuerzas->escalar(time);
	pos.sumar(sumFuerzas);
	//delete aux;

	//Actualiza orientacion
	// Velocidad angular es 0 no podemos aplicar fuerzas directamenteasi que no hay necesidad de modificarla.
	vector_3 a(velAngular->getX(), velAngular->getY(), velAngular->getZ());
	orientation->operator+=(deltaTime *
		matrix_3x3(a, matrix_3x3::SkewSymmetric) *
		*(orientation));
	OrthonormalizeOrientation(*orientation);

	//Actualiza velocidad de centro de masas
	//sumFuerzas->escalar(deltaTime*(1 / masa));
	velCM->setVector(velCM->getX() + deltaTime*(1 / masa)*sumFuerzas->getX(),
		velCM->getY() + deltaTime*(1 / masa)*sumFuerzas->getY(),
		velCM->getZ() + deltaTime*(1 / masa)*sumFuerzas->getZ());

	//Actualiza momento angular
	// El torque vale 0, si quisieramos actualizarlo para poder aplicar mas fuerzas que la gravedad habría que calcularlo antes de todo, y el metodo deberia recibir un vector
	//con todas las fuerzas para calcular el torque
	angularMomentum->setVector(angularMomentum->getX() + deltaTime * torque->getX(), angularMomentum->getY() + deltaTime * torque->getY(), angularMomentum->getZ()+ deltaTime * torque->getZ());

	CalculaTensorInercia(deltaTime);

	// compute auxiliary quantities

	inverseWorldInertiaTensor = *orientation * inverseBodyInertiaTensor * Transpose(*orientation);

	vector_3 auxAng;
	auxAng = inverseWorldInertiaTensor * vector_3(angularMomentum->getX(),angularMomentum->getY(), angularMomentum->getZ());
	velAngular = new PuntoVector3D(auxAng.GetX(), auxAng.GetY(), auxAng.GetZ(),0);

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

void RBody::dibuja(){
	// Cargamos la matriz afin
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	float m[16];

	m[0] = orientation->GetElement(0,0);
	m[1] = orientation->GetElement(1, 0);
	m[2] = orientation->GetElement(2, 0);
	m[3] = 0;
	m[4] = orientation->GetElement(0, 1);
	m[5] = orientation->GetElement(1, 1);
	m[6] = orientation->GetElement(2, 1);
	m[7] = 0;
	m[8] = orientation->GetElement(0, 2);
	m[9] = orientation->GetElement(1, 2);
	m[10] = orientation->GetElement(2, 2);
	m[11] = 0;
	m[12] = pos.getX();
	m[13] = pos.getY();
	m[14] = pos.getZ();
	m[15] = 1;

	CreateOpenGLTransform(orientation, CM, m);
	std::cout << pos.getX() << " " <<  pos.getY() << " " << pos.getZ() << "\n";
/*	glPushMatrix();
	glMultMatrixf(m);*/
	// Dibujamos la malla
	for (int i = 0; i<numeroCaras; i++) {
		if (modo) glBegin(GL_POLYGON);
		else glBegin(GL_LINE_LOOP);
		for (int j = 0; j<cara[i]->getNumeroVertices(); j++) {

			int iN = cara[i]->getIndiceNormalK(j);
			int iV = cara[i]->getIndiceVerticeK(j);
			glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
			glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
			
		}
		glEnd();
	}
	glPopMatrix();
	//glPopMatrix();
}