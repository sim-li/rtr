/* Copyright 2013 Henrik Tramberend. All Rights Reserved. Absolutely No Warranty. */

#version 150 core

struct Transform {
    mat4 projection;
    mat4 inverseView;
    mat4 view;
    mat4 model;
};

in vec3 position;
in vec3 normal;

out vec3 eyeDirV;
out vec3 lightDirV;
out vec3 normalV;

uniform Transform transform;

void main(void) {
    mat4 modelView = transform.inverseView * transform.model;

    vec4 positionV = modelView * vec4(position, 1.0);
    vec4 lightPosV = transform.inverseView * vec4(-10.0, 10.0, 10.0, 1.0);

    eyeDirV = -positionV.xyz;
    lightDirV = lightPosV.xyz - positionV.xyz;
    normalV = (modelView * vec4(normal, 0.0)).xyz;

    gl_Position = transform.projection * positionV;
}
