#define _WORLD_VIEW_PROJ
#define _MAIN_TEXTURE_POINT
#define _DIFFUSE
#include "../Engine/Engine/DefaultProperty.hlsli"

struct appdata
{
  float4 vertex : POSITION;
  float2 uv : TEXCOORD0;
};

struct v2f
{
  float2 uv : TEXCOORD0;
  float4 vertex : SV_POSITION;
};

float2 _UV0 = float2(0.0f, 0.0f);
float2 _UV1 = float2(1.0f, 1.0f);
float _Width = 1.0f;
float _Height = 1.0f;

texture _NoiseTexture;
sampler _Noise = sampler_state
{
  Texture = _NoiseTexture;
  MipFilter = LINEAR;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
};

float PI = 3.14159265358979f;
float _Time;

v2f vert(appdata v)
{
  v2f o;
  v.vertex.x *= _Width;
  v.vertex.y *= _Height;
  o.vertex = mul(v.vertex, _WorldViewProj);

  v.uv *= _UV1 - _UV0;
  v.uv += _UV0;
  o.uv = v.uv;
  return o;
}

float4 frag(v2f i)
{
  psout o;
  o.out0 = 0.0f;
  o.out1 = tex2D(_MainTexSampler, i.uv) - 1.0f;
  return o;
}

technique Default
{
  pass LowPassFilter
  {
    ShadeMode = FLAT;
    ZEnable = FALSE;

    vertexshader = compile vs_3_0 vert();
    pixelshader = compile ps_3_0 frag();
  }
}
