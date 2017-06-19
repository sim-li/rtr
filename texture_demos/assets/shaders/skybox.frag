#version 150
in vec3 directionW;
//in vec4 vPosition;

uniform samplerCube specularEnvMap;
uniform bool abc;

out vec4 color;

void main(void) {
    //color.rgb = texture(specularEnvMap, normalize(directionW)).rgb;
    color.rgb = vec3(0,0,0);
//    if(vPosition.y < 0.5 && vPosition.z > 0.0){
//        float yEnd = 0.0;
//        float yStart = 0.5;
//        float fogFactor = (yEnd - vPosition.y) / (yEnd - yStart);
//        color.rgb = fogFactor * color.rgb + (1 - fogFactor) * vec3(0.8,0.8,0.8);
//    }

    color.a = 1.0;
}
