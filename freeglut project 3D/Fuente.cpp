#include "Fuente.h"
#include "particulas.h"


Fuente::Fuente()
{
}


Fuente::~Fuente()
{
	for (auto p : Vector) {
		delete p;

	}
}

Objeto3D* Fuente::creaParticula()
{
	Objeto3D *p =  new particulas(1, 10, 10, PuntoVector3D(0, 1, 0, 0));
	p->setColor(PuntoVector3D(world->dameRandom(1, 0.5), world->dameRandom(0.5, 0), 0, 0));
	p->setVel(PuntoVector3D(world->dameRandom(5, -5), 20, world->dameRandom(5, -5), 1));
	p->setWorld(world);
	return p;
}
