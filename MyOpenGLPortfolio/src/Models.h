#pragma once

#include "Model.h"

#include <vector>

struct Models{
	std::vector<Model> models = { 
		Model("res/models/nanosuit/nanosuit.obj"),
		Model("res/models/grass/grass.obj"),
		Model("res/models/crate/crate.obj"),
		Model("res/models/brick/brick.obj"),
		Model("res/models/coolerbrick/coolerbrick.obj"),
		Model("res/models/magicwood/magicwood.obj")
	};
};