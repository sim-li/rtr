/*
 * fragment shader for phong + textures + bumps
 *
 */
#version 150

// output - transformed to eye coordinates (EC)
in vec4 position_EC;
in vec3 normal_EC;

// output - transformed to tangent space (TS)
in vec3 viewDir_TS;
in vec3 lightDir_TS;

// tex coords - just copied
in vec2 texcoord_frag;
in float disp_frag;

in float surfaceAngle;
in float distance;
// output: color
out vec4 outColor;

// point light
struct PointLight {
    vec3 intensity;
    vec4 position_EC;
};
uniform PointLight light;

// Phong coefficients and exponent
struct PhongMaterial {
    // basic Phong
    vec3 k_ambient;
    vec3 k_diffuse;
    vec3 k_specular;
    float shininess;
    bool debug_texcoords;
};
uniform PhongMaterial phong;

struct PlanetMaterial {
    // additional textures
    bool useDayTexture;
    bool useNightTexture;
    bool useGlossTexture;
    bool useCloudsTexture;
    sampler2D dayTexture;
    sampler2D snowTexture;
    sampler2D rockTexture;
    sampler2D nightTexture;
    sampler2D glossTexture;
    sampler2D cloudsTexture;
    float night_scale;
    float night_blend_exp;
    // debugging
    bool debug;
    bool debugWaterLand;
    // animation
    bool animateClouds;
};

uniform PlanetMaterial planet;

struct BumpMaterial {
    bool use;
    bool debug;
    float scale;
    sampler2D tex;
};
uniform BumpMaterial bump;

struct DisplacementMaterial {
    bool use;
    float scale;
    sampler2D tex;
};
uniform DisplacementMaterial displacement;

// more uniforms
uniform mat4  projectionMatrix;
uniform float time;
uniform vec3  ambientLightIntensity;

/*
 *  Calculate surface color based on Phong illumination model.
 */
vec3 gammaCorrection(vec3 col) {
    return pow(col, vec3(0.6))*2.0;
}

float terrain_min = 0.01;
float terrain_max = 0.015;

float rock_min = 0.0220;
float rock_max = 0.035;

float snow_min = 0.05;
float snow_max = 0.08;



vec3 textureColByHeight(vec2 uv) {

    if(disp_frag > 0.05){
        vec3 textureCol = texture(planet.dayTexture, uv).rgb;
        return gammaCorrection(textureCol);
    } else if (disp_frag > 0.035) {
        return  texture(planet.snowTexture, uv).rgb;
    } else if (disp_frag > 0.01) {
        return texture(planet.snowTexture, uv).rgb;
    } else {
        vec3 textureCol = texture(planet.dayTexture, uv).rgb;
        return gammaCorrection(textureCol);
    }




}

vec3 planetshader(vec3 n, vec3 v, vec3 l, vec2 uv, int nom) {
    // texture lookups
    vec3  dayCol = textureColByHeight(uv);
    vec3  nightCol = texture(planet.nightTexture, uv).rgb;
    bool  atSea = texture(planet.glossTexture, uv).r > 0.008;
    float cloudDensity = texture(planet.cloudsTexture, uv).r;

    nightCol = pow(nightCol, vec3(0.5)) * planet.night_scale;
    cloudDensity = pow(cloudDensity, 0.8);

    // cosine of angle between light and surface normal.
    float ndotl = dot(n,l);

    // visualizing texture coords + day/night border
    float debugFactor = 1.0;
    const float dawnThreshold = cos(radians(89.0));
    if(planet.debug) {
        if(mod(uv.x, 0.05) >= 0.025) {
            debugFactor = 0.7; // darker bands in u direction
        }
        if(abs(ndotl)<dawnThreshold) {
            return vec3(0.2,0.6,0.2); // green day/night line
        }
    }

    // ambient part
    vec3 ambient = (planet.useNightTexture? nightCol : phong.k_ambient) *
                   ambientLightIntensity * debugFactor;

    // just show water vs. land
    if(planet.debugWaterLand) {
        ambient = atSea? vec3(0.5,0,0) : vec3(0,0.5,0);
    }

    // clouds at night?
    if(planet.useCloudsTexture) {
        ambient = (1.0-cloudDensity)*ambient + cloudDensity * vec3(0.1,0.1,0.1);
    }

    // surface back-facing to light?
    if(ndotl<=0.0)
        return ambient;
    else
        ndotl = max(ndotl, 0.0);

    // diffuse contribution
    vec3 diffuseCoeff = planet.useDayTexture? dayCol : phong.k_diffuse;
    if(planet.debugWaterLand) {
        diffuseCoeff = atSea? vec3(0.8,0,0) : vec3(0,0.8,0);
    }

    // clouds at day?
    if(planet.useCloudsTexture || nom == 1) {
        diffuseCoeff = (1.0-cloudDensity)*diffuseCoeff
                       + cloudDensity*vec3(1.5,1.5,1.5);
    }
    // final diffuse term for daytime
    vec3 diffuse =  diffuseCoeff * light.intensity * ndotl * debugFactor;

    // ambient part contains lights; modify depending on time of day
    ambient *= pow(1.0-ndotl,planet.night_blend_exp);

     // reflected light direction = perfect reflection direction
    vec3 r = reflect(-l,n);

    // cosine of angle between reflection dir and viewing dir
    float rdotv = max( dot(r,v), 0.0);

    // specular contribution + gloss map
    bool loShine = planet.useGlossTexture && !atSea;
    vec3 specularCoeff = phong.k_specular;
    float exponent = phong.shininess;
    if(loShine) {
        specularCoeff /= 6;
        exponent = 15;
    }
    vec3 specular = specularCoeff * light.intensity * pow(rdotv, exponent);

    // return sum of all contributions




    return ambient + diffuse + specular;

}


vec3 decodeNormal(vec3 normal) {
    return normalize(normal * vec3(2, 2, 1) - vec3(1, 1, 0));
}

void main() {
    // default normal in tangent space is (0,0,1).
    vec3 bumpValue = texture(bump.tex, texcoord_frag).xyz;

    // get bump direction (in tangent space) from bump texture
    vec3 N = bump.use? decodeNormal(bumpValue) : vec3(0,0,1);
    vec3 V = normalize(viewDir_TS);
    vec3 L = normalize(lightDir_TS);

    // calculate color using phong illumination
    vec3 color = planetshader(N, V, L, texcoord_frag, 1);
    // set fragment color
    if(phong.debug_texcoords)
       outColor = vec4(texcoord_frag, 0, 1);
    else if(bump.debug)
        outColor = vec4((N+vec3(1,1,1)/2), 1);
    else
        outColor = vec4(color, 1.0);



    vec3 bla;
    bla = vec3(0,1,0);

    float shininess = 10.0f;
    vec3 intensity = 0.2 * bla;
    intensity += bla * 0.7 * max(0, dot(N, L));
    intensity += vec3(0.15) * pow(max(0, dot(reflect(-V, N), L)), shininess);


    vec2 u_FogDist = vec2(15.0, 35.0);
    vec4 v_Color;
    v_Color.rgb = intensity;
    v_Color.a = 1.0;
    vec4 u_FogColor;
    u_FogColor.rgb = vec3(0.8, 0.8, 0.8);
    u_FogColor.a = 1.0;

    u_FogColor.a = exp(distance)/100;


    float fogFactor = (u_FogDist.y - distance) / (u_FogDist.y - u_FogDist.x);
    outColor = mix(u_FogColor, v_Color, clamp(fogFactor, 0.0, 1.0));






}
