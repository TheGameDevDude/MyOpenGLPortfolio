#include "Lighting.h"

Lighting::Lighting() {
	directionalLight = DirectionalLight(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.2f, 0.2f, 0.2f));
	pointLights.push_back(PointLight::PointLight(glm::vec3(-0.5f, 3.5f, 0), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.2f, 0.03f, 0.03f));
	spotLights.push_back(SpotLight::SpotLight(glm::vec3(), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(10.0f, 10.0f, 10.0f), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)), 0.5f, 0.09f, 0.032f));
}

void Lighting::doLightingCalculation(Shader shader) {
	shader.setVec3("directionalLight.direction", directionalLight.direction);
	shader.setVec3("directionalLight.ambient", directionalLight.ambient);
	shader.setVec3("directionalLight.diffuse", directionalLight.diffuse);
	shader.setVec3("directionalLight.specular", directionalLight.specular);

	shader.setInt("numberOfLights.numberOfPointLights", pointLights.size());
	shader.setInt("numberOfLights.numberOfSpotLights", spotLights.size());

	for (unsigned int i = 0; i < pointLights.size(); i++) {
		char buffer[64];

		sprintf_s(buffer, "pointLight[%i].position", i);
		shader.setVec3(buffer, pointLights[i].position);

		sprintf_s(buffer, "pointLight[%i].ambient", i);
		shader.setVec3(buffer, pointLights[i].ambient);

		sprintf_s(buffer, "pointLight[%i].diffuse", i);
		shader.setVec3(buffer, pointLights[i].diffuse);

		sprintf_s(buffer, "pointLight[%i].specular", i);
		shader.setVec3(buffer, pointLights[i].specular);

		sprintf_s(buffer, "pointLight[%i].constantValue", i);
		shader.setFloat(buffer, pointLights[i].constantValue);

		sprintf_s(buffer, "pointLight[%i].linearValue", i);
		shader.setFloat(buffer, pointLights[i].linearValue);

		sprintf_s(buffer, "pointLight[%i].quadraticValue", i);
		shader.setFloat(buffer, pointLights[i].quadraticValue);
	}

	for (unsigned int i = 0; i < spotLights.size(); i++) {
		char buffer[64];

		sprintf_s(buffer, "spotLight[%i].position", i);
		shader.setVec3(buffer, spotLights[i].position);

		sprintf_s(buffer, "spotLight[%i].direction", i);
		shader.setVec3(buffer, spotLights[i].direction);

		sprintf_s(buffer, "spotLight[%i].cutOff", i);
		shader.setFloat(buffer, spotLights[i].cutOff);

		sprintf_s(buffer, "spotLight[%i].outerCutOff", i);
		shader.setFloat(buffer, spotLights[i].outerCutOff);

		sprintf_s(buffer, "spotLight[%i].ambient", i);
		shader.setVec3(buffer, spotLights[i].ambient);

		sprintf_s(buffer, "spotLight[%i].diffuse", i);
		shader.setVec3(buffer, spotLights[i].diffuse);

		sprintf_s(buffer, "spotLight[%i].specular", i);
		shader.setVec3(buffer, spotLights[i].specular);

		sprintf_s(buffer, "spotLight[%i].constantValue", i);
		shader.setFloat(buffer, spotLights[i].constantValue);

		sprintf_s(buffer, "spotLight[%i].linearValue", i);
		shader.setFloat(buffer, spotLights[i].linearValue);

		sprintf_s(buffer, "spotLight[%i].quadraticValue", i);
		shader.setFloat(buffer, spotLights[i].quadraticValue);
	}
}


void Lighting::tick(float deltaTime,Camera camera) {
	spotLights[0].position = camera.position;
	spotLights[0].direction = camera.forward;
}