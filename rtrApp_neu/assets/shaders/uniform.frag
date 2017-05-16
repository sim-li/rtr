#version 150

/*
 * Simple Phong Shader
 * (C)opyright Hartmut Schirmacher, http://schirmacher.beuth-hochschule.de
 *
 * This fragment shader calculates some direction vectors in eye space
 * and then uses a Phong illum model to calculate output color.
 *
 */



// output: color
out vec4 outColor;
uniform vec3 myUniformColor;

in vec4 position_EC;
in vec3 normal_EC;
in vec3 fragNormal;

// calculate Phong-style local illumination

void
main(void)
{

     //outColor.rgb = (normalize(fragNormal) + vec3(1))/2;
    //outColor = vec4(myUniformColor, 1);
     outColor = vec4(normalize(fragNormal),1);

}
