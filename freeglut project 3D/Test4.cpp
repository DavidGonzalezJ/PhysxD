#include "Test4.h"
#include "FireWork.h"


Test4::Test4()
{
	world_ = new World();
	firework = new FireWork();
	firework->setWorld(world_);
}


Test4::~Test4()
{
}

void Test4::creaParticulas(int num) {
}
void Test4::dibuja() {
	GLfloat ticks = glutGet(GLUT_ELAPSED_TIME);
	bool update = false;
	firework->dibuja();

	if (update || lastTimeUpdate + frecuencia <= ticks) {
		firework->update(ticks);

	}
}

Objeto3D* Test4::creaParticula()
{
	Objeto3D* p = new particulas(PuntoVector3D(0, 40, 0, 0));
	p->setColor(PuntoVector3D(world_->dameRandom(1, 0.5), world_->dameRandom(0.5, 0), 0, 0));
	p->setVel(PuntoVector3D(world_->dameRandom(50, -50), world_->dameRandom(50, -50), world_->dameRandom(50, -50), 1));
	p->setWorld(world_);
	return p;
}

