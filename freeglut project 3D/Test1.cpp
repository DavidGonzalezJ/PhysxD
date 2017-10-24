#include "Test1.h"

Test1::Test1()
{
	world_ =  new world();
}


Test1::~Test1()
{
}

void Test1::creaParticulas(int num) {
	numParticulas = num;
	objetos = new Objeto3D*[num];
	for (int i = 0; i < num; i++)
	{
		objetos[i] = new particulas(1, 10, 10, PuntoVector3D(world_->dameRandom(50, -50), world_->dameRandom(250, 0), world_->dameRandom(50, -50), 0));
		objetos[i]->setColor(PuntoVector3D(world_->dameRandom(1, 0.5), world_->dameRandom(0.5, 0), 0, 0));
		objetos[i]->setWorld(world_);
		
	}
	
	
}
void Test1::dibuja() {
	GLfloat ticks = glutGet(GLUT_ELAPSED_TIME);
	bool update = false;
	for (size_t i = 0; i < numParticulas; i++)
	{
		objetos[i]->dibuja();

		if (update || lastTimeUpdate + frecuencia <= ticks) {
		objetos[i]->update(ticks);
			update = true;
			lastTimeUpdate = ticks;
		objetos[i]->aplicarFuerza(PuntoVector3D(world_->dameRandom(-4,4), 0, world_->dameRandom(-4, 4), 0));
		objetos[i]->update(ticks);
		}
	}
}

