#include "model.h"


namespace Engine::Rendering
{
    Model::Model()
    {

    }

    Model::~Model()
    {
        for (const auto& mesh : meshes)
        {
            delete mesh;
        }
    }
}