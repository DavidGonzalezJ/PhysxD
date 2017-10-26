#include "FireWork.h"
#include "Explosion.h"


FireWork::FireWork()
{
	vidaAct = 1;
	cohete = new particulas(PuntoVector3D(0, 1, 0, 1));
	cohete->setColor(PuntoVector3D(1, 1, 1, 1));
	cohete->setVel(PuntoVector3D(0, 50, 0, 1));
	estadoCohete = LANZADO;
	cohete->setWorld(world);
	cohete->vidaAct = 100000.0f;
}


FireWork::~FireWork()
{
	delete cohete;
}

void FireWork::update(GLfloat dt){
	pos = cohete->pos;
	cohete->update(dt);
	switch (estadoCohete)
	{
	case FireWork::LANZADO:
		if (cohete->vel.getY() < 0){
			estadoCohete = EXPLOTADO;
			delete cohete;
			cohete = new Explosion(pos);
		}
			
		break;
	case FireWork::EXPLOTADO:
		if (cohete->getVidaAct() == 0){

			reiniciar();
		}
		break;
	default:
		break;
	}

	
	
}