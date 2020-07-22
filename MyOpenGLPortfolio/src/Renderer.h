#pragma once

#include "Shader.h"
#include "Lighting.h"
#include "Models.h"
#include "Camera.h"
#include "Controls.h"
#include "Entity.h"
#include "ModelNames.h"
#include "ReflectionProb.h"

class Renderer {
public:
private:
	//no lighting shader
	Shader diffuse_Emissive_NLShader;
	Shader diffuse_Emissive_NLShaderInstanced;

	//no lighting shader
	Shader diffuse_NLShader;
	Shader diffuse_NLShaderInstanced;

	Shader diffuse_Specular_Emissive_Shader;
	Shader diffuse_Specular_Emissive_ShaderInstanced;
	
	Shader diffuse_Specular_Shader;
	Shader diffuse_Specular_ShaderInstanced;

	Shader diffuse_Specular_ReflectiveShaderInstanced;

	//with transperancy for grass
	Shader grass_ShaderInstanced;
	//no lighting shader
	Shader grass_NLShaderInstanced;

	Shader diffuse_Specular_Normal_Shader;
	Shader diffuse_Specular_Normal_Parallax_Shader;
	
	Lighting lighting;

	//constains all the models and to access it use modelnames enum
	Models models;
public:
	Renderer();
	void cameraCalculation(Camera& camera, Controls controls);
	void lightingCalculation(Camera camera, Controls controls, float deltaTime);

	void render_diffuse_Emissive_NLShader(Entity& entity);
	void render_diffuse_Emissive_NLShader(std::vector<Entity> entities);
	void render_diffuse_Emissive_NLShaderInstanced(std::vector<Entity> entities);
	
	void render_diffuse_NLShader(Entity& entity);
	void render_diffuse_NLShader(std::vector<Entity> entities);
	void render_diffuse_NLShaderInstanced(std::vector<Entity> entities);

	void render_diffuse_Specular_Emissive_Shader(Entity& entity, float shininess);
	void render_diffuse_Specular_Emissive_Shader(std::vector<Entity> entities, float shininess);
	void render_diffuse_Specular_Emissive_ShaderInstanced(std::vector<Entity> entities, float shininess);

	void render_diffuse_Specular_Shader(Entity& entity, float shininess);
	void render_diffuse_Specular_Shader(std::vector<Entity> entities, float shininess);
	void render_diffuse_Specular_ShaderInstanced(std::vector<Entity> entities, float shininess);

	void render_diffuse_Specular_Reflective_ShaderInstanced(std::vector<Entity> entities, float shininess, ReflectionProb reflectionProb);

	void render_grass_ShaderInstanced(std::vector<Entity> entities);
	void render_grass_NLShaderInstanced(std::vector<Entity> entities);

	void render_diffuse_Specular_Normal_Shader(Entity& entity, float shininess);
	void render_diffuse_Specular_Normal_Parallax_Shader(Entity& entity, float shininess, float heightScale);
private:
};