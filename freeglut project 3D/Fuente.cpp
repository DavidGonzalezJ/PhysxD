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

void Fuente::update(GLfloat dt)
{
	for (size_t i = 0; i < Vector.size(); i++)
	{
		Vector[i]->setColor(PuntoVector3D(0,0.3, 0.6, (int)((Vector[i]->getVidaAct() / Vector[i]->vida) * 10) / 10.0));
		Vector[i]->update(dt);
		if (Vector[i]->getDestroy()) {
			Vector.erase(Vector.begin() + i);
		}
	}
	if (Vector.size() < 10000)
		for (size_t i = 0; i < 50; i++)
		{
			Vector.push_back(creaParticula());

		}
}

Objeto3D* Fuente::creaParticula()
{
	Objeto3D *p = new particulas(PuntoVector3D(0, 1, 0, 0),-9.81,150,100);
	p->setColor(PuntoVector3D(0,0.3,0.6,1));
	p->setVel(PuntoVector3D(world->dameRandom(10,-10), 50, world->dameRandom(10, -10), 1));
	p->setWorld(world);
	return p;
}