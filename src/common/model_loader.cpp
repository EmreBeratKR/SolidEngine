#define TINYOBJLOADER_IMPLEMENTATION


#include <unordered_map>


#include "model_loader.h"


namespace Engine::IO
{
    Rendering::Model* loadObj(const char* path)
	{
        //TODO check if path ends with .obj

        Rendering::Model* model = new Rendering::Model();
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path)) 
        {
            throw std::runtime_error(warn + err);
        }

        for (const auto& shape : shapes) 
        {
            Rendering::Mesh mesh{};
            std::unordered_map<Rendering::Vertex, uint32_t> uniqueVertices{};

            for (const auto& index : shape.mesh.indices) 
            {
                Rendering::Vertex vertex{};

                auto vx = attrib.vertices[3 * index.vertex_index + 0];
                auto vy = attrib.vertices[3 * index.vertex_index + 1];
                auto vz = attrib.vertices[3 * index.vertex_index + 2];

                vertex.position = {vx, vy, vz};

                auto tx = attrib.texcoords[2 * index.texcoord_index + 0];
                auto ty = 1.0f - attrib.texcoords[2 * index.texcoord_index + 1];

                vertex.texCoord = {tx, ty};

                vertex.color = { 1.0f, 1.0f, 1.0f };

                if (uniqueVertices.count(vertex) == 0) 
                {
                    uniqueVertices[vertex] = static_cast<uint32_t>(mesh.vertices.size());
                    mesh.vertices.push_back(vertex);
                }

                mesh.indices.push_back(uniqueVertices[vertex]);
            }

            model->meshes.push_back(mesh);

            return model;
        }
	}
}