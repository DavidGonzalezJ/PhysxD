#pragma once
#include "Malla.h"
class Cubo : public Malla
{
public:
	Cubo(int tam);

	virtual ~Cubo();
	virtual void dibuja();
	void cambiaSoliAWire(){
		solido = !solido;
	}
	bool solido = true;
	int tam;
	//GLfloat size;
};