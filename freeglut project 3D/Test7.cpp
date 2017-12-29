#include "Test7.h"
#include <iostream>
#include "LectorObj.h"


Test7::Test7()
{
	std::vector< glm::vec3 >* vertices	= new std::vector< glm::vec3 >;
	std::vector< glm::vec2 >* uvs		= new std::vector< glm::vec2 >;
	std::vector< glm::vec3 >* normals	= new std::vector< glm::vec3 >;
	std::vector<Cara>*	caras			= new std::vector< Cara >;
	loadOBJ("box.obj",* vertices, *uvs, *normals,*caras);
	kekubo = Malla(vertices, normals, caras);
	for (size_t i = 0; i < 2; i++)
	{
		ejericito.push_back(new TeteraRigida(i*5, i * 100, 0,2));
		if (i == 0)ejericito[i]->setForce({ 0,1000,0 }, 1/*, {-2.5,0,2.5}*/);
		else ejericito[i]->setForce({0,0, 0 }, 1/*, {-2.5,0,2.5}*/);
	}
}
Test7::~Test7()
{
}
void Test7::dibuja() {
	GLfloat ticks = glutGet(GLUT_ELAPSED_TIME);
	if (lastTimeUpdate + frecuencia <= ticks) {
		//kekubo.dibuja();
		ticks = (ticks - lastTimeUpdate - frecuencia) / 1000;
		bool eke = true;
		for (size_t i = 0; i < 2; i++)
		{

			for (size_t j = 0; j < 2 && eke; j++) {
				if (j != i) {
					PuntoVector3D *s = &ejericito[i]->mT->getPos();
					PuntoVector3D *s2 = &ejericito[j]->mT->getPos();
					s2->escalar(-1);

					s->sumar(s2);
					float squareLength = (s->getX() * s->getX()) + (s->getY() * s->getY()) + (s->getZ() * s->getZ());

					if (ejericito[i]->collider.collision(ejericito[j]->collider)) {
						ejericito[i]->setColour(1, 0, 0);
						vec3 f1 = ejericito[i]->getLinearMomentum();
						vec3 f2 = ejericito[j]->getLinearMomentum();
						vec3 lit = glm::normalize(f1);
						vec3 lit2 = glm::normalize(f2);

						ejericito[i]->setMomentum(f2);
						ejericito[j]->setMomentum(f1);
						ejericito[j]->setColour(1, 0, 0);
						eke = false;
					}
					else {
						ejericito[i]->setColour(1, 1, 1);
						ejericito[j]->setColour(1, 1, 1);
					}
				}
			}
			ejericito[i]->Update(ticks);

		}
	}
	for (size_t i = 0; i < 2; i++)
	{
		ejericito[i]->Render();
	}
}
