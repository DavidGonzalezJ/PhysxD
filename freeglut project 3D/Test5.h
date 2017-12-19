#pragma once
#include "RigidBody.h"
#include <vector>
class Test5
{
public:
	Test5() {
		for (size_t i = 0; i < 10; i++)
		{
			if(i%2==0)
				ejericito.push_back(new TeteraRigida(i*10, 0, 0, 1));
			else
				ejericito.push_back(new Esfera(i * 10, 0, 0,4,5));
			ejericito[i]->setForce({ 0,8 * 1000,0 }, 1/*, {-2.5,0,2.5}*/);
			ejericito[i]->setTorque({ 9,9,0 },2);


		}
		

	};
	~Test5() {};
	void dibuja() {
		GLfloat ticks = glutGet(GLUT_ELAPSED_TIME);
		if ( lastTimeUpdate + frecuencia <= ticks) {
			for (size_t i = 0; i < 10; i++)
			{
				ejericito[i]->Update(ticks);
			}
		}
		for (size_t i = 0; i < 10; i++)
		{
			ejericito[i]->Render();
		}
	}

private:
	std::vector<RigidBody*> ejericito;
	TeteraRigida * tetera;
	GLfloat lastTimeUpdate = 0;
	GLfloat frecuencia = 20;

	

};

