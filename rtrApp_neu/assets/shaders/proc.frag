#version 150

out vec4 outColor;
uniform vec3 myUniformColor;

in vec4 position_EC;
in vec3 normal_EC;
in vec3 fragNormal;

void main(void) {
     outColor = vec4(normalize(fragNormal),1);
}
