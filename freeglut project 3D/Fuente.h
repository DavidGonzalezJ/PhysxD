#pragma once
#include "Objeto3D.h"
#include <vector>
class Fuente :
	public Objeto3D
{
public:
	Fuente();
	virtual ~Fuente();
	virtual void dibuja() {
		for (auto &p : Vector) {
			p->dibuja();
		}
	};
	virtual void update(GLfloat dt) {
		for (size_t i = 0; i < Vector.size(); i++)
		{
			Vector[i]->update(dt);
			if (Vector[i]->getDestroy()) {
				Vector.erase(Vector.begin() + i);
			}
		}
		if (Vector.size() < 5000)
			Vector.push_back(creaParticula());

	};
	Objeto3D *creaParticula();
private:
	std::vector<Objeto3D*> Vector;
};

