#include "Test5.h"
#include "TiradorSolidos.h"

Test5::Test5()
{
	world_ = new World();
	fuente = new TiradorSolidos();
	fuente->setWorld(world_);
}


Test5::~Test5()
{
}
void Test5::dibuja() {
	GLfloat ticks = glutGet(GLUT_ELAPSED_TIME);
	bool update = false;
	fuente->dibuja();

	if (update || lastTimeUpdate + frecuencia <= ticks) {
		fuente->update(ticks);


	}
}
