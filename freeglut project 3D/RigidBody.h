#pragma once
#include "Vector.h"
#include "Matrix3x3.h"
#include "Quaternion.h"

class RigidBody
{
public:
	RigidBody();
	~RigidBody();
	float         fMass;           // total mass
	Matrix3x3     mInertia;        // mass moment of inertia
	// in body coordinates

	Matrix3x3     mInertiaInverse; // inverse of mass moment of inertia
	Vector      vPosition;       // position in earth coordinates
	Vector        vVelocity;       // velocity in earth coordinates
	Vector        vVelocityBody;   // velocity in body coordinates
	Vector        vAngularVelocity;// angular velocity in body coordinates
	Vector        vEulerAngles;    // Euler angles in body coordinates
	float         fSpeed;          // speed (magnitude of the velocity)
	Quaternion    qOrientation;    // orientation in earth coordinates
	Vector        vForces;         // total force on body
	Vector        vMoments;        // total moment (torque) on body
};

