 
#include "Malla.h"
 
void Malla::dibuja() {	 	 
	glMatrixMode(GL_MODELVIEW);
	for (int i = 0; i<numeroCaras; i++) {
		if (mode)
			glBegin(GL_POLYGON);
		else 
			glBegin(GL_LINE_STRIP);

		for (int j = 0; j<cara->at(i).getNumeroVertices(); j++) {
			int iN = cara->at(i).getIndiceNormalK(j);
			int iV = cara->at(i).getIndiceVerticeK(j);
			glNormal3f(normales->at(iN).x, normales->at(iN).y, normales->at(iN).z);
			glVertex3f(vertices->at(iV).x, vertices->at(iV).y, vertices->at(iV).z);
		}
		glEnd();
	}
}

 

