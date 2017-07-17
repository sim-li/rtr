#version 150

//zhis isdone

// transformation matrices as provided by Cinder
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

// in: position and normal vector in model coordinates (_MC)
in vec3 position_MC;
in vec3 normal_MC;
in vec2 texcoord;

// position + normal vector in eye coordinates (_EC)
out vec4 position_EC;
out vec3 normal_EC;
out vec2 texcoord_out;

out vec3 fragNormal;


//wave function
const float pi2 = asin(1.0);

float wave(float x, float t, float A, float f, float c, float p0)
{
return A * sin(pi2 * f * (t - x/c ) + p0);
}

void main(void) {

    vec3 direction = vec(0, 1.0, 0.0);
    float projected = dot(direction, position_EC.xyz);
    vec3 dispdir = position_EC.xyz - direction * projected;
    float disp = wave(projected, time, 0.2, 4.0, 0.05, 0.0);
    vec3 rippled = position_EC.xyz + dispdir + disp;

    gl_Position = modelViewMatrix * vec4(rippled);
    fragNormal = normal_EC;
/*

    // position to eye coordinates
    position_EC = modelViewMatrix * vec4(position_MC,1);

    // normal to eye coordinates
    normal_EC = normalMatrix * normal_MC;

    // position to clip coordinates
    gl_Position = projectionMatrix * position_EC;
*/
    texcoord_out = texcoord;

}
