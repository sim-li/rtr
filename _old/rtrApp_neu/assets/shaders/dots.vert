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
out vec2 texCoord_FRA;

void main(void) {
    // position to eye coordinates
    position_EC = modelViewMatrix * vec4(position_MC,1);

    // normal to eye coordinates
    normal_EC = normalMatrix * normal_MC;

    // position to clip coordinates
    gl_Position = projectionMatrix * position_EC;

    texCoord_FRA = texcoord;
}
