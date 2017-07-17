/* Copyright 2013 Henrik Tramberend. All Rights Reserved. Absolutely No Warranty. */

#version 150 core

struct Transform {
    mat4 projection;
    mat4 inverseView;
    mat4 view;
    mat4 model;
};

struct PointLight {
    vec3 position;
    vec3 intensity;
    vec3 attenuation;
};

in vec2 uv;
in vec3 position;
in vec3 normal;
in vec3 tangent;
in vec3 bitangent;

uniform sampler2D terrainNZ;
uniform PointLight pointlight;
uniform Transform transform;
uniform float textureRepeat;

out vec3 eyeDirT;
out vec3 lightDirT;
out vec2 uvI;
out float height;
out float distance;

const float bias = 0.7;
const float scale = 2.0;

void main(void) {

    vec2 uvR = uv * vec2(textureRepeat);
    height = texture(terrainNZ, uvR).w;
    vec3 displaced = position + normal * (bias + height) * scale / textureRepeat;

    vec4 positionW = transform.model * vec4(displaced, 1.0);

    vec3 tangentW = (transform.model * vec4(tangent, 0.0)).xyz;
    vec3 binormalW = (transform.model * vec4(bitangent, 0.0)).xyz;
    vec3 normalW = (transform.model * vec4(normal, 0.0)).xyz;

    vec3 lightDirW = pointlight.position - positionW.xyz;
    vec3 eyePositionW = (transform.view * vec4(0, 0, 0, 1)).xyz;
    vec3 eyeDirW = eyePositionW - positionW.xyz;

    mat3 TBN = mat3(tangentW, binormalW, normalW);

    lightDirT = lightDirW * TBN;
    eyeDirT = eyeDirW * TBN;

    uvI = uv;
    vec4 positionV = transform.projection * transform.inverseView * positionW;
    distance = positionV.w;
    gl_Position = positionV;
}
