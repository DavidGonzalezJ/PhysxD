#include "Cubo.h"
Cubo::Cubo(int tam) :tam(tam){
	numeroVertices = 8;
	vertice = new PuntoVector3D*[numeroVertices];
	numeroNormales = 8;
	normal = new PuntoVector3D*[numeroNormales];
	numeroCaras = 6;
	cara = new Cara*[numeroCaras];
	//modo = false;

	// Vértices  
	vertice[0] = new PuntoVector3D(-0.5f*tam, 0.5f*tam, 0.5f*tam, 1);
	vertice[1] = new PuntoVector3D(-0.5f*tam, -0.5f*tam, 0.5f*tam, 1);
	vertice[2] = new PuntoVector3D(0.5f*tam, -0.5f*tam, 0.5f*tam, 1);
	vertice[3] = new PuntoVector3D(0.5f*tam, 0.5f*tam, 0.5f*tam, 1);
	vertice[4] = new PuntoVector3D(-0.5f*tam, 0.5f*tam, -0.5f*tam, 1);
	vertice[5] = new PuntoVector3D(-0.5f*tam, -0.5f*tam, -0.5f*tam, 1);
	vertice[6] = new PuntoVector3D(0.5f*tam, -0.5f*tam, -0.5f*tam, 1);
	vertice[7] = new PuntoVector3D(0.5f*tam, 0.5f*tam, -0.5f*tam, 1);

	// Normales  
	normal[0] = new PuntoVector3D(0, 0, 1, 0);
	normal[1] = new PuntoVector3D(1, 0, 0, 0);
	normal[2] = new PuntoVector3D(0, 0, -1, 0);
	normal[3] = new PuntoVector3D(-1, 0, 0, 0);
	normal[4] = new PuntoVector3D(0, 1, 0, 0);
	normal[5] = new PuntoVector3D(0, -1, 0, 0);


	// Caras
	VerticeNormal** aVN = new VerticeNormal*[4];
	aVN[0] = new VerticeNormal(0, 0);
	aVN[1] = new VerticeNormal(1, 0);
	aVN[2] = new VerticeNormal(2, 0);
	aVN[3] = new VerticeNormal(3, 0);

	cara[0] = new Cara(4, aVN);

	aVN = new VerticeNormal*[4];
	aVN[0] = new VerticeNormal(3, 1);
	aVN[1] = new VerticeNormal(2, 1);
	aVN[2] = new VerticeNormal(6, 1);
	aVN[3] = new VerticeNormal(7, 1);

	cara[1] = new Cara(4, aVN);

	aVN = new VerticeNormal*[4];
	aVN[0] = new VerticeNormal(7, 2);
	aVN[1] = new VerticeNormal(6, 2);
	aVN[2] = new VerticeNormal(5, 2);
	aVN[3] = new VerticeNormal(4, 2);

	cara[2] = new Cara(4, aVN);

	aVN = new VerticeNormal*[4];
	aVN[0] = new VerticeNormal(4, 3);
	aVN[1] = new VerticeNormal(5, 3);
	aVN[2] = new VerticeNormal(1, 3);
	aVN[3] = new VerticeNormal(0, 3);

	cara[3] = new Cara(4, aVN);

	aVN = new VerticeNormal*[4];
	aVN[0] = new VerticeNormal(4, 4);
	aVN[1] = new VerticeNormal(0, 4);
	aVN[2] = new VerticeNormal(3, 4);
	aVN[3] = new VerticeNormal(7, 4);

	cara[4] = new Cara(4, aVN);

	aVN = new VerticeNormal*[4];
	aVN[0] = new VerticeNormal(1, 5);
	aVN[1] = new VerticeNormal(5, 5);
	aVN[2] = new VerticeNormal(6, 5);
	aVN[3] = new VerticeNormal(2, 5);

	cara[5] = new Cara(4, aVN);

}
Cubo::~Cubo()
{
}

void Cubo::dibuja(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//Cargar m como matriz actual de modelado-vista
	glMultMatrixf(mt->m);
	Malla::dibuja();
	glPopMatrix();
}