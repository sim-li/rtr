/*
 * Simple Phong Shader
 * (C)opyright Hartmut Schirmacher, http://schirmacher.beuth-hochschule.de
 *
 * This fragment shader calculates some direction vectors in eye space
 * and then uses a Phong illum model to calculate output color.
 *
 */

#version 150

// Phong coefficients and exponent
uniform vec3  k_ambient;
uniform vec3  k_diffuse;
uniform vec3  k_specular;
uniform float shininess;
uniform int bands;
uniform float specularBias;

uniform float r;
uniform vec2 scale;
uniform vec2 offset;
uniform vec3 colorA;
uniform vec3 colorB;


// ambient light and point light
uniform vec3 ambientLightColor;
uniform vec3 lightColor;
uniform vec4 lightPositionEC; // in eye coordinates!

// Cinder-provided unoformas
uniform mat4 ciModelView;
uniform mat4 ciProjectionMatrix;

// vertex position from vertex shader, in eye coordinates
in vec4 vertexPositionEC;

// normal vector from vertex shader, in eye coordinates
in vec3 normalDirEC;

// output: color
out vec4 outColor;



//
 

//

// calculate Phong-style local illumination
vec3 phongIllum(vec3 normalDir, vec3 viewDir, vec3 lightDir, float bands)
{
    // No magic numbers: n bands should visually result in n bands:
    bands -= 1;
    
    // ambient part
    vec3 ambient = k_ambient * ambientLightColor;
    
    // back face towards viewer?
    float ndotv = dot(normalDir,viewDir);
    if(ndotv<0.0)
        return vec3(0);
    // Alternative for toon shader:
    // if (ndotv < toonEdgeWidth)
    //    return toonEdgeColor;
    // ... "toonEdgeWith" and "toonEdgeColor" should be uniforms. ...
    
    // cos of angle between light and surface.
    float ndotl = dot(normalDir,-lightDir);
    if(ndotl<0.0)
        return vec3(0); // shadow / facing away from the light source
    
    // diffuse contribution
    vec3 diffuse = k_diffuse * lightColor * ndotl;
    
    // reflected light direction = perfect reflection direction
    vec3 r = reflect(lightDir,normalDir);
    
    // angle between reflection dir and viewing dir
    float rdotv = max( dot(r,viewDir), 0.0);
    
    // specular contribution
    vec3 specular =  k_specular * lightColor * pow(rdotv, shininess);
    
    // return sum of all contributions
    
    // Toon Shading
    
    // Independent diffuse and specular banding. Illustration looks like spec is always white (or k_specular),
    // could achive the same result by ignoring light contribution in specular computation above:
    // vec3 specular =  k_specular * pow(rdotv, shininess);
    return ambient + floor(diffuse * bands) / bands + step(specularBias, specular);
    
}

void
main(void)
{
    
    
    
    // normalize normal after projection
    vec3 normalEC = normalize(normalDirEC);
    
    // calculate light direction (for point light)
    vec3 lightDirEC = normalize(vertexPositionEC - lightPositionEC).xyz;
    
    // do we use a perspective or an orthogonal projection matrix?
    bool usePerspective = ciProjectionMatrix[2][3] != 0.0;
    
    // for perspective mode, the viewing direction (in eye coords) points
    // from the vertex to the origin (0,0,0) --> use -ecPosition as direction.
    // for orthogonal mode, the viewing direction is simply (0,0,1)
    vec3 viewdirEC = usePerspective? normalize(-vertexPositionEC.xyz) : vec3(0,0,1);
    
    // calculate color using phong illumination
    vec3 color = phongIllum(normalEC, viewdirEC, lightDirEC, bands);
    
    // out to frame buffer
    outColor = vec4(color, 1);
    
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.x *= u_resolution.x/u_resolution.y;
    
    st += offset;
    st = mod(st / scale, 1.);
    st -= vec2(.5);
    
    vec3 color;
    sqrt(st.x*st.x + st.y*st.y) > r
    ? color = colorA
    : color = colorB;
    
    gl_FragColor = vec4(color, 1.0);
    //outColor = vec4((vertexPositionEC.xyz+vec3(1))/4,1);
    
}


