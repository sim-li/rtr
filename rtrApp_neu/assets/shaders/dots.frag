#version 150

// Phong coefficients and exponent
struct ToonMaterial {
    vec3 k_ambient;
    vec3 k_diffuse;
    vec3 k_specular;
    float shininess;
};

uniform int bands;
uniform float specularBias;

// point light // ambient light
struct PointLight {
    vec3 intensity;
    vec4 position_EC;
};
uniform vec3 ambientLightIntensity;


uniform ToonMaterial material;
uniform PointLight light;

uniform vec2 u_resolution;

in vec2 texCoord_FRA;

//_____________________________
// matrices provided by the camera
uniform mat4 modelViewMatrix; // ciModelView
uniform mat4 projectionMatrix; // ciProjectionMatrix

// vertex position from vertex shader, in eye coordinates
in vec4 position_EC; //vertexposition
// normal vector from vertex shader, in eye coordinates
in vec3 normal_EC; // normalDirEC
// output: color
out vec4 outColor;


// calculate Phong-style local illumination
vec3 toonIllum(vec3 normalDir, vec3 viewDir, vec3 lightDir, int bands)
{
    bands -= 1;
    // ambient part
    vec3 ambient = material.k_ambient * ambientLightIntensity;

    // back face towards viewer?
    float ndotv = dot(normalDir,viewDir);

    // visual debugging, you can safely comment this out
    // if(ndotv<0)
    //     return vec3(0,1,0);

    // cos of angle between light and surface.
    float ndotl = max(dot(normalDir,-lightDir),0);

    // diffuse contribution
    vec3 diffuse = material.k_diffuse * light.intensity * ndotl;

    // reflected light direction = perfect reflection direction
    vec3 r = reflect(lightDir,normalDir);

    // angle between reflection dir and viewing dir
    float rdotv = max( dot(r,viewDir), 0.0);

    // specular contribution
    vec3 specular = material.k_specular * light.intensity *
                    pow(rdotv, material.shininess);

    // return sum of all contributions
    return ambient + floor(diffuse * bands) / bands + step(specularBias, specular);

}

float circle(in vec2 _st, in float _radius){
    vec2 l = _st-vec2(0.5);
    return 1.-smoothstep(_radius-(_radius*0.01),
                         _radius+(_radius*0.01),
                         dot(l,l)*4.0);
}

void
main(void)
{
    // normalize normal after projection
    vec3 normal = normalize(normal_EC);

    // calculate light direction (for point light)
    vec3 lightDir = normalize(position_EC - light.position_EC).xyz;

    // do we use a perspective or an orthogonal projection matrix?
    bool usePerspective = projectionMatrix[2][3] != 0.0;

    // for perspective mode, the viewing direction (in eye coords) points
    // from the vertex to the origin (0,0,0) --> use -ecPosition as direction.
    // for orthogonal mode, the viewing direction is simply (0,0,1)
    vec3 viewDir = usePerspective? normalize(-position_EC.xyz) : vec3(0,0,1);


    vec2 st = texCoord_FRA.xy / u_resolution;
    vec3 color = vec3(0.0);
    st *= 3.0;      // Scale up the space by 3
    st = fract(st); // Wrap arround 1.0
    // Now we have 3 spaces that goes from 0-1
    color = vec3(st,0.0);
    //color = vec3(circle(st,0.5));
    outColor = vec4(color,1.0);


    // calculate color using phong illumination
    //vec3 color = toonIllum(normal, viewDir, lightDir, bands);

    // out to frame buffer
    //outColor = vec4(color, 1);

}
