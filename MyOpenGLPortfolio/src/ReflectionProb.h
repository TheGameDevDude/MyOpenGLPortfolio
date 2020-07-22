#pragma once

#include <glad/glad.h>
#include <iostream>
#include <functional>
#include "Camera.h"

class ReflectionProb {
public:
	unsigned int textureID;
private:
	Camera reflectionCamera;
	unsigned int frameBufferObject;
	unsigned int renderBufferObject;
	unsigned int size;
public:
	ReflectionProb(int size);
	void render(Camera camera, const std::function<void(Camera& camera)>& render);
private:
	void cameraSwitch(int i);
};
