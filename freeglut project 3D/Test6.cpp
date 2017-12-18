#include "Test6.h"
#include "TiradorSolidos.h"
#include "SimulaColision2D.h"


Test6::Test6()
{
	world_ = new World();
	fuente = new SimulaColision2D();
	fuente->setWorld(world_);
}


Test6::~Test6()
{
}

void Test6::dibuja() {
	GLfloat ticks = glutGet(GLUT_ELAPSED_TIME);
	bool update = false;
	fuente->dibuja();

	if (update || lastTimeUpdate + frecuencia <= ticks) {
		fuente->update(ticks);
	}
}