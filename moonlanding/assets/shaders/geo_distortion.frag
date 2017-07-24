/*
 * Simple Blur Shader
 * (C)opyright Hartmut Schirmacher, http://schirmacher.beuth-hochschule.de
 *
 */

#version 150

// texture to be blurred
uniform sampler2D post_tex;
uniform int image_width;
uniform int image_height;
uniform int kernel_width;
uniform int kernel_height;

uniform sampler2D normal_tex;
uniform bool useNormal_text;

// use jittering?
uniform bool use_jitter;
uniform float time;

// texture coords
in vec2 texcoord_frag;

in vec4 sceneSpace;

in vec3 normal;

// output: color
out vec4 outColor;


void main(void)
{
    vec2 image_size = vec2(image_width, image_height);

    vec2 perspective = (sceneSpace.xy/sceneSpace.w) * 0.5 + 0.5;

    vec2 refractCoord = vec2(perspective.x, perspective.y);

    // distortion factor (bias)
    refractCoord.x += 0.04;

    // not working properly
    if (useNormal_text) {
        vec3 distortion = texture(normal_tex, texcoord_frag).rgb;
        vec2 offset = distortion.xy * refractCoord.xy;
        vec3 color = texture(post_tex, offset).rgb;
        outColor = vec4(color, 1);
    } else {
        // this to use                 // geo tex distortion
        vec3 color = texture(post_tex, texcoord_frag*0.05 + refractCoord).rgb;
//    vec3 color = texture(post_tex, refractCoord + normal.xy * 0.3).rgb;
        outColor = vec4(color, 1);
    }
}
