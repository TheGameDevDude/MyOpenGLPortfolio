#include "ReflectionProb.h"

ReflectionProb::ReflectionProb(int size) {
	this->size = size;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (int i = 0; i < 6; i++) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	glGenFramebuffers(1, &frameBufferObject);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);

	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	
	glGenRenderbuffers(1, &renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, size, size);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ReflectionProb::render(Camera camera, const std::function<void(Camera& camera)>& render) {
	glViewport(0, 0, size, size);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//render all 6 direction to create a cubemap
	for (int i = 0; i < 6; i++) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, textureID, 0);
		reflectionCamera.position = camera.position;
		reflectionCamera.aspectRatio = 1;
		reflectionCamera.fov = 90.0f;
		cameraSwitch(i);
		render(reflectionCamera);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ReflectionProb::cameraSwitch(int i) {
	switch (i)
	{
	case 0:
		reflectionCamera.pitch = 0;
		reflectionCamera.yaw = 90;
		break;
	case 1:
		reflectionCamera.pitch = 0;
		reflectionCamera.yaw = -90;
		break;
	case 2:
		reflectionCamera.pitch = -90;
		reflectionCamera.yaw = 180;
		break;
	case 3:
		reflectionCamera.pitch = 90;
		reflectionCamera.yaw = 180;
		break;
	case 4:
		reflectionCamera.pitch = 0;
		reflectionCamera.yaw = 180;
		break;
	case 5:
		reflectionCamera.pitch = 0;
		reflectionCamera.yaw = 0;
		break;
	}
}