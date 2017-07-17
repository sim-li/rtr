#version 150 core

struct Transform {
    mat4 projection;
    mat4 inverseView;
    mat4 view;
    mat4 model;
};

in vec3 position;

uniform Transform transform;

out vec3 directionW;
//out vec4 vPosition;

void main(void) {
    // Transform to world space
    // Only consider the direction to the vertex
    directionW = vec3(transform.view * vec4(position, 0.0));
    // The cube already *is* in camera coordinates

//    vPosition = transform.projection * transform.inverseView * vec4(position, 1.0);
    gl_Position = transform.projection * vec4(position, 1.0);
//    vPosition = gl_Position;
}
