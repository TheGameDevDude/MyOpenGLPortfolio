#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstddef>

#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"
#include "Entity.h"

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	unsigned int vao;
private:
	unsigned int vbo, ebo;
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void draw(Shader shader);
	void draw(Shader shader, std::vector<Entity> entities);
	void drawInstanced(Shader shader, std::vector<Entity> entities);
private:
	void setupMesh();
};