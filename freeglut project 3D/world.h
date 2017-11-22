#ifndef WORLD_H
#define WORLD_H

#include "PuntoVector3D.h"
#include <math.h>
#include "ListaObjetos.h"
#define GRAVITY -9.81f
class World 
{
public:
	World() { 
		gravity = PuntoVector3D(0, GRAVITY, 0, 1); 
	};
	~World() {};
	virtual PuntoVector3D getGravity(){ return gravity; };
	virtual PuntoVector3D getWorldBox(){ return worldBox; };
	GLfloat dameRandom(GLfloat max, GLfloat min) {
		return min + static_cast <GLfloat> (rand()) / (static_cast <GLfloat> (RAND_MAX / (max - min)));
	}
	PuntoVector3D DameVectorAleatorio(GLfloat magnitud) {
		PuntoVector3D v;
		GLfloat phi = dameRandom(3.1415f, 0.0f);
		GLfloat cosTheta = dameRandom(1, -1);

		GLfloat theta = acosf(cosTheta);
		GLfloat x = sinf(theta)*cosf(phi), y = sinf(theta)*sinf(phi), z = cosf(theta);
		v.setVector(x, y, z);
		v.mult(magnitud);
		return v;
	}
	//vector<Objeto3D> getObjects(){ return objetos; };
private:
	PuntoVector3D gravity;
	PuntoVector3D worldBox;
};

#endif // !WORLD_H
