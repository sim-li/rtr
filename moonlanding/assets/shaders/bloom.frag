/* bloom shader */

#version 150

// texture to be blurred
uniform sampler2D highlight_tex;
uniform sampler2D scene_tex;

// use jittering?

// texture coords
in vec2 texcoord_frag;

// output: color
out vec4 outColor;

void main(void)
{
    vec3 hilit = texture(highlight_tex, texcoord_frag).rgb;
    vec3 sceneColor = texture(scene_tex, texcoord_frag).rgb;

    outColor = vec4(hilit + sceneColor, 1);
    

}
