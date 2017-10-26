#pragma once
#include "Objeto3D.h"
#include <vector>
class FireWorks : public Objeto3D
{
public:
	FireWorks(PuntoVector3D Pos);
	virtual ~FireWorks();
	virtual void dibuja(){
		for (auto &p : Vector) {
			p->dibuja();
		}
	}
	virtual void update(GLfloat dt);
	Objeto3D* creaParticula();
	virtual void reiniciar(){
		for (size_t i = 0; i < 1; i++)
		{
			Vector.push_back(creaParticula());
			Vector[i]->setSize(3);
		}
		vidaAct = 10000;
	}
	bool Ended(){
		return Vector.size() < 4;
	}
private:
	Objeto3D* cohete;
	PuntoVector3D initPos;
	std::vector<Objeto3D*> Vector;
};

