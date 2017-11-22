#pragma once
#include "RigidBody.h"
#include <vector>
class Test5
{
public:
	Test5() {
		for (size_t i = 0; i < 10; i++)
		{
			ejericito.push_back(new TeteraRigida(i*10, 0, 0, 1));
			ejericito[i]->setForce({ 0,8*1000,0 });
			ejericito[i]->setTorque({ 0,0.1,0 });


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
	std::vector<TeteraRigida*> ejericito;
	TeteraRigida * tetera;
	GLfloat lastTimeUpdate = 0;
	GLfloat frecuencia = 20;

	

};

