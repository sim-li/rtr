/* Copyright 2013 Henrik Tramberend. All Rights Reserved. Absolutely No Warranty. */

#version 150 core

in vec3 eyeDirT;
in vec3 lightDirT;
in vec2 uvI;
in float height;
in float distance;

uniform sampler2D terrainNZ;
uniform sampler2D terrainRocks;
uniform sampler2D terrainWater;
uniform sampler2D terrainGrass;
uniform sampler2D terrainSand;

uniform float textureRepeat;
uniform float time;

out vec4 color;

const vec2 waterFlowVelocity = vec2(.03, .03);
const float WATER_LINE_MAX = 0.01;
const float SAND_LINE_MIN = 0.01;
const float SAND_LINE_MAX = 0.15;
const float GRASS_LINE_MIN = 0.22;
const float GRASS_LINE_MAX = 0.35;
const float ROCK_LINE_MIN = 0.50;
const float ROCK_LINE_MAX = 0.80;
const float SNOW_LINE_MIN = 0.87;

// Decode a color from a normal map.
vec3 decodeN(vec4 nz) {
    return normalize(nz.rgb * vec3(2, -2, 0.5) - vec3(1, -1, 0));
}

void main(void) {
    vec2 uv = uvI * vec2(textureRepeat);
    vec3 kDiffuse;

    vec3 N = normalize(decodeN(texture(terrainNZ, uv)));
    vec3 E = normalize(eyeDirT);
    vec3 L = normalize(lightDirT);

    float shininess = 10.0;

    float height2 = height;

    // source used for transitioning textures:
    // http://www.mbsoftworks.sk/index.php?page=tutorials&series=1&tutorial=24

    if(height2 < WATER_LINE_MAX) {
        // scale texture by factor 10 and "animate" water by offsetting the uv position
        kDiffuse = texture(terrainWater, uv * 10 - waterFlowVelocity * time).xyz;
//        N = vec3(0, 0, 1);
        shininess = 5.0;
    } else if (height2 < SAND_LINE_MAX) {
        kDiffuse = texture(terrainSand, uv * 20).xyz;
    // Blend between sand and grass texture
    } else if (height2 <= GRASS_LINE_MIN) {

        height2 -= SAND_LINE_MAX;
        height2 /= (GRASS_LINE_MIN - SAND_LINE_MAX);

        kDiffuse = texture(terrainSand, uv * 20).xyz * (1.0 - height2);
        kDiffuse += texture(terrainGrass, uv * 20).xyz * height2;
    } else if(height2 <= GRASS_LINE_MAX) {
        kDiffuse = texture(terrainGrass, uv * 20).xyz;

    // Blend between grass and rock texture
    } else if(height2 <= ROCK_LINE_MIN) {
        height2 -= GRASS_LINE_MAX;
        height2 /= (ROCK_LINE_MIN - GRASS_LINE_MAX);

        kDiffuse = texture(terrainGrass, uv * 20).xyz * (1.0 - height2);
        kDiffuse += texture(terrainRocks, uv * 20).xyz * height2;
    } else if(height2 <= ROCK_LINE_MAX) {
        kDiffuse = texture(terrainRocks, uv * 20).xyz;

    // Blend between rock and snow texture
    } else if(height2 <= SNOW_LINE_MIN) {
        height2 -= ROCK_LINE_MAX;
        height2 /= (SNOW_LINE_MIN - ROCK_LINE_MAX);

        kDiffuse = texture(terrainRocks, uv * 20).xyz * (1.0 - height2);
        kDiffuse += vec3(1).xyz * height2;
    // SNOW_LINE
    } else {
        kDiffuse = vec3(1);
    }

    vec3 intensity = 0.2 * kDiffuse;
    intensity += kDiffuse * 0.7 * max(0, dot(N, L));
    intensity += vec3(0.15) * pow(max(0, dot(reflect(-E, N), L)), shininess);

    // fog
    //sources used:
    // http://www.geeks3d.com/20100228/fog-in-glsl-webgl/
    // http://stackoverflow.com/questions/25274783/opengl-3-3-glsl-fragment-shader-fog-effect-not-working
    vec2 u_FogDist = vec2(15.0, 35.0);
    vec4 v_Color;
    v_Color.rgb = intensity;
    v_Color.a = 1.0;
    vec4 u_FogColor;
    u_FogColor.rgb = vec3(0.8, 0.8, 0.8);
    u_FogColor.a = 1.0;

    u_FogColor.a = exp(distance)/100;

//    if(distance > 50) {
//        u_FogColor.a = 1.0 - mix(0, 0.6, distance/100);
//    }

    float fogFactor = (u_FogDist.y - distance) / (u_FogDist.y - u_FogDist.x);
    color = mix(u_FogColor, v_Color, clamp(fogFactor, 0.0, 1.0));


//    color.rgb = intensity;
//    color.a = 1.0;
}
