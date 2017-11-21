#include "Avion.h"
#include "Vector.h"

Avion::Avion()
{
	float iRoll, iPitch, iYaw;

	// Set initial position
	vPosition.x = -5000.0f;
	vPosition.y = 0.0f;
	vPosition.z = 2000.0f;

	// Set initial velocity
	vVelocity.x = 60.0f;
	vVelocity.y = 0.0f;
	vVelocity.z = 0.0f;
	fSpeed = 60.0f;

	// Set initial angular velocity
	vAngularVelocity.x = 0.0f;
	vAngularVelocity.y = 0.0f;
	vAngularVelocity.z = 0.0f;

	// Set the initial thrust, forces, and moments
	vForces.x = 500.0f;
	vForces.y = 0.0f;
	vForces.z = 0.0f;
	ThrustForce = 500.0;

	vMoments.x = 0.0f;
	vMoments.y = 0.0f;
	vMoments.z = 0.0f;

	// Zero the velocity in body space coordinates
	vVelocityBody.x = 0.0f;
	vVelocityBody.y = 0.0f;
	vVelocityBody.z = 0.0f;

	// Set these to false at first,
	// you can control later using the keyboard
	Stalling = false;
	Flaps = false;

	// Set the initial orientation
	iRoll = 0.0f;
	iPitch = 0.0f;
	iYaw = 0.0f;
	qOrientation = MakeQFromEulerAngles(iRoll, iPitch, iYaw);

	// Now go ahead and calculate the plane's mass properties
	CalcAirplaneMassProperties();
}


Avion::~Avion()
{
}
void Avion::    CalcAirplaneMassProperties(void)
{
	float     mass;
	Vector    vMoment;
	Vector    CG;
	int       i;
	float     Ixx, Iyy, Izz, Ixy, Ixz, Iyz;
	float     in, di;

	// Initialize the elements here
	// Initially the coordinates of each element are referenced from
	// a design coordinates system located at the very tail end of the plane,
	// its baseline and center line.  Later, these coordinates will be adjusted
	// so that each element is referenced to the combined center of gravity of
	// the 
	Element[0].fMass = 6.56f;
	Element[0].vDCoords = Vector(14.5f, 12.0f, 2.5f);
	Element[0].vLocalInertia = Vector(13.92f, 10.50f, 24.00f);
	Element[0].fIncidence = -3.5f;
	Element[0].fDihedral = 0.0f;
	Element[0].fArea = 31.2f;
	Element[0].iFlap = 0;

	Element[1].fMass = 7.31f;
	Element[1].vDCoords = Vector(14.5f, 5.5f, 2.5f);
	Element[1].vLocalInertia = Vector(21.95f, 12.22f, 33.67f);
	Element[1].fIncidence = -3.5f;
	Element[1].fDihedral = 0.0f;
	Element[1].fArea = 36.4f;
	Element[1].iFlap = 0;

	Element[2].fMass = 7.31f;
	Element[2].vDCoords = Vector(14.5f, -5.5f, 2.5f);
	Element[2].vLocalInertia = Vector(21.95f, 12.22f, 33.67f);
	Element[2].fIncidence = -3.5f;
	Element[2].fDihedral = 0.0f;
	Element[2].fArea = 36.4f;
	Element[2].iFlap = 0;

	Element[3].fMass = 6.56f;
	Element[3].vDCoords = Vector(14.5f, -12.0f, 2.5f);
	Element[3].vLocalInertia = Vector(13.92f, 10.50f, 24.00f);
	Element[3].fIncidence = -3.5f;
	Element[3].fDihedral = 0.0f;
	Element[3].fArea = 31.2f;
	Element[3].iFlap = 0;

	Element[4].fMass = 2.62f;
	Element[4].vDCoords = Vector(3.03f, 2.5f, 3.0f);
	Element[4].vLocalInertia = Vector(0.837f, 0.385f, 1.206f);
	Element[4].fIncidence = 0.0f;
	Element[4].fDihedral = 0.0f;
	Element[4].fArea = 10.8f;
	Element[4].iFlap = 0;

	Element[5].fMass = 2.62f;
	Element[5].vDCoords = Vector(3.03f, -2.5f, 3.0f);
	Element[5].vLocalInertia = Vector(0.837f, 0.385f, 1.206f);
	Element[5].fIncidence = 0.0f;
	Element[5].fDihedral = 0.0f;
	Element[5].fArea = 10.8f;
	Element[5].iFlap = 0;

	Element[6].fMass = 2.93f;
	Element[6].vDCoords = Vector(2.25f, 0.0f, 5.0f);
	Element[6].vLocalInertia = Vector(1.262f, 1.942f, 0.718f);
	Element[6].fIncidence = 0.0f;
	Element[6].fDihedral = 90.0f;
	Element[6].fArea = 12.0f;
	Element[6].iFlap = 0;

	Element[7].fMass = 31.8f;
	Element[7].vDCoords = Vector(15.25f, 0.0f, 1.5f);
	Element[7].vLocalInertia = Vector(66.30f, 861.9f, 861.9f);
	Element[7].fIncidence = 0.0f;
	Element[7].fDihedral = 0.0f;
	Element[7].fArea = 84.0f;
	Element[7].iFlap = 0;

	// Calculate the vector normal (perpendicular) to each lifting surface.
	// This is required when you are calculating the relative air velocity for
	// lift and drag calculations.
	for (i = 0; i< 8; i++)
	{
		in = DegreesToRadians(Element[i].fIncidence);
		di = DegreesToRadians(Element[i].fDihedral);
		Element[i].vNormal = Vector((float)sin(in), (float)(cos(in)*sin(di)),
			(float)(cos(in)*cos(di)));
		Element[i].vNormal.Normalize();
	}

	// Calculate total mass
	mass = 0;
	for (i = 0; i< 8; i++)
		mass += Element[i].fMass;

	// Calculate combined center of gravity location
	vMoment = Vector(0.0f, 0.0f, 0.0f);
	for (i = 0; i< 8; i++)
	{
		vMoment += Element[i].fMass*Element[i].vDCoords;
	}
	CG = vMoment / mass;

	// Calculate coordinates of each element with respect to the combined CG
	for (i = 0; i< 8; i++)
	{
		Element[i].vCGCoords = Element[i].vDCoords - CG;
	}

	// Now calculate the moments and products of inertia for the
	// combined elements.
	// (This inertia matrix (tensor) is in body coordinates)
	Ixx = 0;     Iyy = 0;     Izz = 0;
	Ixy = 0;     Ixz = 0;     Iyz = 0;
	for (i = 0; i< 8; i++)
	{
		Ixx += Element[i].vLocalInertia.x + Element[i].fMass *
			(Element[i].vCGCoords.y*Element[i].vCGCoords.y +
			Element[i].vCGCoords.z*Element[i].vCGCoords.z);
		Iyy += Element[i].vLocalInertia.y + Element[i].fMass *
			(Element[i].vCGCoords.z*Element[i].vCGCoords.z +
			Element[i].vCGCoords.x*Element[i].vCGCoords.x);
		Izz += Element[i].vLocalInertia.z + Element[i].fMass *
			(Element[i].vCGCoords.x*Element[i].vCGCoords.x +
			Element[i].vCGCoords.y*Element[i].vCGCoords.y);
		Ixy += Element[i].fMass * (Element[i].vCGCoords.x *
			Element[i].vCGCoords.y);
		Ixz += Element[i].fMass * (Element[i].vCGCoords.x *
			Element[i].vCGCoords.z);
		Iyz += Element[i].fMass * (Element[i].vCGCoords.y *
			Element[i].vCGCoords.z);
	}

	// Finally, set up the airplane's mass and its inertia matrix and take the
	// inverse of the inertia matrix.
	fMass = mass;
	mInertia.e11 = Ixx;
	mInertia.e12 = -Ixy;
	mInertia.e13 = -Ixz;
	mInertia.e21 = -Ixy;
	mInertia.e22 = Iyy;
	mInertia.e23 = -Iyz;
	mInertia.e31 = -Ixz;
	mInertia.e32 = -Iyz;
	mInertia.e33 = Izz;

	mInertiaInverse = mInertia.Inverse();
}