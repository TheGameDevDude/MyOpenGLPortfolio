#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window {
public:
	int WIDTH;
	int HEIGHT;
	std::string title;
	GLFWwindow* window;
private:
public:
	Window(int WIDTH, int HEIGHT, const char* title);
private:
};
