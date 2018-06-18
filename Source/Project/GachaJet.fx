#define _WORLD_VIEW_PROJ
#define _WORLD
#define _LIGHT_LAMBERT
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

texture _NoiseTexture;
sampler _Noise = sampler_state
{
  Texture = _NoiseTexture;
  MipFilter = LINEAR;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
};

texture _UvNoiseTexture;
sampler _UvNoise = sampler_state
{
  Texture = _UvNoiseTexture;
  MipFilter = LINEAR;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
};

float _Time;

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  o.uv = v.uv;
  return o;
}

static const float PI = 3.1415926535;

static const float4 _C0 = float4(1.0, 0.0, 0.0, 1.0);
static const float4 _C1 = float4(0.0, 0.22, 1.0, 1.0);
static const float4 _C2 = float4(1.0, 1.0, 1.0, 1.0);
static const float _P = 0.92;

float4 frag(v2f i) : SV_TARGET
{
  float sint = (sin(_Time * 10.0) + 1.0) * 0.5;
  float sinx = tex2D(_UvNoise, float2(i.uv.x, _Time * 10.0)).r;
  i.uv.y += sinx * 0.1 - 0.05;
  const float p = _P;
  float t0 = sin(smoothstep(0.0, p, i.uv.y) * PI * 0.5);
  float t1 = sin(smoothstep(p, 1.0, i.uv.y) * PI * 0.5);
  float4 col = (_C0 * (1.0 - t0) + _C1 * t0) * (1.0 - t1) + _C2 * t1;

  col.r += 1.0 - i.uv.y;
  col.g += abs(i.uv.y - 0.5);
  //col.rgb = clamp(col.rgb, 0.0f, 1.0f);
  col.a *= (smoothstep(0.0, 0.9, i.uv.y * i.uv.y));
  return col;
}

technique Default
{
  pass
  {
    AlphaBlendEnable = TRUE;
    BlendOp = ADD;
    SrcBlend = SRCALPHA;
    DestBlend = ONE;
    ShadeMode = GOURAUD;
    CullMode = NONE;
    ZEnable = FALSE;
    ZWriteEnable = FALSE;
    vertexshader = compile vs_3_0 vert();
    pixelshader = compile ps_3_0 frag();
  }
}
