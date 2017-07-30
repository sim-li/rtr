/*hilit shader */

#version 150

// texture to be blurred
uniform sampler2D post_tex;
uniform int image_width;
uniform int image_height;
uniform int kernel_width;
uniform int kernel_height;

// use jittering?
uniform bool use_jitter;

// texture coords
in vec2 texcoord_frag;

// output: color
out vec4 outColor;

void main(void)
{

    vec2 coord = texcoord_frag;
    vec3 color = texture(post_tex, coord).rgb;

    // ?
    //color *= 1.0/float(kernel_size.x*kernel_size.y);

    // luminous factor
    //float brightness = color.r * 0.2126 + color.g * 0.7152 + color.b * 0.0722

    // with gradiant
    // outColor = vec4(color * brightness, 1);


    bool brightness = color.r > 0.7 || color.g > 0.7 || color.b > 0.7;
    if (brightness)
        outColor = vec4(color, 1);
    else
        outColor = vec4(0);
}
