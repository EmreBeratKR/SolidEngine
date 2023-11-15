#pragma once

#include <tiny_obj_loader.h>
#include "src/core/rendering/model.h"


namespace Engine::IO
{
	void loadObj(const char* path, Rendering::Model* model);
}