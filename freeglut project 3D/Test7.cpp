#include "Test7.h"
#include <iostream>


Test7::Test7()
{
	for (size_t i = 0; i < 2; i++)
	{
		ejericito.push_back(new Esfera(i * 40, 0, 0, 2, 5));
		if (i == 0)ejericito[i]->setForce({ 2000,8 * 1000,0 }, 1/*, {-2.5,0,2.5}*/);
		else ejericito[i]->setForce({ -2000, 8 * 1000, 0 }, 1/*, {-2.5,0,2.5}*/);
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

			for (size_t j = 0; j < 2; j++){
				if (j != i){
					PuntoVector3D *s = &ejericito[i]->mT->getPos();
					PuntoVector3D *s2 = &ejericito[j]->mT->getPos();
					s2->escalar(-1);

					s->sumar(s2);
					float squareLength = (s->getX() * s->getX()) + (s->getY() * s->getY()) + (s->getZ() * s->getZ());

					if (squareLength <= 100){ 
						std::cout << "choque\n";
						ejericito[i]->setColour(1,0,0);
						ejericito[j]->setColour(1, 0, 0);
					}
					else {
						ejericito[i]->setColour(1, 1, 1);
						ejericito[i]->setColour(1, 1, 1);
					}
				}
			}
			
		}
	}
	for (size_t i = 0; i < 2; i++)
	{
		ejericito[i]->Render();
	}
}
