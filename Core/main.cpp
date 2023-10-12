#include "engine_window.h"
#include "Rendering/render_pipeline.h"
#include "Rendering/vulkan_graphic_api.h";


int main() 
{
    Engine::Rendering::VulkanGraphicApi graphicApi{};
    Engine::Rendering::RenderPipeline renderPipeline{"Core/Shaders/shader.vert.spv", "Core/Shaders/shader.frag.spv"};
    Engine::EngineWindow window{800, 600, "Game Engine"};

    return 0;
}