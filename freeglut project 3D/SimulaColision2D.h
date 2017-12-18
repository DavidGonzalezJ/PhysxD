#pragma once
#include "Objeto3D.h"
class SimulaColision2D : public Objeto3D
{
public:
	SimulaColision2D();
	~SimulaColision2D();
	virtual void dibuja() {
		caja1->dibuja();
		caja2->dibuja();
	};
	virtual void update(GLfloat dt);
	Objeto3D *creaParticula();
private:
	Objeto3D* caja1;
	Objeto3D* caja2;
	bool colision2D(Objeto3D* a, Objeto3D* b);
};

