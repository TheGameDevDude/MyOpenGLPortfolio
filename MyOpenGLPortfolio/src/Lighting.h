#pragma once

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Shader.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <vector>

class Lighting {
public:
	DirectionalLight directionalLight;
	std::vector<PointLight> pointLights;
	std::vector<SpotLight> spotLights;
private:
public:
	Lighting();
	void doLightingCalculation(Shader shader);
	void tick(float deltaTime,Camera camera);
private:
};