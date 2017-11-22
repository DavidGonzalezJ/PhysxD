#include "Test5.h"


Test5::Test5()
{
	world_ = new World();
	cubo = new RBody(5, 10);
}

void Test5::dibuja() {
	GLfloat ticks = glutGet(GLUT_ELAPSED_TIME);
	bool update = false;
	cubo->dibuja();

	if (update || lastTimeUpdate + frecuencia <= ticks) {
		cubo->update(ticks);
		
	}
}

Test5::~Test5()
{
}
