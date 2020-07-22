#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() {
	direction = glm::vec3();
	ambient = glm::vec3();
	diffuse = glm::vec3();
	specular = glm::vec3();
}

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}
