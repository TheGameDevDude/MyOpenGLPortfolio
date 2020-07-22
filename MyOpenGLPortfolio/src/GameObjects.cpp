#include "GameObjects.h"

GameObjects::GameObjects() {
	nanoSuits.push_back(Entity(nanosuitModel, glm::vec3(8, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(45.0f, 46.0f, 32.0f)));
	nanoSuits.push_back(Entity(nanosuitModel, glm::vec3(-8, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(45.0f, 46.0f, 32.0f)));
	nanoSuits.push_back(Entity(nanosuitModel, glm::vec3(0, 0, 8), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(45.0f, 46.0f, 32.0f)));
	nanoSuits.push_back(Entity(nanosuitModel, glm::vec3(0, 0, -8), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(45.0f, 46.0f, 32.0f)));
	grass.push_back(Entity(grassModel, glm::vec3(2, 4, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3()));
	crate = Entity(crateModel, glm::vec3(2, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3());
	brick = Entity(brickModel, glm::vec3(-3, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3());
	coolerbrick = Entity(coolerbrickModel, glm::vec3(-3, 0, 3), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3());
	magicwood = Entity(magicwoodModel, glm::vec3(-3, 2.5f, 3), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3());
}

void GameObjects::tick(float deltatime) {
	for (unsigned int i = 0; i < nanoSuits.size(); i++) {
		nanoSuits[i].orientation.y += 20.0f * deltatime;
		nanoSuits[i].orderOfRotation(1, 3, 2);
	}

	magicwood.orientation.y += 20.0f * deltatime;
	magicwood.orderOfRotation(1, 2, 3);
}