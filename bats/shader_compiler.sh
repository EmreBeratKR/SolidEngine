#!/bin/bash
$VULKAN_SDK/bin/glslc resources/shaders/glsl/shader.vert -o resources/shaders/spv/shader.vert.spv
$VULKAN_SDK/bin/glslc resources/shaders/glsl/shader.frag -o resources/shaders/spv/shader.frag.spv