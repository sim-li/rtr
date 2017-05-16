#version 150

/*
 * Simple Phong Shader
 * (C)opyright Hartmut Schirmacher, http://schirmacher.beuth-hochschule.de
 *
 * This vertex shader expects a position and normal vector per vertex,
 * and model-view, projection and normal matrices.
 *
 * It transforms the position and normal to eye coordinates and
 * passes them to the fragment shader; it also transforms the vertex 
 * position to clip coordinates for the needs of the pipeline.
 *
 */





// transformation matrices as provided by Cinder
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewProjectionMatrix;

//uniform float Scale = 1,0f;

// in: position and normal vector in model coordinates (_MC)
in vec3 position_MC;
in vec3 normal_MC;

// position + normal vector in eye coordinates (_EC)
out vec4 position_EC;
out vec3 normal_EC;
out vec3 fragNormal;

const float pi2 = asin(1.0);
float wave(float x, float t, float A, float f, float c, float p0)
{
return A * sin(pi2 * f * (t - x/c ) + p0);
}

void main(void) {
/*
    // position to eye coordinates
    position_EC = modelViewMatrix * vec4(position_MC,1);
    // normal to eye coordinates
    normal_EC = normalMatrix * normal_MC;
    // position to clip coordinates
    gl_Position = projectionMatrix * position_EC;
*/

 /*
    vec4 pos = vec4(position_MC,1) * vec4(1,1,0.2,1);
    gl_Position = modelViewProjectionMatrix * pos ;//vec4(position_MC,1);
    fragNormal = normal_MC;
*/

    vec3 direction = vec3 (0, 1.0, 0.0);
    float projected = dot(direction, position_MC);
    vec3 dispdir = position_MC - direction * projected;
    float disp = wave(projected, 0.9, 0.2, 4.0, 0.05, 0.0);
    vec3 rippled = position_MC + dispdir * disp;

    gl_Position = modelViewProjectionMatrix * vec4(rippled,1.0) ;//vec4(position_MC,1);
    fragNormal = normal_MC;





}
