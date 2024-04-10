#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(push_constant) uniform Push
{
    mat4 transform;
} push;

layout(location = 0) in vec3 inNormal;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inUv;

layout(location = 0) out vec4 outColor;


void main()
{
	outColor = texture(texSampler, inUv) * vec4(inColor, 1.0f);
    //outColor = vec4(inNormal, 1.0f);
}