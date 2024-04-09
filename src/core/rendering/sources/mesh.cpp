#include "mesh.h"
#include "vertex.h"
#include "vulkan_buffer.h"


namespace Engine::Rendering
{
    Mesh::Mesh()
    {
        vertexBuffer = new VertexBuffer();
        indexBuffer = new IndexBuffer(); 
    }

    Mesh::~Mesh()
    {
        delete vertexBuffer;
        delete indexBuffer;
    }
}