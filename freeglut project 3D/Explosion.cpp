#include "Explosion.h"
#include "particulas.h"

Explosion::Explosion(PuntoVector3D posi) 
{
	vidaAct = 1;
	pos = posi;
	reiniciar();
}


Explosion::~Explosion()
{
	for (auto p : Vector) {
		delete p;
	}
}

void Explosion::update(GLfloat dt)
{
	for (size_t i = 0; i < Vector.size(); i++)
	{
		Vector[i]->setColor(PuntoVector3D(1, (Vector[i]->getVidaAct() / Vector[i]->vida) - 0.2, 0, (int)((Vector[i]->getVidaAct() / Vector[i]->vida) * 40) / 10.0));
		Vector[i]->update(dt);
	
		if (Vector[i]->getDestroy()) {
			Vector.erase(Vector.begin() + i);
		}
	}
	if (Vector.size() == 0){
		vidaAct = 0;
	}
}

Objeto3D* Explosion::creaParticula()
{
	Objeto3D *p = new particulas(pos);
	//p->setColor(PuntoVector3D(0, 0.3, 0.6, 1));
	
	p->setVel(world->DameVectorAleatorio(world->dameRandom(50,-50)));
	p->setWorld(world);
	return p;
}
