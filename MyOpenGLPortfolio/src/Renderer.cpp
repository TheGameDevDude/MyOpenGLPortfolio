#include "Renderer.h"

Renderer::Renderer() {
	diffuse_Emissive_NLShader = Shader("res/shaders/DiffuseEmissiveNLShader/vertexShader.shader", "res/shaders/DiffuseEmissiveNLShader/fragmentShader.shader");
	diffuse_Emissive_NLShaderInstanced = Shader("res/shaders/DiffuseEmissiveNLShaderInstanced/vertexShader.shader", "res/shaders/DiffuseEmissiveNLShaderInstanced/fragmentShader.shader");

	diffuse_NLShader = Shader("res/shaders/DiffuseNLShader/vertexShader.shader", "res/shaders/DiffuseNLShader/fragmentShader.shader");
	diffuse_NLShaderInstanced = Shader("res/shaders/DiffuseNLShaderInstanced/vertexShader.shader", "res/shaders/DiffuseNLShaderInstanced/fragmentShader.shader");

	diffuse_Specular_Emissive_Shader = Shader("res/shaders/DiffuseSpecularEmissiveShader/vertexShader.shader", "res/shaders/DiffuseSpecularEmissiveShader/fragmentShader.shader");
	diffuse_Specular_Emissive_ShaderInstanced = Shader("res/shaders/DiffuseSpecularEmissiveShaderInstanced/vertexShader.shader", "res/shaders/DiffuseSpecularEmissiveShaderInstanced/fragmentShader.shader");

	diffuse_Specular_Shader = Shader("res/shaders/DiffuseSpecularShader/vertexShader.shader", "res/shaders/DiffuseSpecularShader/fragmentShader.shader");
	diffuse_Specular_ShaderInstanced = Shader("res/shaders/DiffuseSpecularShaderInstanced/vertexShader.shader", "res/shaders/DiffuseSpecularShaderInstanced/fragmentShader.shader");
	
	diffuse_Specular_ReflectiveShaderInstanced = Shader("res/shaders/DiffuseSpecularReflectiveShaderInstanced/vertexShader.shader", "res/shaders/DiffuseSpecularReflectiveShaderInstanced/fragmentShader.shader");
	
	grass_ShaderInstanced = Shader("res/shaders/GrassShader/vertexShader.shader", "res/shaders/GrassShader/fragmentShader.shader");
	grass_NLShaderInstanced = Shader("res/shaders/GrassNLShader/vertexShader.shader", "res/shaders/GrassNLShader/fragmentShader.shader");

	diffuse_Specular_Normal_Shader = Shader("res/shaders/DiffuseSpecularNormalShader/vertexShader.shader", "res/shaders/DiffuseSpecularNormalShader/fragmentShader.shader");
	diffuse_Specular_Normal_Parallax_Shader = Shader("res/shaders/DiffuseSpecularNormalParallaxShader/vertexShader.shader", "res/shaders/DiffuseSpecularNormalParallaxShader/fragmentShader.shader");
}

void Renderer::cameraCalculation(Camera& camera, Controls controls) {
	glm::mat4 perspectiveProjection = camera.getPerspectiveProjectionMatrix();
	glm::mat4 view = camera.getViewMatrix();

	diffuse_Emissive_NLShader.use();
	diffuse_Emissive_NLShader.setMat4("projection", perspectiveProjection);
	diffuse_Emissive_NLShader.setMat4("view", view);
	diffuse_Emissive_NLShader.stop();

	diffuse_Emissive_NLShaderInstanced.use();
	diffuse_Emissive_NLShaderInstanced.setMat4("projection", perspectiveProjection);
	diffuse_Emissive_NLShaderInstanced.setMat4("view", view);
	diffuse_Emissive_NLShaderInstanced.stop();

	diffuse_NLShader.use();
	diffuse_NLShader.setMat4("projection", perspectiveProjection);
	diffuse_NLShader.setMat4("view", view);
	diffuse_NLShader.stop();

	diffuse_NLShaderInstanced.use();
	diffuse_NLShaderInstanced.setMat4("projection", perspectiveProjection);
	diffuse_NLShaderInstanced.setMat4("view", view);
	diffuse_NLShaderInstanced.stop();

	diffuse_Specular_Emissive_Shader.use();
	diffuse_Specular_Emissive_Shader.setMat4("projection", perspectiveProjection);
	diffuse_Specular_Emissive_Shader.setMat4("view", view);
	diffuse_Specular_Emissive_Shader.stop();

	diffuse_Specular_Shader.use();
	diffuse_Specular_Shader.setMat4("projection", perspectiveProjection);
	diffuse_Specular_Shader.setMat4("view", view);
	diffuse_Specular_Shader.stop();

	diffuse_Specular_Emissive_ShaderInstanced.use();
	diffuse_Specular_Emissive_ShaderInstanced.setMat4("projection", perspectiveProjection);
	diffuse_Specular_Emissive_ShaderInstanced.setMat4("view", view);
	diffuse_Specular_Emissive_ShaderInstanced.stop();

	diffuse_Specular_ShaderInstanced.use();
	diffuse_Specular_ShaderInstanced.setMat4("projection", perspectiveProjection);
	diffuse_Specular_ShaderInstanced.setMat4("view", view);
	diffuse_Specular_ShaderInstanced.stop();

	diffuse_Specular_ReflectiveShaderInstanced.use();
	diffuse_Specular_ReflectiveShaderInstanced.setMat4("projection", perspectiveProjection);
	diffuse_Specular_ReflectiveShaderInstanced.setMat4("view", view);
	diffuse_Specular_ReflectiveShaderInstanced.stop();

	grass_ShaderInstanced.use();
	grass_ShaderInstanced.setMat4("projection", perspectiveProjection);
	grass_ShaderInstanced.setMat4("view", view);
	grass_ShaderInstanced.stop();

	grass_NLShaderInstanced.use();
	grass_NLShaderInstanced.setMat4("projection", perspectiveProjection);
	grass_NLShaderInstanced.setMat4("view", view);
	grass_NLShaderInstanced.stop();

	diffuse_Specular_Normal_Shader.use();
	diffuse_Specular_Normal_Shader.setMat4("projection", perspectiveProjection);
	diffuse_Specular_Normal_Shader.setMat4("view", view);
	diffuse_Specular_Normal_Shader.stop();

	diffuse_Specular_Normal_Parallax_Shader.use();
	diffuse_Specular_Normal_Parallax_Shader.setMat4("projection", perspectiveProjection);
	diffuse_Specular_Normal_Parallax_Shader.setMat4("view", view);
	diffuse_Specular_Normal_Parallax_Shader.stop();
}

void Renderer::lightingCalculation(Camera camera, Controls controls, float deltaTime) {
	lighting.tick(deltaTime, camera);

	diffuse_Specular_Emissive_Shader.use();
	lighting.doLightingCalculation(diffuse_Specular_Emissive_Shader);
	diffuse_Specular_Emissive_Shader.stop();

	diffuse_Specular_Shader.use();
	lighting.doLightingCalculation(diffuse_Specular_Shader);
	diffuse_Specular_Shader.stop();

	diffuse_Specular_Emissive_ShaderInstanced.use();
	lighting.doLightingCalculation(diffuse_Specular_Emissive_ShaderInstanced);
	diffuse_Specular_Emissive_ShaderInstanced.stop();

	diffuse_Specular_ShaderInstanced.use();
	lighting.doLightingCalculation(diffuse_Specular_ShaderInstanced);
	diffuse_Specular_ShaderInstanced.stop();

	diffuse_Specular_ReflectiveShaderInstanced.use();
	lighting.doLightingCalculation(diffuse_Specular_ReflectiveShaderInstanced);
	diffuse_Specular_ReflectiveShaderInstanced.stop();

	grass_ShaderInstanced.use();
	lighting.doLightingCalculation(grass_ShaderInstanced);
	grass_ShaderInstanced.stop();

	diffuse_Specular_Normal_Shader.use();
	lighting.doLightingCalculation(diffuse_Specular_Normal_Shader);
	diffuse_Specular_Normal_Shader.stop();

	diffuse_Specular_Normal_Parallax_Shader.use();
	lighting.doLightingCalculation(diffuse_Specular_Normal_Parallax_Shader);
	diffuse_Specular_Normal_Parallax_Shader.stop();
}

void Renderer::render_diffuse_Emissive_NLShader(Entity& entity) {
	diffuse_Emissive_NLShader.use();
	glm::mat4 model = entity.getModelMatrix();
	diffuse_Emissive_NLShader.setMat4("model", model);
	models.models[entity.modelName].draw(diffuse_Emissive_NLShader);
	diffuse_Emissive_NLShader.stop();
}

void Renderer::render_diffuse_Emissive_NLShader(std::vector<Entity> entities) {
	diffuse_Emissive_NLShader.use();
	models.models[entities[0].modelName].draw(diffuse_Emissive_NLShader, entities);
	diffuse_Emissive_NLShader.stop();
}

void Renderer::render_diffuse_Emissive_NLShaderInstanced(std::vector<Entity> entities) {
	diffuse_Emissive_NLShaderInstanced.use();
	models.models[entities[0].modelName].drawInstanced(diffuse_Emissive_NLShaderInstanced, entities);
	diffuse_Emissive_NLShaderInstanced.stop();
}

void Renderer::render_diffuse_NLShader(Entity& entity) {
	diffuse_NLShader.use();
	glm::mat4 model = entity.getModelMatrix();
	diffuse_NLShader.setMat4("model", model);
	models.models[entity.modelName].draw(diffuse_NLShader);
	diffuse_NLShader.stop();
}

void Renderer::render_diffuse_NLShader(std::vector<Entity> entities) {
	diffuse_NLShader.use();
	models.models[entities[0].modelName].draw(diffuse_NLShader, entities);
	diffuse_NLShader.stop();
}

void Renderer::render_diffuse_NLShaderInstanced(std::vector<Entity> entities) {
	diffuse_NLShaderInstanced.use();
	models.models[entities[0].modelName].drawInstanced(diffuse_NLShaderInstanced, entities);
	diffuse_NLShaderInstanced.stop();
}

void Renderer::render_diffuse_Specular_Emissive_Shader(Entity& entity,float shininess) {
	diffuse_Specular_Emissive_Shader.use();
	glm::mat4 model = entity.getModelMatrix();
	diffuse_Specular_Emissive_Shader.setMat4("model", model);
	diffuse_Specular_Emissive_Shader.setFloat("material.shininess", shininess);
	models.models[entity.modelName].draw(diffuse_Specular_Emissive_Shader);
	diffuse_Specular_Emissive_Shader.stop();
}

void Renderer::render_diffuse_Specular_Emissive_Shader(std::vector<Entity> entities, float shininess) {
	diffuse_Specular_Emissive_Shader.use();
	diffuse_Specular_Emissive_Shader.setFloat("material.shininess", shininess);
	models.models[entities[0].modelName].draw(diffuse_Specular_Emissive_Shader, entities);
	diffuse_Specular_Emissive_Shader.stop();
}

void Renderer::render_diffuse_Specular_Emissive_ShaderInstanced(std::vector<Entity> entities, float shininess) {
	diffuse_Specular_Emissive_ShaderInstanced.use();
	diffuse_Specular_Emissive_ShaderInstanced.setFloat("material.shininess", shininess);
	models.models[entities[0].modelName].drawInstanced(diffuse_Specular_Emissive_ShaderInstanced, entities);
	diffuse_Specular_Emissive_ShaderInstanced.stop();
}

void Renderer::render_diffuse_Specular_Shader(Entity& entity,float shininess) {
	diffuse_Specular_Shader.use();
	glm::mat4 model = entity.getModelMatrix();
	diffuse_Specular_Shader.setMat4("model", model);
	diffuse_Specular_Shader.setFloat("material.shininess", shininess);
	models.models[entity.modelName].draw(diffuse_Specular_Shader);
	diffuse_Specular_Shader.stop();
}

void Renderer::render_diffuse_Specular_Shader(std::vector<Entity> entities, float shininess) {
	diffuse_Specular_Shader.use();
	diffuse_Specular_Shader.setFloat("material.shininess", shininess);
	models.models[entities[0].modelName].draw(diffuse_Specular_Shader, entities);
	diffuse_Specular_Shader.stop();
}

void Renderer::render_diffuse_Specular_ShaderInstanced(std::vector<Entity> entities, float shininess) {
	diffuse_Specular_ShaderInstanced.use();
	diffuse_Specular_ShaderInstanced.setFloat("material.shininess", shininess);
	models.models[entities[0].modelName].drawInstanced(diffuse_Specular_ShaderInstanced, entities);
	diffuse_Specular_ShaderInstanced.stop();
}

void Renderer::render_diffuse_Specular_Reflective_ShaderInstanced(std::vector<Entity> entities, float shininess, ReflectionProb reflectionProb) {
	diffuse_Specular_ReflectiveShaderInstanced.use();
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_CUBE_MAP, reflectionProb.textureID);
	diffuse_Specular_ReflectiveShaderInstanced.setInt("reflectionCube", 5);
	diffuse_Specular_ReflectiveShaderInstanced.setFloat("material.shininess", shininess);
	models.models[entities[0].modelName].drawInstanced(diffuse_Specular_ShaderInstanced, entities);
	diffuse_Specular_ReflectiveShaderInstanced.stop();
}

void Renderer::render_grass_ShaderInstanced(std::vector<Entity> entities) {
	glDisable(GL_CULL_FACE);
	grass_ShaderInstanced.use();
	models.models[entities[0].modelName].drawInstanced(grass_ShaderInstanced, entities);
	grass_ShaderInstanced.stop();
	glEnable(GL_CULL_FACE);
}

void Renderer::render_grass_NLShaderInstanced(std::vector<Entity> entities) {
	glDisable(GL_CULL_FACE);
	grass_NLShaderInstanced.use();
	models.models[entities[0].modelName].drawInstanced(grass_NLShaderInstanced, entities);
	grass_NLShaderInstanced.stop();
	glEnable(GL_CULL_FACE);
}

void Renderer::render_diffuse_Specular_Normal_Shader(Entity& entity, float shininess) {
	diffuse_Specular_Normal_Shader.use();
	glm::mat4 model = entity.getModelMatrix();
	diffuse_Specular_Normal_Shader.setMat4("model", model);
	diffuse_Specular_Normal_Shader.setFloat("material.shininess", shininess);
	models.models[entity.modelName].draw(diffuse_Specular_Normal_Shader);
	diffuse_Specular_Normal_Shader.stop();
}

void Renderer::render_diffuse_Specular_Normal_Parallax_Shader(Entity& entity, float shininess, float heightScale) {
	diffuse_Specular_Normal_Parallax_Shader.use();
	glm::mat4 model = entity.getModelMatrix();
	diffuse_Specular_Normal_Parallax_Shader.setMat4("model", model);
	diffuse_Specular_Normal_Parallax_Shader.setFloat("heightScale", heightScale);
	diffuse_Specular_Normal_Parallax_Shader.setFloat("material.shininess", shininess);
	models.models[entity.modelName].draw(diffuse_Specular_Normal_Parallax_Shader);
	diffuse_Specular_Normal_Parallax_Shader.stop();
}