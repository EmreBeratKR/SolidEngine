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


vec4 debug_normal(vec3 normal)
{
    vec4 debugNormal = vec4(normal, 1.0f);

    if (debugNormal.x < 0)
    {
        debugNormal.x *= -0.01f;
    }

    if (debugNormal.y < 0)
    {
        debugNormal.y *= -0.01f;
    }

    if (debugNormal.z < 0)
    {
        debugNormal.z *= -0.01f;
    }

    return debugNormal;
}

void main()
{
	outColor = texture(texSampler, inUv) * vec4(inColor, 1.0f);
    //outColor = debug_normal(inNormal);
}