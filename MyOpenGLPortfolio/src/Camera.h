#pragma once

#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Controls.h"

class Camera {
public:
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 left;
	glm::vec3 up;

	float pitch;
	float yaw;
	float roll;

	const float mouseSensitivity = 0.05f;
	const float mouseShakeSensitivity = 0.03f;
	const float speed = 2.0f;

	float fov;
	float near;
	float far;
	float aspectRatio;
public:
	Camera();
	Camera(glm::vec3 position, float pitch, float yaw, float roll);
	glm::mat4 getViewMatrix();
	glm::mat4 getPerspectiveProjectionMatrix();
	void tick(Controls controls, float deltaTime);
private:
	void move(Controls controls, float deltaTime);
};