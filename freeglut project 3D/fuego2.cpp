#include "Fuego2.h"
#include "particulas.h"


Fuego2::Fuego2()
{
	Vector.reserve(5000);
}


Fuego2::~Fuego2()
{
	for (auto p : Vector) {
		delete p;

	}
}

void Fuego2::update(GLfloat dt)
{
	for (size_t i = 0; i < Vector.size(); i++)
	{
		Vector[i]->setColor( PuntoVector3D (1,1,1,1));
		Vector[i]->update(dt);

		if (Vector[i]->getDestroy()) {
			Vector.erase(Vector.begin() + i);
		}
	}
	if (Vector.size() <1000)
		for (size_t i = 0; i < 50; i++)
		{
			Vector.push_back(creaParticula());

		}


}

Objeto3D* Fuego2::creaParticula()
{
	Objeto3D *p = new particulas(PuntoVector3D(world->dameRandom(2, -2), 1, world->dameRandom(2, -2), 0), 0, 100, 20);
	p->setVel(PuntoVector3D(world->dameRandom(2, -2), world->dameRandom(10, 5), world->dameRandom(2, -2), 1));
	p->setWorld(world);
	return p;
}