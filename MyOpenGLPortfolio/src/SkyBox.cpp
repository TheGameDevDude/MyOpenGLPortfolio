#include "SkyBox.h"

SkyBox::SkyBox() {
	faces = {
		"res/skyboxtextures/blueMountain/right.jpg",
		"res/skyboxtextures/blueMountain/left.jpg",
		"res/skyboxtextures/blueMountain/top.jpg",
		"res/skyboxtextures/blueMountain/bottom.jpg",
		"res/skyboxtextures/blueMountain/front.jpg",
		"res/skyboxtextures/blueMountain/back.jpg"
	};

	skyBoxShader = Shader("res/shaders/SkyBoxShader/vertexShader.shader", "res/shaders/SkyBoxShader/fragmentShader.shader");
	textureID = TextureLoader::loadCubemap(faces);
	setupCube();
}

void SkyBox::render(Camera camera, Controls controls) {
	glm::mat4 perspectiveProjection = camera.getPerspectiveProjectionMatrix();
	glm::mat4 view = glm::mat4(glm::mat3(camera.getViewMatrix()));
	
	skyBoxShader.use();
	glDepthFunc(GL_LEQUAL);
	skyBoxShader.setMat4("projection", perspectiveProjection);
	skyBoxShader.setMat4("view", view);
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	skyBoxShader.setInt("skybox", 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
	skyBoxShader.stop();
}

void SkyBox::setupCube() {
	float skyboxVertices[] = {        
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}