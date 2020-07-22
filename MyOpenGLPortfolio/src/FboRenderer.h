#pragma once

#include"Shader.h"
#include"Fbo.h"

#include<glad/glad.h>

class FboRenderer {
public:
private:
	Fbo normalFbo;
	Shader normalFboShader;
	unsigned int quadVAO;
	unsigned int quadVBO;
	int screenWidth;
	int screenHeight;
public:
	FboRenderer(int screenWidth, int screenHeight);
	void useNormalFbo();
	void stopNormalFbo();
	void renderNormalFbo(bool hdr, float exposure);
private:
};
