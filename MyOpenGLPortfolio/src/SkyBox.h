#pragma once

#include "TextureLoader.h"
#include "Shader.h"
#include "Camera.h"
#include "Controls.h"

#include<iostream>
#include<vector>

class SkyBox {
public:
	unsigned int textureID;
private:
	std::vector<std::string> faces;
	Shader skyBoxShader;
	unsigned int skyboxVAO, skyboxVBO;
public:
	SkyBox();
	void render(Camera camera, Controls controls);
private:
	void setupCube();
};
