#pragma once
#include "Objeto3D.h"
#include <vector>
class Explosion : public Objeto3D
{
public:
	Explosion();
	virtual ~Explosion();
	virtual void dibuja(){
		for (auto &p : Vector) {
			p->dibuja();
		}
	}
	virtual void update(GLfloat dt);
	Objeto3D* creaParticula();
	void reiniciarEscena(){
		for (size_t i = 0; i < 1000; i++)
		{
			Vector.push_back(creaParticula());
		}
	}
private:
	std::vector<Objeto3D*> Vector;
};

