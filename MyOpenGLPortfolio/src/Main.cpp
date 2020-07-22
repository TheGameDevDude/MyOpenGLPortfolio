#include "Window.h"
#include "Camera.h"
#include "Controls.h"
#include "Renderer.h"
#include "SkyBox.h"
#include "FboRenderer.h"
#include "GameObjects.h"
#include "ReflectionProb.h"
#include <functional>

int main() {
	Window windowManager(1366, 768, "MyOpenGLPortfolio");
	Controls controls(windowManager.window);
	Camera camera(glm::vec3(0.0f, 0.0f, 2.0f), 0.0f, 0.0f, 0.0f);
	FboRenderer fboRenderer(windowManager.WIDTH, windowManager.HEIGHT);
	Renderer renderer;
	SkyBox skybox;
	GameObjects gameObjects;
	ReflectionProb reflectionProb(512);

	auto tick = [&](float deltaTime) {
		camera.tick(controls, deltaTime);
		gameObjects.tick(deltaTime);
	};

	//rendering for reflection probe
	auto render = [&](Camera& camera) {
		renderer.cameraCalculation(camera, controls);
		renderer.render_diffuse_Emissive_NLShader(gameObjects.crate);
		renderer.render_diffuse_NLShaderInstanced(gameObjects.nanoSuits);
		renderer.render_grass_NLShaderInstanced(gameObjects.grass);
		renderer.render_diffuse_NLShader(gameObjects.brick);
		renderer.render_diffuse_NLShader(gameObjects.coolerbrick);
		renderer.render_diffuse_NLShader(gameObjects.magicwood);
		skybox.render(camera, controls);
	};

	//rendering with refelction using reflection probe as a skybox
	auto renderWithReflections = [&](float deltaTime, Camera& camera) {
		renderer.cameraCalculation(camera, controls);
		renderer.lightingCalculation(camera, controls, deltaTime);
		renderer.render_diffuse_Specular_Emissive_Shader(gameObjects.crate, 32.0f);
		renderer.render_diffuse_Specular_Reflective_ShaderInstanced(gameObjects.nanoSuits,32.0f, reflectionProb);
		renderer.render_grass_ShaderInstanced(gameObjects.grass);
		renderer.render_diffuse_Specular_Normal_Shader(gameObjects.brick, 32.0f);
		renderer.render_diffuse_Specular_Normal_Parallax_Shader(gameObjects.coolerbrick, 32.0f, 0.1f);
		renderer.render_diffuse_Specular_Normal_Parallax_Shader(gameObjects.magicwood, 32.0f, 0.1f);
		skybox.render(camera, controls);
	};

	double prevTime = glfwGetTime();
	while (!glfwWindowShouldClose(windowManager.window)) {
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - prevTime);
		prevTime = currentTime;

		tick(deltaTime);
		reflectionProb.render(camera, render);
		fboRenderer.useNormalFbo();
		renderWithReflections(deltaTime, camera);
		fboRenderer.stopNormalFbo();
		fboRenderer.renderNormalFbo(true, 0.08f);

		glfwSwapBuffers(windowManager.window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}