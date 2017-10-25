#include "Test0.h"
#include "LluviaParticulas.h"

Test0::Test0()
{
	world_ = new World();
	lluviaP = new LLuviaParticulas();
	lluviaP->setWorld(world_);
}


Test0::~Test0()
{
}

void Test0::creaParticulas(int num) {
}
void Test0::dibuja() {
	GLfloat ticks = glutGet(GLUT_ELAPSED_TIME);
	bool update = false;
	lluviaP->dibuja();

	if (update || lastTimeUpdate + frecuencia <= ticks) {
		lluviaP->update(ticks);


	}
}

Objeto3D* Test0::creaParticula()
{
	Objeto3D* p = new particulas(PuntoVector3D(0, 1, 0, 0));
	p->setColor(PuntoVector3D(world_->dameRandom(1, 0.5), world_->dameRandom(0.5, 0), 0, 0));
	p->setVel(PuntoVector3D(world_->dameRandom(50, -50), 50, world_->dameRandom(50, -50), 1));
	p->setWorld(world_);
	return p;
}

