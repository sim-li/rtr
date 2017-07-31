#version 150


// matrices provided by the camera
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

uniform samplerCube cubeMap;
uniform mat4 viewMatrix;

// vertex position and normal from vertex shader, in eye coordinates
in vec4 position_EC;
in vec3 normal_EC;
in vec2 texcoord_frag;

// output: color
out vec4 outColor;


void main(void)
{
    bool usePerspective = projectionMatrix[2][3] != 0.0;
    vec3 toVertEC = usePerspective ? normalize(position_EC.xyz) : vec3(0, 0, -1);
    vec3 toVertWC = (inverse(viewMatrix) * vec4(toVertEC, 0)).xyz;
    vec3 sky = texture(cubeMap, toVertWC).rgb;
    outColor = vec4(sky, 0);
}
