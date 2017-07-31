#version 150

uniform sampler2D post_tex;
uniform int image_width;
uniform int image_height;
uniform int kernel_width;
uniform int kernel_height;

uniform bool use_jitter;

in vec2 texcoord_frag;

out vec4 outColor;

void main(void) {
    vec2 coord = texcoord_frag;
    vec3 color = texture(post_tex, coord).rgb;
    bool brightness = color.r > 0.7 || color.g > 0.7 || color.b > 0.7;
    outColor = brightness ? vec4(color, 1) :  vec4(0);
}
