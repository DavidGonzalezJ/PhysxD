#include "Test5.h"

Test5::Test5()
{
	world_ = new World();
	rb = new RBody(1,2);
	rb->setWorld(world_);
}


Test5::~Test5()
{
}

void Test5::creaParticulas(int num) {
}
void Test5::dibuja() {
	GLfloat ticks = glutGet(GLUT_ELAPSED_TIME);
	bool update = false;
	rb->dibuja();

	if (update || lastTimeUpdate + frecuencia <= ticks) {
		rb->aplicaFuerzas();
		rb->update(ticks);
		if (rb->getVidaAct() == 0){
			rb->reiniciar();
		}
	}
}

Objeto3D* Test5::creaParticula()
{
	Objeto3D* p = new RBody(1,2);
	p->setColor(PuntoVector3D(world_->dameRandom(1, 0.5), world_->dameRandom(0.5, 0), 0, 0));
	p->setVel(PuntoVector3D(world_->dameRandom(50, -50), world_->dameRandom(50, -50), world_->dameRandom(50, -50), 1));
	p->setWorld(world_);
	return p;
}

