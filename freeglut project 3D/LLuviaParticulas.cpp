#include "LLuviaParticulas.h"
#include "particulas.h"

LLuviaParticulas::LLuviaParticulas()
{
}


LLuviaParticulas::~LLuviaParticulas()
{
	for (auto p : Vector) {
		delete p;

	}
}
void LLuviaParticulas::update(GLfloat dt)
{
	for (size_t i = 0; i < Vector.size(); i++)
	{
		Vector[i]->setColor(PuntoVector3D(1, 1, 1, (int)((Vector[i]->getVidaAct() / Vector[i]->vida) * 30) / 10.0));
		Vector[i]->update(dt);
		if (Vector[i]->getDestroy()) {
			Vector.erase(Vector.begin() + i);
		}
	}
	if (Vector.size() < 8000)
	for (size_t i = 0; i < 50; i++)
	{
		Vector.push_back(creaParticula());

	}
}

Objeto3D* LLuviaParticulas::creaParticula()
{
	Objeto3D *p = new particulas(PuntoVector3D(world->dameRandom(55, -55), 180, world->dameRandom(55, -55), 0), -0.8);
	p->setColor(PuntoVector3D(1, 1, 1, 1));
	p->setVel(PuntoVector3D(0, 0, 0, 1));
	p->setWorld(world);
	return p;
}