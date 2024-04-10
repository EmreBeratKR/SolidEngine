#version 450

layout(binding = 0) uniform UniformBufferObject 
{
    mat4 view;
    mat4 proj;
} ubo;

layout(push_constant) uniform Push
{
    mat4 transform;
} push;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;
layout(location = 3) in vec2 inUv;

layout(location = 0) out vec3 outNormal;
layout(location = 1) out vec3 outColor;
layout(location = 2) out vec2 outUv;


const vec3 LIGHT_DIRECTION = normalize(vec3(0.0f, -1.0f, 0.0f));


void main()
{
    vec4 position = vec4(inPosition, 1.0);
    vec3 normal = normalize((push.transform * vec4(inNormal, 1.0f)).xyz);
    float lightIntensity = max(dot(normal, LIGHT_DIRECTION), 0.02f);
    
	gl_Position = ubo.proj * ubo.view * push.transform * position;
    outNormal = inNormal;
	outColor = inColor * lightIntensity;
    outUv = inUv;
}