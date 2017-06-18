/* Copyright 2013 Henrik Tramberend. All Rights Reserved. Absolutely No Warranty. */

#version 150 core

in vec3 eyeDirV;
in vec3 lightDirV;
in vec3 normalV;

uniform vec3 kd;

out vec4 color;

const vec3 ks = vec3(0.33);

void main(void) {
    vec3 N = normalize(normalV);
    vec3 E = normalize(eyeDirV);
    vec3 L = normalize(lightDirV);

    vec3 intensity = kd * max(0.0, dot(N, L));
    intensity += ks * pow(max(0.0, dot(reflect(-E, N), L)), 10.0);

    color.rgb = intensity;
    color.a = 1.0;
}
