#pragma once
#include "TAfin.h"
#include "MATH3D.H"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>

class RigidBody
{
public:
	RigidBody(float x, float y, float z,GLfloat masa):mass(masa) {
		timer =0;
		pos = { x,y,z };
		mT = new TAfin();
		mT->traslada({ x,y,z,0 });
	}
	virtual void Update(float dt) {
		//TODO
		dt = 1.0f / 120.0f;
		Fuerza += peso;
	
		updateLinearMomentum(dt);

		updateVelocity();
		updatePosition(dt);
		updateInertia();
		updateAngularVelocity();
		updateRotationQuaternion(dt);

		rotMat = glm::mat4_cast(orie);
		cubeMatrix = glm::mat4(1.0f); //reinicia la matriu de transformacio
		cubeMatrix = glm::translate(cubeMatrix, pos) * rotMat; //translation + rotation
		
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				mT->m[4 * i + j] = cubeMatrix[i][j];
			}

		}
		timer += dt;
		Fuerza *= 0;
		
	}
	virtual void applyForce(glm::vec3 fuerza) {
		Fuerza += fuerza;
		
	}
	virtual void setForce(glm::vec3 fuerza, float dt, glm::vec3 posFuerza = {0,0,0}) {
		Fuerza += fuerza;
		if (posFuerza.x == 0 && posFuerza.y == 0 && posFuerza.z == 0)
			posFuerza = pos;
		glm::vec3 dist = posFuerza - pos;
		//TORQUE con respecto a la fuerza
		glm::vec3 aux = { dist.y * fuerza.z - dist.z * fuerza.y, -dist.x*fuerza.z + dist.z*fuerza.x, dist.x*fuerza.y - dist.y* fuerza.x };
		//Se le suma al inicial
		torque += aux;
		angMom = angMom + (dt * torque);
	}
	virtual void setTorque(glm::vec3 angulag, float dt) {
		torque += angulag;
		angMom = angMom + (dt * torque);
	}
	~RigidBody() {

	};
	virtual void Render() = 0;
	TAfin * mT;
protected:
	glm::mat4 cubeMatrix;//Matriu transposada
	float timer = 0;
	float mass = 1;
	glm::mat3 iBody = { (mass * 2) / 12, 0, 0,
		0, (mass * 2) / 12, 0,
		0, 0, (mass * 2) / 12 };
	//Cosas chungas de Wizu
	glm::vec3 torque;
	glm::mat4 rotMat;
	glm::vec3 pos = { 0, 0, 0 };//Position vector (x)
	glm::vec3 lVel;//Linear Velocity (v)
	glm::vec3 aVel; //Angular velocity (w)
	glm::quat orie;//Quaternion orientation (R)
	glm::vec3 linMom;//Linear Momentum (P)
	glm::vec3 angMom;//Angular Momentum (L)
	glm::mat3 inertia; //(I)
	glm::vec3 peso = {0,-9.81*mass,0};
	glm::vec3 Fuerza;
	void updateLinearMomentum(float dt) {
		linMom = linMom + (dt * Fuerza);
	}

	void updateAngularMomentum(float dt, float t[3]) {
		angMom = angMom + (dt * torque);
	}

	void updateVelocity() {
		lVel = linMom / mass;
	}

	void updatePosition(float dt) {
		pos = pos + (dt * lVel);
		if (pos[1] <= 0) pos[1] = 0;
	}

	void updateInertia() {
		glm::mat3 rot = glm::mat3_cast(orie);
		inertia = rot * iBody * glm::transpose(rot);
	}

	void updateAngularVelocity() {
		aVel = glm::inverse(inertia) * angMom;
	}

	void updateRotationQuaternion(float dt) {//Aquesta funció va amb quaternions
		glm::quat velAng = glm::quat(0.f, aVel);
		orie = glm::normalize(orie + 0.5f * dt * velAng*orie);
	}



	

};

class TeteraRigida: public RigidBody
{
public:
	TeteraRigida(float x, float y, float z, GLfloat masa):RigidBody(x, y, z, masa){

	};
	~TeteraRigida() {

	}
	virtual void Render() {
		glPushMatrix();
		glMultMatrixf(mT->m);
		//glutSolidTeapot(5);
		glutSolidCube(5);
		glPopMatrix();
	}

private:

};

//A falta de ajustar el torque
class Cono : public RigidBody
{
public:
	Cono(float x, float y, float z, GLfloat masa,GLfloat altura,GLfloat radio) :RigidBody(x, y, z, masa),h(altura),r(radio) {
		iBody = { (3*(mass * std::pow(altura,2)/*Altura al cuadrado*/) / 5)+ 3 * (mass * std::pow(radio/*radio*/,2))/20, 0, 0,
			0, (3 * (mass * std::pow(altura,2)/*Altura al cuadrado*/) / 5) + 3 * (mass * std::pow(radio/*radio*/,2)) / 20, 0,
			0, 0, 3 * (mass * std::pow(radio/*radio*/,2)) / 10 };
		pos = { x,y,z-h/4 };
		/*this->mT->rota(&PuntoVector3D(0, 0, 1, 0), 90);*/
	};
	~Cono() {

	}
	virtual void Render() {
		glPushMatrix();
		glMultMatrixf(mT->m);
		glutSolidCone(h, r, 20, 20);
		glPopMatrix();
	}

private:
	GLfloat h, r;
};

class Cilindro : public RigidBody
{
public:
	Cilindro(float x, float y, float z, GLfloat masa, GLfloat altura, GLfloat radio) :RigidBody(x, y, z, masa), h(altura), r(radio) {
		iBody = { (1/12)*masa*(3*pow(radio,2)+pow(h,2)), 0, 0,
			0, (1 / 12)*masa*(3 * pow(radio,2) + pow(h,2)), 0,
			0, 0, (1 / 2)*masa*pow(radio,2) };
		pos = { x,y+h/2,z};
	};
	~Cilindro() {

	}
	virtual void Render() {
		glPushMatrix();
		glMultMatrixf(mT->m);
		glutSolidCylinder(h, r, 20, 20);
		glPopMatrix();
	}

private:
	GLfloat h, r;
};

class Esfera : public RigidBody
{
public:
	Esfera(float x, float y, float z, GLfloat masa, GLfloat radio) :RigidBody(x, y, z, masa), h(radio), r(radio) {
		
		pos = { x, y, z  };
		/*this->mT->rota(&PuntoVector3D(0, 0, 1, 0), 90);*/
	};
	~Esfera() {

	}
	virtual void Render() {
		glPushMatrix();
		glMultMatrixf(mT->m);
		glutSolidSphere(r, 24, 24);
		glPopMatrix();
	}

private:
	GLfloat h, r;
};