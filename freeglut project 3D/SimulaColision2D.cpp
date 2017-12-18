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
	if (colision2D(caja1, caja2)) {//Estoy haciendo el caso super concreto de que la 1 esté en mov y la 2 no. :(
		caja2->setVel(caja1->vel);
		caja1->setVel(PuntoVector3D(0, 0, 0, 1));
	}
}

Objeto3D * SimulaColision2D::creaParticula()
{
	return nullptr;
}

struct referencia2D {
	PuntoVector3D ari;
	PuntoVector3D ard;
	PuntoVector3D abd;
	PuntoVector3D abi;
};

//Coste casi cósmico. Lo suyo sería hacer las cajas de colisión en otra clase y que se
//actualizasen, pero estamos aquí para hacer un rush.
bool SimulaColision2D::colision2D(Objeto3D* a,Objeto3D* b) {
	referencia2D a1, b1;
	a1.ari.setX(a->pos.getX() - static_cast<Cubo*>(a)->tam / 2);
	a1.ari.setY(a->pos.getY() + static_cast<Cubo*>(a)->tam / 2);
	a1.ari.setZ(0);
	a1.abi.setX(a->pos.getX() - static_cast<Cubo*>(a)->tam / 2);
	a1.abi.setY(a->pos.getY() - static_cast<Cubo*>(a)->tam / 2);
	a1.abi.setZ(0);
	a1.ard.setX(a->pos.getX() + static_cast<Cubo*>(a)->tam / 2);
	a1.ard.setY(a->pos.getY() + static_cast<Cubo*>(a)->tam / 2);
	a1.ard.setZ(0);
	a1.abd.setX(a->pos.getX() + static_cast<Cubo*>(a)->tam / 2);
	a1.abd.setY(a->pos.getY() - static_cast<Cubo*>(a)->tam / 2);
	a1.abd.setZ(0);

	b1.ari.setX(b->pos.getX() - static_cast<Cubo*>(b)->tam / 2);
	b1.ari.setY(b->pos.getY() + static_cast<Cubo*>(b)->tam / 2);
	b1.ari.setZ(0);
	b1.abi.setX(b->pos.getX() - static_cast<Cubo*>(b)->tam / 2);
	b1.abi.setY(b->pos.getY() - static_cast<Cubo*>(b)->tam / 2);
	b1.abi.setZ(0);
	b1.ard.setX(b->pos.getX() + static_cast<Cubo*>(b)->tam / 2);
	b1.ard.setY(b->pos.getY() + static_cast<Cubo*>(b)->tam / 2);
	b1.ard.setZ(0);
	b1.abd.setX(b->pos.getX() + static_cast<Cubo*>(b)->tam / 2);
	b1.abd.setY(b->pos.getY() - static_cast<Cubo*>(b)->tam / 2);
	b1.abd.setZ(0);

	if (!((b1.abi.getX() > a1.ard.getX() || b1.abi.getY() > a1.ard.getY())
		|| (b1.ari.getX() > a1.abd.getX() || b1.ari.getY() < a1.abd.getY())
		|| (b1.ard.getX() < a1.abi.getX() || b1.ard.getY() < a1.abi.getY())
		|| (b1.abd.getX() < a1.ari.getX() || b1.abd.getY() > a1.ari.getY())))
		return true;
	return false;
}