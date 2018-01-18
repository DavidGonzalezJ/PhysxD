#include "Test3.h"
#include "Explosion.h"

Test3::Test3(PuntoVector3D * pos)
{
	world_ = new World();
	_explosion = new Explosion(PuntoVector3D(pos->getX(),pos->getY(),pos->getZ(),1));
	_explosion->setWorld(world_);
}


Test3::~Test3()
{
}

void Test3::creaParticulas(int num) {
}
void Test3::dibuja() {
	GLfloat ticks = glutGet(GLUT_ELAPSED_TIME);
	bool update = false;

	_explosion->dibuja();

	if (update || lastTimeUpdate + frecuencia <= ticks) {
		_explosion->update(ticks);
		if (_explosion->getVidaAct() ==0){
			_explosion->reiniciar();
		}
	}
}

Objeto3D* Test3::creaParticula()
{
	Objeto3D* p = new particulas(PuntoVector3D(0, 40, 0, 0));
	p->setColor(PuntoVector3D(world_->dameRandom(1, 0.5), world_->dameRandom(0.5, 0), 1, 0));
	p->setVel(PuntoVector3D(world_->dameRandom(50, -50), world_->dameRandom(50, -50), world_->dameRandom(50, -50), 1));
	p->setWorld(world_);
	return p;
}

