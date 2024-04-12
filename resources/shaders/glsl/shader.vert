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


const vec3 LIGHT_DIRECTION = normalize(vec3(15.0f, 1.0f, -3.0f));


mat4 transform_to_model(mat4 transform)
{
    mat4 model = transform;

    model[3][0] = 0.0f;
    model[3][1] = 0.0f;
    model[3][2] = 0.0f;

    return model;
}

void main()
{
    vec4 position = vec4(inPosition, 1.0);
    mat4 model = transform_to_model(push.transform);
    vec3 normal = normalize((model * vec4(inNormal, 1.0f)).xyz);
    float lightIntensity = max(dot(normal, LIGHT_DIRECTION), 0.02f);
    
	gl_Position = ubo.proj * ubo.view * push.transform * position;
    outNormal = normal;
	outColor = inColor * lightIntensity;
    outUv = inUv;
}