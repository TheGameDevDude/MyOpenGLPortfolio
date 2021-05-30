#pragma once

#include <GLFW/glfw3.h>

class Controls {
public:
	bool forward;
	bool backward;
	bool right;
	bool left;
	bool up;
	bool down;

	// mouse dynamic position 
	double mouseDX;
	double mouseDY;

	// mouse position 
	double mouseX;
	double mouseY;

	int windowWidth;
	int windowHeight;

	GLFWwindow* window;
public:
	Controls(GLFWwindow* window);
	void tick();
private:
	void mouse();
	void keyboard();
};