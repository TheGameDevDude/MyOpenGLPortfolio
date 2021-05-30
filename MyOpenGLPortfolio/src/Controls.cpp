#include "Controls.h"

Controls::Controls(GLFWwindow* window) {
	this->window = window;
	forward = false;
	backward = false;
	left = false;
	right = false;
	up = false;
	down = false;
	mouseDX = 0.0f;
	mouseDY = 0.0f;
	mouseX = 0.0f;
	mouseY = 0.0f;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
}

// keyboard and mouse input 
void Controls::tick() {
	mouse();
	keyboard();
}

// figuring out dynamic position (current pos - mid point of the screen)
void Controls::mouse() {
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	glfwGetCursorPos(window, &mouseX, &mouseY);
	mouseDX = mouseX - windowWidth / 2;
	mouseDY = -(mouseY - windowHeight / 2);
	// reseting the cursor back to mid of the screen
	glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
}

void Controls::keyboard() {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		forward = true;
		backward = false;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		backward = true;
		forward = false;
	}
	else {
		forward = false;
		backward = false;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		left = true;
		right = false;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		right = true;
		left = false;
	}
	else {
		left = false;
		right = false;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		up = true;
		down = false;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		down = true;
		up = false;
	}
	else {
		down = false;
		up = false;
	}
}