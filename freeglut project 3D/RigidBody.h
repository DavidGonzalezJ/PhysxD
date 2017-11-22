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
	virtual void setForce(glm::vec3 fuerza) {
		Fuerza = fuerza;
	}
	virtual void setTorque(glm::vec3 angulag) {
		angMom = angulag;
	}
	~RigidBody() {

	};
	TAfin * mT;
protected:
	glm::mat4 cubeMatrix;//Matriu transposada
	float timer = 0;
	float mass = 1;
	glm::mat3 iBody = { (mass * 2) / 12, 0, 0,
		0, (mass * 2) / 12, 0,
		0, 0, (mass * 2) / 12 };
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
		glm::vec3 newTorque = { t[0], t[1], t[2] };
		angMom = angMom + (dt * newTorque);
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
	void Render() {
		glPushMatrix();
		glMultMatrixf(mT->m);
		glutSolidCube(5);
		glPopMatrix();
	}

private:

};