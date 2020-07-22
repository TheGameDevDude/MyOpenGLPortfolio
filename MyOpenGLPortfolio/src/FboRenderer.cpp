#include "FboRenderer.h"

FboRenderer::FboRenderer(int screenWidth, int screenHeight) {
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	normalFboShader = Shader("res/shaders/FboShader/vertexShader.shader", "res/shaders/FboShader/fragmentShader.shader");
	normalFbo = Fbo(screenWidth, screenHeight);

	float quadVertices[] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void FboRenderer::useNormalFbo() {
	normalFbo.use();
}

void FboRenderer::stopNormalFbo() {
	normalFbo.stop();
	glViewport(0, 0, screenWidth, screenHeight);
}

void FboRenderer::renderNormalFbo(bool hdr, float exposure) {
	normalFboShader.use();
	glBindVertexArray(quadVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, normalFbo.textureColorBuffer);
	normalFboShader.setInt("screenTexture", 0);
	normalFboShader.setBool("hdr", hdr);
	normalFboShader.setFloat("exposure", exposure);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	normalFboShader.stop();
}