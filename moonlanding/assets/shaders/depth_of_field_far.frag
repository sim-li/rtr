in  vec4 gs_TexCoord[8];
out vec4 gs_FragColor;

uniform sampler2D ScreenTexture;
uniform sampler2D ScreenTextureLowRes;
uniform sampler2D CameraDepthTexture;
uniform float Texelsize;
uniform vec4 DepthOfFieldParameter;

// DepthOfFieldParameter.x := NearBlurDepth
// DepthOfFieldParameter.y := FocalPlaneDepth
// DepthOfFieldParameter.z := FarBlurDepth

void main()
{
  float CameraDepth = texture(CameraDepthTexture, gs_TexCoord[0].st).w;

  if(CameraDepth == -1.0) // Hintergrund
  gs_FragColor = texture(ScreenTexture,gs_TexCoord[0].st);
  else
  {
    vec4 BlurredColor = 0.25*(
      texture(ScreenTextureLowRes, gs_TexCoord[0].st+vec2(Texelsize, Texelsize))+
      texture(ScreenTextureLowRes, gs_TexCoord[0].st-vec2(Texelsize, Texelsize))+
      texture(ScreenTextureLowRes, gs_TexCoord[0].st+vec2(Texelsize, -Texelsize))+
      texture(ScreenTextureLowRes, gs_TexCoord[0].st+vec2(-Texelsize, Texelsize)));

    if(CameraDepth < DepthOfFieldParameter.x ||
    CameraDepth > DepthOfFieldParameter.z)
    gs_FragColor = BlurredColor;
    else
    {
      if(CameraDepth > DepthOfFieldParameter.y)
      {
        float factor = (DepthOfFieldParameter.z-CameraDepth)/
          (DepthOfFieldParameter.z-DepthOfFieldParameter.y);
        gs_FragColor = factor*texture(ScreenTexture, gs_TexCoord[0].st) +
          (1.0-factor)*BlurredColor;
      }
      else
      {
        float factor = (CameraDepth-DepthOfFieldParameter.x)/
          (DepthOfFieldParameter.y-DepthOfFieldParameter.x);
        gs_FragColor = factor*texture(ScreenTexture, gs_TexCoord[0].st) +
          (1.0-factor)*BlurredColor;
}}}}
