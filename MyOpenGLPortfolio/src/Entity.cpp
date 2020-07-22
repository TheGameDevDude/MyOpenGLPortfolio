#include "Entity.h"

Entity::Entity() {

}

Entity::Entity(int modelName, glm::vec3 position, glm::vec3 scale, glm::vec3 orientation) {
	this->modelName = modelName;
	this->position = position;
	this->scale = scale;
	this->orientation = orientation;
	forward = glm::vec3(0.0f, 0.0f, 1.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	orderOfRotation(1, 2, 3);
}

void Entity::orderOfRotation(int x, int y, int z) {
	if (x == 1 && y == 2 && z == 3) {
		forward = glm::vec3(0.0f, 0.0f, 1.0f);
		right = glm::vec3(1.0f, 0.0f, 0.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);

		float pitchX = right.x * sin(glm::radians(orientation.x) / 2);
		float pitchY = right.y * sin(glm::radians(orientation.x) / 2);
		float pitchZ = right.z * sin(glm::radians(orientation.x) / 2);
		float pitchW = cos(glm::radians(orientation.x) / 2);
		glm::quat pitchQuaternion = glm::quat(pitchW, pitchX, pitchY, pitchZ);

		forward = pitchQuaternion * forward;
		up = pitchQuaternion * up;

		float yawX = up.x * sin(glm::radians(orientation.y) / 2);
		float yawY = up.y * sin(glm::radians(orientation.y) / 2);
		float yawZ = up.z * sin(glm::radians(orientation.y) / 2);
		float yawW = cos(glm::radians(orientation.y) / 2);
		glm::quat yawQuaternion = glm::quat(yawW, yawX, yawY, yawZ);

		forward = yawQuaternion * forward;
		right = yawQuaternion * right;

		float rollX = forward.x * sin(glm::radians(orientation.z) / 2);
		float rollY = forward.y * sin(glm::radians(orientation.z) / 2);
		float rollZ = forward.z * sin(glm::radians(orientation.z) / 2);
		float rollW = cos(glm::radians(orientation.z) / 2);
		glm::quat rollQuaternion = glm::quat(rollW, rollX, rollY, rollZ);

		right = rollQuaternion * right;
		up = rollQuaternion * up;

		modelMatrix = glm::translate(glm::mat4(1.0f), position) * glm::mat4(rollQuaternion) * glm::mat4(yawQuaternion) * glm::mat4(pitchQuaternion) * glm::scale(glm::mat4(1.0f), scale);
	}
	else if (x == 1 && z == 2 && y == 3) {
		forward = glm::vec3(0.0f, 0.0f, 1.0f);
		right = glm::vec3(1.0f, 0.0f, 0.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);

		float pitchX = right.x * sin(glm::radians(orientation.x) / 2);
		float pitchY = right.y * sin(glm::radians(orientation.x) / 2);
		float pitchZ = right.z * sin(glm::radians(orientation.x) / 2);
		float pitchW = cos(glm::radians(orientation.x) / 2);
		glm::quat pitchQuaternion = glm::quat(pitchW, pitchX, pitchY, pitchZ);

		forward = pitchQuaternion * forward;
		up = pitchQuaternion * up;

		float rollX = forward.x * sin(glm::radians(orientation.z) / 2);
		float rollY = forward.y * sin(glm::radians(orientation.z) / 2);
		float rollZ = forward.z * sin(glm::radians(orientation.z) / 2);
		float rollW = cos(glm::radians(orientation.z) / 2);
		glm::quat rollQuaternion = glm::quat(rollW, rollX, rollY, rollZ);

		right = rollQuaternion * right;
		up = rollQuaternion * up;

		float yawX = up.x * sin(glm::radians(orientation.y) / 2);
		float yawY = up.y * sin(glm::radians(orientation.y) / 2);
		float yawZ = up.z * sin(glm::radians(orientation.y) / 2);
		float yawW = cos(glm::radians(orientation.y) / 2);
		glm::quat yawQuaternion = glm::quat(yawW, yawX, yawY, yawZ);

		forward = yawQuaternion * forward;
		right = yawQuaternion * right;

		modelMatrix = glm::translate(glm::mat4(1.0f), position) * glm::mat4(yawQuaternion) * glm::mat4(rollQuaternion) * glm::mat4(pitchQuaternion) * glm::scale(glm::mat4(1.0f), scale);
	}
	else if (y == 1 && x == 2 && z == 3) {
		forward = glm::vec3(0.0f, 0.0f, 1.0f);
		right = glm::vec3(1.0f, 0.0f, 0.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);

		float yawX = up.x * sin(glm::radians(orientation.y) / 2);
		float yawY = up.y * sin(glm::radians(orientation.y) / 2);
		float yawZ = up.z * sin(glm::radians(orientation.y) / 2);
		float yawW = cos(glm::radians(orientation.y) / 2);
		glm::quat yawQuaternion = glm::quat(yawW, yawX, yawY, yawZ);

		forward = yawQuaternion * forward;
		right = yawQuaternion * right;

		float pitchX = right.x * sin(glm::radians(orientation.x) / 2);
		float pitchY = right.y * sin(glm::radians(orientation.x) / 2);
		float pitchZ = right.z * sin(glm::radians(orientation.x) / 2);
		float pitchW = cos(glm::radians(orientation.x) / 2);
		glm::quat pitchQuaternion = glm::quat(pitchW, pitchX, pitchY, pitchZ);

		forward = pitchQuaternion * forward;
		up = pitchQuaternion * up;

		float rollX = forward.x * sin(glm::radians(orientation.z) / 2);
		float rollY = forward.y * sin(glm::radians(orientation.z) / 2);
		float rollZ = forward.z * sin(glm::radians(orientation.z) / 2);
		float rollW = cos(glm::radians(orientation.z) / 2);
		glm::quat rollQuaternion = glm::quat(rollW, rollX, rollY, rollZ);

		right = rollQuaternion * right;
		up = rollQuaternion * up;

		modelMatrix = glm::translate(glm::mat4(1.0f), position) * glm::mat4(rollQuaternion) * glm::mat4(pitchQuaternion) * glm::mat4(yawQuaternion) * glm::scale(glm::mat4(1.0f), scale);
	}
	else if (y == 1 && z == 2 && x == 3) {
			forward = glm::vec3(0.0f, 0.0f, 1.0f);
		right = glm::vec3(1.0f, 0.0f, 0.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);

		float yawX = up.x * sin(glm::radians(orientation.y) / 2);
		float yawY = up.y * sin(glm::radians(orientation.y) / 2);
		float yawZ = up.z * sin(glm::radians(orientation.y) / 2);
		float yawW = cos(glm::radians(orientation.y) / 2);
		glm::quat yawQuaternion = glm::quat(yawW, yawX, yawY, yawZ);

		forward = yawQuaternion * forward;
		right = yawQuaternion * right;

		float pitchX = right.x * sin(glm::radians(orientation.x) / 2);
		float pitchY = right.y * sin(glm::radians(orientation.x) / 2);
		float pitchZ = right.z * sin(glm::radians(orientation.x) / 2);
		float pitchW = cos(glm::radians(orientation.x) / 2);
		glm::quat pitchQuaternion = glm::quat(pitchW, pitchX, pitchY, pitchZ);

		forward = pitchQuaternion * forward;
		up = pitchQuaternion * up;

		float rollX = forward.x * sin(glm::radians(orientation.z) / 2);
		float rollY = forward.y * sin(glm::radians(orientation.z) / 2);
		float rollZ = forward.z * sin(glm::radians(orientation.z) / 2);
		float rollW = cos(glm::radians(orientation.z) / 2);
		glm::quat rollQuaternion = glm::quat(rollW, rollX, rollY, rollZ);

		right = rollQuaternion * right;
		up = rollQuaternion * up;

		modelMatrix = glm::translate(glm::mat4(1.0f), position) * glm::mat4(rollQuaternion) * glm::mat4(pitchQuaternion) * glm::mat4(yawQuaternion) * glm::scale(glm::mat4(1.0f), scale);
	}
	else if (z == 1 && x == 2 && y == 3) {
		forward = glm::vec3(0.0f, 0.0f, 1.0f);
		right = glm::vec3(1.0f, 0.0f, 0.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);

		float rollX = forward.x * sin(glm::radians(orientation.z) / 2);
		float rollY = forward.y * sin(glm::radians(orientation.z) / 2);
		float rollZ = forward.z * sin(glm::radians(orientation.z) / 2);
		float rollW = cos(glm::radians(orientation.z) / 2);
		glm::quat rollQuaternion = glm::quat(rollW, rollX, rollY, rollZ);

		right = rollQuaternion * right;
		up = rollQuaternion * up;

		float pitchX = right.x * sin(glm::radians(orientation.x) / 2);
		float pitchY = right.y * sin(glm::radians(orientation.x) / 2);
		float pitchZ = right.z * sin(glm::radians(orientation.x) / 2);
		float pitchW = cos(glm::radians(orientation.x) / 2);
		glm::quat pitchQuaternion = glm::quat(pitchW, pitchX, pitchY, pitchZ);

		forward = pitchQuaternion * forward;
		up = pitchQuaternion * up;

		float yawX = up.x * sin(glm::radians(orientation.y) / 2);
		float yawY = up.y * sin(glm::radians(orientation.y) / 2);
		float yawZ = up.z * sin(glm::radians(orientation.y) / 2);
		float yawW = cos(glm::radians(orientation.y) / 2);
		glm::quat yawQuaternion = glm::quat(yawW, yawX, yawY, yawZ);

		forward = yawQuaternion * forward;
		right = yawQuaternion * right;

		modelMatrix = glm::translate(glm::mat4(1.0f), position) * glm::mat4(yawQuaternion) * glm::mat4(pitchQuaternion) * glm::mat4(rollQuaternion) * glm::scale(glm::mat4(1.0f), scale);
	}
	else if (z == 1 && y == 2 && x == 3) {
		forward = glm::vec3(0.0f, 0.0f, 1.0f);
		right = glm::vec3(1.0f, 0.0f, 0.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);

		float rollX = forward.x * sin(glm::radians(orientation.z) / 2);
		float rollY = forward.y * sin(glm::radians(orientation.z) / 2);
		float rollZ = forward.z * sin(glm::radians(orientation.z) / 2);
		float rollW = cos(glm::radians(orientation.z) / 2);
		glm::quat rollQuaternion = glm::quat(rollW, rollX, rollY, rollZ);

		right = rollQuaternion * right;
		up = rollQuaternion * up;

		float yawX = up.x * sin(glm::radians(orientation.y) / 2);
		float yawY = up.y * sin(glm::radians(orientation.y) / 2);
		float yawZ = up.z * sin(glm::radians(orientation.y) / 2);
		float yawW = cos(glm::radians(orientation.y) / 2);
		glm::quat yawQuaternion = glm::quat(yawW, yawX, yawY, yawZ);

		forward = yawQuaternion * forward;
		right = yawQuaternion * right;

		float pitchX = right.x * sin(glm::radians(orientation.x) / 2);
		float pitchY = right.y * sin(glm::radians(orientation.x) / 2);
		float pitchZ = right.z * sin(glm::radians(orientation.x) / 2);
		float pitchW = cos(glm::radians(orientation.x) / 2);
		glm::quat pitchQuaternion = glm::quat(pitchW, pitchX, pitchY, pitchZ);

		forward = pitchQuaternion * forward;
		up = pitchQuaternion * up;

		modelMatrix = glm::translate(glm::mat4(1.0f), position) * glm::mat4(pitchQuaternion) * glm::mat4(yawQuaternion) * glm::mat4(rollQuaternion) * glm::scale(glm::mat4(1.0f), scale);
	}
}

glm::mat4 Entity::getModelMatrix() {
	return modelMatrix;
}