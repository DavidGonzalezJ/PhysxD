#include "FireWorks.h"
#include "particulas.h"
#include "Explosion.h"

FireWorks::FireWorks(PuntoVector3D posi)
{
	vidaAct = 1000;
	initPos = posi;
	reiniciar();
}


FireWorks::~FireWorks()
{
	for (auto p : Vector) {
		delete p;
	}
}

void FireWorks::update(GLfloat dt)
{
	
	for (size_t i = 0; i < Vector.size(); i++)
	{
		Vector[i]->setColor(PuntoVector3D(1, (Vector[i]->getVidaAct() / Vector[i]->vida) - 0.2, 0, (int)((Vector[i]->getVidaAct() / Vector[i]->vida) * 10) / 10.0));

		Vector[i]->update(dt);
		if (Vector[i]->vel.getY()>0 || Vector[i]->pos.getY()> 100)pos = Vector[i]->pos;
		if (Vector[i]->getDestroy()) {
			Vector.erase(Vector.begin() + i);

		}
	}
	if (Vector.size() == 0){
		vidaAct = 0;
	}
}

Objeto3D* FireWorks::creaParticula()
{
	Objeto3D *p = new particulas(initPos, -9.8, 1000, 900);
	//p->setColor(PuntoVector3D(0, 0.3, 0.6, 1));

	p->setVel(PuntoVector3D(world->dameRandom(10, -10), 50, world->dameRandom(10, -10), 1));
	p->setWorld(world);
	return p;
}
