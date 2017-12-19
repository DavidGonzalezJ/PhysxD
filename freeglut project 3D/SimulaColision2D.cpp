#include "SimulaColision2D.h"
#include "Cubo.h"
#include "Rigidbody.h"


SimulaColision2D::SimulaColision2D()
{
	//Habría que cambiar la gravedad aquí
	caja1 = new Rigidbody(PuntoVector3D(0, 1, 0, 0),0);
	caja1->setColor(PuntoVector3D(0, 0.3, 0.6, 1));
	caja1->setSize(10);
	caja1->setVel(PuntoVector3D(20, 0, 0, 1));
	caja1->setWorld(world);

	caja2 = new Rigidbody(PuntoVector3D(15, 1, 0, 0),0);
	caja2->setColor(PuntoVector3D(0, 0.3, 0.6, 1));
	caja2->setSize(10);
	caja2->setVel(PuntoVector3D(0, 0, 0, 1));
	caja2->setWorld(world);

	glutSolidSphere(size, 5, 5);

}


SimulaColision2D::~SimulaColision2D()
{
	delete caja1;
	delete caja2;
}

void SimulaColision2D::update(GLfloat dt)
{
	caja1->setColor(PuntoVector3D(0, 0.3, 0.6, (int)((caja1->getVidaAct() / caja1->vida) * 10) / 10.0));
	caja1->update(dt);
	caja2->setColor(PuntoVector3D(0, 0.3, 0.6, (int)((caja1->getVidaAct() / caja1->vida) * 10) / 10.0));
	caja2->update(dt);
	
}

Objeto3D * SimulaColision2D::creaParticula()
{
	return nullptr;
}



//Coste casi cósmico. Lo suyo sería hacer las cajas de colisión en otra clase y que se
//actualizasen, pero estamos aquí para hacer un rush.
bool SimulaColision2D::colision2D(Objeto3D* a,Objeto3D* b) {

}