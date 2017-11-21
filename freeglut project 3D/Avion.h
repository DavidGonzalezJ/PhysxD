#pragma once+
#include "RigidBody.h"
class Avion: public RigidBody
{
public:
	Avion();
	~Avion();
	void InitializeAirplane(void);
	void CalcAirplaneMassProperties();
	bool Stalling, Flaps;
	double ThrustForce;
};
