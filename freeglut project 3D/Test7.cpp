#include "Test7.h"
#include <iostream>
#include "LectorObj.h"




Test7::Test7()
{
	std::vector< glm::vec3 >* vertices	= new std::vector< glm::vec3 >;
	std::vector< glm::vec2 >* uvs		= new std::vector< glm::vec2 >;
	std::vector< glm::vec3 >* normals	= new std::vector< glm::vec3 >;
	std::vector<Cara>*	caras			= new std::vector< Cara >;

	std::vector< glm::vec3 >* vertices2 = new std::vector< glm::vec3 >;
	std::vector< glm::vec2 >* uvs2 = new std::vector< glm::vec2 >;
	std::vector< glm::vec3 >* normals2 = new std::vector< glm::vec3 >;
	std::vector<Cara>*	caras2 = new std::vector< Cara >;

	loadOBJ("plane.obj",* vertices, *uvs, *normals,*caras);
	kekubo = Malla(vertices, normals, caras);
	loadOBJ("terrain.obj", *vertices2, *uvs2, *normals2, *caras2);
	terreno = Malla(vertices2, normals2, caras2);
	a = 140;
	b = 80;
	c = 40;
	t = 0;
	posAvion = new PuntoVector3D(0, 0, 0, 1);

	world_ = new World();
	
	estela = new Fuego2;
	estela->setWorld(world_);
	



	
}
Test7::~Test7()
{
}
void Test7::dibuja() {
	GLfloat ticks = glutGet(GLUT_ELAPSED_TIME);
	GLfloat tickss = glutGet(GLUT_ELAPSED_TIME);
	if (lastTimeUpdate + frecuencia <= ticks) {
		//kekubo.dibuja();
		ticks = (ticks - lastTimeUpdate - frecuencia) / 1000;
		bool eke = true;
		for (size_t i = 0; i < ejericito.size(); i++)
		{

			for (size_t j = 0; j < ejericito.size() && eke; j++) {
				if (ejericito[i]->getPos().y < 20 && ! ejericito[i]->dormido) {
					
					updateF = glutGet(GLUT_ELAPSED_TIME);
					ejericito[i]->dormido = true;

					fuego.push_back(new Fuego);
					fuego[fuego.size() - 1]->setWorld(world_);
					fuego[fuego.size() - 1]->posIni = new PuntoVector3D(ejericito[i]->getPos().x, world_->dameRandom(20,50), ejericito[i]->getPos().z, 1);
					
					
					//explosionn = new Test3(new PuntoVector3D(ejericito[i]->getPos().x, 50, ejericito[i]->getPos().z, 1));
					/*_explosion = new Explosion(PuntoVector3D(ejericito[i]->getPos().x, 50, ejericito[i]->getPos().z, 1));
					world_ = new World();
					_explosion->setWorld(world_);
					_explosion->dibuja();
					_explosion->update();*/

				}
				
				
			}
			ejericito[i]->Update(ticks);

		}
		for (size_t i = 0; i < fuego.size(); i++)
		{
			glPushMatrix();
			glTranslatef(fuego[i]->posIni->getX(), fuego[i]->posIni->getY(), fuego[i]->posIni->getZ());
			glScalef(0.2, 0.2, 0.2);
			fuego[i]->dibuja();
			glPopMatrix();
			fuego[i]->update(tickss);
		}
	for (size_t i = 0; i <  ejericito.size(); i++)
	{
		if (!ejericito[i]->dormido) {
			glColor3f(1, 1, 1);
			ejericito[i]->Render();
		}

	}

	
	t += 0.01;
	posAvion->sumar( new PuntoVector3D(0, 0, 0, 1));
	glPushMatrix();
	
	glTranslatef(C(t)->getX(), 130, C(t)->getZ());
	
	float kek = 0;
	kek = atan2((double)C’(t)->getX(), (double)C’(t)->getZ()) * 180 / 3.141519;
	glRotated(kek , 1, 1, 0);
	glPushMatrix();
	glTranslatef(0, 0, -20);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	estela->update(tickss);
	glColor3f(1.0f, 1.0f, 1.0f);
	estela->dibuja();
	glPopMatrix();
	glColor3f(0.5f, 0.0f, 0.0f);

	kekubo.dibuja();
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0f, 0.6f, 0.0f);
	glScalef(30, 10, 30);
	terreno.dibuja();
	glPopMatrix();
	}
	}
void Test7::lanzaProyectil()
{
	ejericito.push_back(new TeteraRigida(C(t)->getX(), 130, C(t)->getZ(), 20));
	ejericito[ejericito.size()-1]->setForce({ 0,-1000,0 }, 1/*, {-2.5,0,2.5}*/);
	ejericito[ejericito.size() - 1]->applyForce({ 0,-1000,0 });
	ejericito[ejericito.size() - 1]->setTorque({ 2.5,2,2.5 }, 10);
	
	
}
void Test7::apagaFuego() {
}
PuntoVector3D* Test7::C(GLfloat t) {
	return  new PuntoVector3D((a - b)*cos(t) + c*cos(t*((a - b) / b)),
		0,
		(a - b)*sin(t) - c*sin(t*((a - b) / b)), 0);
}

PuntoVector3D* Test7::C’(GLfloat t) {
	return  new PuntoVector3D(-(a - b)*sin(t) - c*((a - b) / b)*sin(t*((a - b) / b)),
		0,
		(a - b)*cos(t) - c*((a - b) / b)*cos(t*((a - b) / b)), 0);
}

PuntoVector3D* Test7::C’’(GLfloat t) {
	return new PuntoVector3D(-(a - b)*cos(t) - c*((a - b) / b)*((a - b) / b)*cos(t*((a - b) / b)),
		0,
		-(a - b)*sin(t) + c*((a - b) / b) *((a - b) / b) * sin(t*((a - b) / b)), 0);
}
