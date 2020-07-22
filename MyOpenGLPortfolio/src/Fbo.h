#pragma once

#include<glad/glad.h>
#include<iostream>

class Fbo {
public:
	unsigned int width;
	unsigned int height;
	unsigned int textureColorBuffer;
private:
	unsigned int frameBufferObject;
	unsigned int renderBufferObject;
public:
	Fbo();
	Fbo(unsigned int width, unsigned int height);
	void use();
	void stop();
private:
};