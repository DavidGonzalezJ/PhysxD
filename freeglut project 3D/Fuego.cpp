#include "Fuego.h"
#include "particulas.h"


Fuego::Fuego()
{
	Vector.reserve(5000);
}


Fuego::~Fuego()
{
	for (auto p : Vector) {
		delete p;

	}
}

void Fuego::update(GLfloat dt)
{
	for (size_t i = 0; i < Vector.size(); i++)
	{
		Vector[i]->setColor(PuntoVector3D(1, (Vector[i]->getVidaAct() / Vector[i]->vida) - 0.2, 0, (int)((Vector[i]->getVidaAct() / Vector[i]->vida) * 10) / 10.0));
		Vector[i]->update(dt);

		if (Vector[i]->getDestroy()) {
			Vector.erase(Vector.begin() + i);
		}
	}
	if (Vector.size() <10000)
		for (size_t i = 0; i < 50; i++)
		{
			Vector.push_back(creaParticula());

		}


}

Objeto3D* Fuego::creaParticula()
{
	Objeto3D *p =  new particulas( PuntoVector3D(world->dameRandom(15,-15), 1, world->dameRandom(15, -15), 0),0,150,100);
	p->setVel(PuntoVector3D(world->dameRandom(2, -2), world->dameRandom(10,5), world->dameRandom(2, -2), 1));
	p->setWorld(world);
	return p;
}
