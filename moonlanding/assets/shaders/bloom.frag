#version 150

uniform sampler2D highlight_tex;
uniform sampler2D scene_tex;

in vec2 texcoord_frag;

out vec4 outColor;

void main(void) {
    vec3 highlight = texture(highlight_tex, texcoord_frag).rgb;
    vec3 sceneColor = texture(scene_tex, texcoord_frag).rgb;
    outColor = vec4(highlight + sceneColor, 1);
}
