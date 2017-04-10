#version 150

/*
 * Simple Phong Shader
 * (C)opyright Hartmut Schirmacher, http://schirmacher.beuth-hochschule.de
 *
 * This fragment shader calculates some direction vectors in eye space
 * and then uses a Phong illum model to calculate output color.
 *
 */


// Phong coefficients and exponent
struct PhongMaterial {
    vec3 k_ambient;
    vec3 k_diffuse;
    vec3 k_specular;
    float shininess;
};

// point light
struct PointLight {
    vec3 intensity;
    vec4 position_EC;
};

uniform PhongMaterial material;
uniform PointLight light;

// ambient light
uniform vec3 ambientLightIntensity;

// matrices provided by the camera
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

// vertex position from vertex shader, in eye coordinates
in vec4 position_EC;

// normal vector from vertex shader, in eye coordinates
in vec3 normal_EC;

// output: color
out vec4 outColor;


// calculate Phong-style local illumination
vec3 phongIllum(vec3 normalDir, vec3 viewDir, vec3 lightDir)
{
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
    return ambient + diffuse + specular;

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
    
    // calculate color using phong illumination
    vec3 color = phongIllum(normal, viewDir, lightDir);

    // out to frame buffer
    outColor = vec4(color, 1);

}
