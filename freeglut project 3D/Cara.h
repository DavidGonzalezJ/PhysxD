 
#ifndef Cara_H_
#define Cara_H_

#include "VerticeNormal.h"
#include <vector>
 
class Cara {
	private:
		int numeroVertices;
        std::vector<VerticeNormal> arrayVerticeNormal;
    public:
        Cara(int nV, std::vector<VerticeNormal>& aVN) {
			numeroVertices = nV;
			arrayVerticeNormal = aVN;
		}
		~Cara() {

		}
		inline int getNumeroVertices() {
			return numeroVertices;
		}
		inline int getIndiceVerticeK(int k) {
			return arrayVerticeNormal[k].getIV();
		}
		inline int getIndiceNormalK(int k) {
			return arrayVerticeNormal[k].getIN();
		}
};
#endif
