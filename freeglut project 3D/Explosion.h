#pragma once
#include "Objeto3D.h"
#include <vector>
class Explosion : public Objeto3D
{
public:
	Explosion(PuntoVector3D Pos);
	virtual ~Explosion();
	virtual void dibuja(){
		for (auto &p : Vector) {
			p->dibuja();
		}
	}
	virtual void update(GLfloat dt);
	Objeto3D* creaParticula();
	virtual void reiniciar(){
		for (size_t i = 0; i < 1000; i++)
		{
			Vector.push_back(creaParticula());
		}
		vidaAct = 1;
	}
	bool Ended(){
		return Vector.size() < 4;
	}
private:
	std::vector<Objeto3D*> Vector;
};

