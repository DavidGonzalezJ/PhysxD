#pragma once
#include "Objeto3D.h"
#include <vector>
class Fuego :
	public Objeto3D
{
public:
	Fuego();
	virtual ~Fuego();
	virtual void dibuja() {
		for (auto &p : Vector) {
			p->dibuja();
		}
	};
	virtual void update(GLfloat dt);
	Objeto3D *creaParticula();
private:
	std::vector<Objeto3D*> Vector;
};

