 
#ifndef Malla_H_
#define Malla_H_

#include "PuntoVector3D.h"
#include "Cara.h"
#include "glm\glm.hpp"
#include <vector>

class Malla {	 
    protected:
        int numeroVertices;
		std::vector< glm::vec3>* vertices;
        int numeroNormales;
		std::vector< glm::vec3>* normales;
        int numeroCaras;
		std::vector<Cara>* cara;
		GLboolean mode;
    public:
		Malla(std::vector< glm::vec3>* v, std::vector< glm::vec3>* n,std::vector<Cara>* c=nullptr) {
			numeroVertices = v->size();
			vertices = v;
			numeroNormales = n->size();
			normales = n;
			numeroCaras = c->size();
			cara = c;
		}
		Malla() {}
		~Malla() {
			
		}
		inline int getNumeroVertices() {
			return numeroVertices;
		}
		inline int getNumeroNormales() {
			return numeroNormales;
		}
		inline int getNumeroCaras() {
			return numeroCaras;
		}
		inline void changeMode(){ mode = !mode; };
		virtual void dibuja() {
			glMatrixMode(GL_MODELVIEW);
			for (int i = 0; i < numeroCaras; i++) {
				if (mode)
					glBegin(GL_POLYGON);
				else
					glBegin(GL_LINE_STRIP);

				for (int j = 0; j < cara->at(i).getNumeroVertices(); j++) {
					int iN = cara->at(i).getIndiceNormalK(j);
					int iV = cara->at(i).getIndiceVerticeK(j);
					glNormal3f(normales->at(iN).x, normales->at(iN).y, normales->at(iN).z);
					glVertex3f(vertices->at(iV).x, vertices->at(iV).y, vertices->at(iV).z);
				}
				glEnd();
			}
		}
};
#endif
