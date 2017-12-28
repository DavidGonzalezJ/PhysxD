#pragma once
#include "RigidBody.h"
#include <vector>
#include "Malla.h"
class Test7
{
public:
	Test7();
	~Test7();
	virtual void dibuja();
private:
	std::vector<RigidBody*> ejericito;
	GLfloat lastTimeUpdate = 0;
	GLfloat frecuencia = 20;
	Malla kekubo;
};
struct shitNigga {
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
};

