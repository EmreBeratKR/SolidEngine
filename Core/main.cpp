#include "engine_window.h"
#include "render_pipeline.h"


int main() 
{
    Engine::Rendering::RenderPipeline renderPipeline("Core/Shaders/shader.vert.spv", "Core/Shaders/shader.frag.spv");
    Engine::EngineWindow window(800, 600, "Game Engine");

    return 0;
}