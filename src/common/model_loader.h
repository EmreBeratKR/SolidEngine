#pragma once

#include <tiny_obj_loader.h>
#include "../core/rendering/model.h"


namespace Engine::IO
{
	Rendering::Model* loadObj(const char* path);
}