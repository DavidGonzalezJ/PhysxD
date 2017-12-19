#include "Test7.h"



Test7::Test7()
{
	for (size_t i = 0; i < 2; i++)
	{
		ejericito.push_back(new Esfera(i * 10, 0, 0, 4, 5));
	//	ejericito[i]->setForce({ 0,8 * 1000,0 }, 1/*, {-2.5,0,2.5}*/);
	}
}


Test7::~Test7()
{
}
void Test7::dibuja() {
	GLfloat ticks = glutGet(GLUT_ELAPSED_TIME);
	if (lastTimeUpdate + frecuencia <= ticks) {
		for (size_t i = 0; i < 2; i++)
		{
			ejericito[i]->Update(ticks);
		}
	}
	for (size_t i = 0; i < 2; i++)
	{
		ejericito[i]->Render();
	}
}
