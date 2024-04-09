#pragma once

#include <tiny_obj_loader.h>


#include "fwd.h"


namespace Engine::IO
{
	Rendering::Model* loadObj(const char* path);
}