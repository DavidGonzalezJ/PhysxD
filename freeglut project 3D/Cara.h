#pragma once
#include "VerticeNormal.h"

class Cara {
private:
	int numeroVertices;
	VerticeNormal** arrayVerticeNormal;
public:
	Cara(int nV, VerticeNormal** aVN);
	~Cara();
	int getNumeroVertices();
	int getIndiceVerticeK(int k);
	int getIndiceNormalK(int k);
};
