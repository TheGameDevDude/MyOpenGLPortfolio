#pragma once

#include <glad/glad.h>
#include<iostream>
#include<vector>

class TextureLoader {
public:
	static unsigned int loadTexture(const char* file_path);
	static unsigned int textureFromFile(const char* path, const std::string& directory);
	static unsigned int loadCubemap(std::vector<std::string> faces);
};

