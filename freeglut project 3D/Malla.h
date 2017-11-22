 
#ifndef Malla_H_
#define Malla_H_

#include "PuntoVector3D.h"
#include "Cara.h"
#include "Objeto3D.h"

class Malla:
	public Objeto3D {	 
    protected:
        int numeroVertices;
        PuntoVector3D** vertice;
        int numeroNormales;
        PuntoVector3D** normal;
        int numeroCaras;
        Cara** cara;  
		bool modo;
    public:
		Malla(int nV, int nN, int nC, PuntoVector3D** v, PuntoVector3D** n, Cara** c, GLfloat r = 0, GLfloat g = 0, GLfloat b = 0);
        Malla();
        ~Malla();
        int getNumeroVertices();
        int getNumeroNormales();
        int getNumeroCaras();         
        virtual void dibuja();  
		virtual void swDrawMode(){
			modo = !modo;
		}
};
#endif
