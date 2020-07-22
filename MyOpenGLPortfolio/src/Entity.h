#pragma once

#include <glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "ModelNames.h"

class Entity {
public:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 orientation;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	//for rendering which model (used as an enum) "Models" class has all the models use this to access models
	int modelName;
private:
	glm::mat4 modelMatrix;
public:
	Entity();
	Entity(int modelName, glm::vec3 position, glm::vec3 scale, glm::vec3 orientation);
	void orderOfRotation(int x, int y, int z);
	glm::mat4 getModelMatrix();
private:
};