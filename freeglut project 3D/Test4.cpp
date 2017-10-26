#include "Test4.h"
#include "FireWorks.h"
#include "Explosion.h"

Test4::Test4()
{
	world_ = new World();
	_explosion = new FireWorks(PuntoVector3D(0, 0, 0, 1));
	_explosion->setWorld(world_);
	
		done = false;
}


Test4::~Test4()
{
}

void Test4::creaParticulas(int num) {
}
void Test4::dibuja() {
	GLfloat ticks = glutGet(GLUT_ELAPSED_TIME);
	bool update = false;
	if (!done){
		_explosion->dibuja();

		if (update || lastTimeUpdate + frecuencia <= ticks) {
			_explosion->update(ticks);
			if (_explosion->getVidaAct() == 0){
				posAux = _explosion->pos;
				_explosion->reiniciar();
				fireworks = new Explosion(posAux);
				fireworks->setWorld(world_);
				done = true;

			}
		}
	}
	else{
		fireworks->dibuja();

		if (update || lastTimeUpdate + frecuencia <= ticks) {
			fireworks->update(ticks);
			if (fireworks->getVidaAct() == 0){
				fireworks->reiniciar();
				done = false;

			}
		}
	}
}

Objeto3D* Test4::creaParticula()
{
	Objeto3D* p = new particulas(PuntoVector3D(0, 40, 0, 0), (-9.81));
	p->setColor(PuntoVector3D(world_->dameRandom(1, 0.5), world_->dameRandom(0.5, 0), 0, 0));
	p->setVel(PuntoVector3D(world_->dameRandom(50, -50), world_->dameRandom(50, -50), world_->dameRandom(50, -50), 1));
	p->setWorld(world_);
	return p;
}

