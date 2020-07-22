#pragma once

#include "ModelNames.h"
#include "Entity.h"
#include<glm/glm.hpp>
#include<vector>

class GameObjects {
public:
	std::vector<Entity> nanoSuits;
	std::vector<Entity> grass;
	Entity crate;
	Entity brick;
	Entity coolerbrick;
	Entity magicwood;
private:
public:
	GameObjects();
	void tick(float deltaTime);
private:
};