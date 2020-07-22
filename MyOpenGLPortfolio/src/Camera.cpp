#include "Camera.h"

Camera::Camera() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	left = glm::vec3(-1.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	pitch = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;
	fov = 60.0f;
	near = 0.01f;
	far = 1000.0f;
	aspectRatio = 1.0f;
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, float roll) {
	this->position = position;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	left = glm::vec3(-1.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;
	fov = 60.0f;
	near = 0.01f;
	far = 1000.0f;
	aspectRatio = 1.0f;
}

glm::mat4 Camera::getViewMatrix() {
	glm::quat pitchQuaternion = glm::quat(glm::vec3(glm::radians(pitch), 0, 0));
	glm::quat yawQuaternion = glm::quat(glm::vec3(0, glm::radians(yaw), 0));

	float rollX = forward.x * sin(glm::radians(roll) / 2);
	float rollY = forward.y * sin(glm::radians(roll) / 2);
	float rollZ = forward.z * sin(glm::radians(roll) / 2);
	float rollW = cos(glm::radians(roll) / 2);
	glm::quat rollQuaternion = glm::quat(rollW, rollX, rollY, rollZ);

	forward = glm::vec3(0.0f, 0.0f, -1.0f) * pitchQuaternion * yawQuaternion;
	left = glm::vec3(-1.0f, 0.0f, 0.0f) * pitchQuaternion * yawQuaternion * rollQuaternion;
	up = glm::vec3(0.0f, 1.0f, 0.0f) * pitchQuaternion * yawQuaternion * rollQuaternion;

	forward = glm::normalize(forward);
	left = glm::normalize(left);
	up = glm::normalize(up);

	return  glm::mat4(pitchQuaternion) * glm::mat4(yawQuaternion) * glm::mat4(rollQuaternion) * glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, -position.z));
}

glm::mat4 Camera::getPerspectiveProjectionMatrix(){
	glm::mat4 projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
	return projection;
}

void Camera::tick(Controls controls, float deltaTime) {
	int width = 0, height = 0;
	glfwGetWindowSize(controls.window, &width, &height);
	aspectRatio = (float)width / (float)height;
	move(controls, deltaTime);
}

void Camera::move(Controls controls, float deltaTime) {
	controls.tick();

	pitch -= (float)controls.mouseDY * mouseSensitivity;
	yaw += (float)controls.mouseDX * mouseSensitivity;
	roll = (float)controls.mouseDX * mouseShakeSensitivity;

	pitch = glm::clamp(pitch, -90.0f, 90.0f);

	if (controls.forward) {
		position += forward * speed * deltaTime;
	}
	else if(controls.backward){
		position -= forward * speed * deltaTime;
	}

	if (controls.left) {
		position += left * speed * deltaTime;
	}
	else if (controls.right) {
		position -= left * speed * deltaTime;
	}

	if (controls.up) {
		position.y += speed * deltaTime;
	}
	else if (controls.down) {
		position.y -= speed * deltaTime;
	}
}