#include "esfera.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>

#define TOP_DEADZONE 200
#define BOTTOM_DEADZONE 0

esfera::esfera(int radio, int meridiano, int paralelo)
{
	radio_ = radio;
	meridiano_ = meridiano;
	paralelo_ = paralelo;
}


esfera::~esfera()
{
}
void esfera::dibuja() {
	glutSolidSphere(radio_, meridiano_, paralelo_);

}

void esfera::setPos(PuntoVector3D aux)
{
	pos = aux;
}

void esfera::setDir(PuntoVector3D aux)
{
	dir = aux;
}

void esfera::setAce(PuntoVector3D aux)
{
	ace = aux;
}
void esfera::setColor(PuntoVector3D aux)
{
	color = aux;
}
void esfera::update() {
	pos.sumar(&dir);
	if (pos.getY() >= TOP_DEADZONE) {
		setPos(PuntoVector3D(pos.getX(), 0, pos.getZ(), 0));

	}
}
