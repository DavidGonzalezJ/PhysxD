#include "Test2.h"
#include "Fuente.h"

Test2::Test2()
{
	world_ = new World();
	fuente = new Fuente();
	fuente->setWorld(world_);
}


Test2::~Test2()
{
}

void Test2::creaParticulas(int num) {
}
void Test2::dibuja() {
	GLfloat ticks = glutGet(GLUT_ELAPSED_TIME);
	bool update = false;
	fuente->dibuja();

	if (update || lastTimeUpdate + frecuencia <= ticks) {
		fuente->update(ticks);


	}
}

Objeto3D* Test2::creaParticula()
{
	Objeto3D* p = new particulas(PuntoVector3D(0, 1, 0, 0));
	p->setColor(PuntoVector3D(world_->dameRandom(1, 0.5), world_->dameRandom(0.5, 0), 0, 0));
	p->setVel(PuntoVector3D(world_->dameRandom(50, -50), 50, world_->dameRandom(50, -50), 1));
	p->setWorld(world_);
	return p;
}

