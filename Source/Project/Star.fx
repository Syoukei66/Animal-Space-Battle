#define _WORLD_VIEW_PROJ
#define _WORLD
#define _LIGHT_LAMBERT
#include "../Engine/Engine/DefaultProperty.hlsli"

struct appdata
{
  float4 vertex : POSITION;
  float2 uv : TEXCOORD0;
  float3 normal : NORMAL0;
};

struct v2f
{
  float2 uv : TEXCOORD0;
  float4 vertex : SV_POSITION;
  float4 color : COLOR0;
};

float _Time;
float4 _PlayerColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  o.uv = v.uv;

  float d = (sin(_Time / 60.0f * 3.141592f * 2) + 1.0f) * 0.5f;
  float4 col = 1.0f - (1.0f - _PlayerColor) * d * 0.2f;
  float L = dot(normalize(mul(v.normal, _World)), _LightDirection);
  o.color = col * max(0.0f, L);
  o.color.a = 1.0f;

  return o;
}

float4 frag(v2f i) : SV_TARGET
{
  return i.color;
}

technique Default
{
  pass
  {
    ZEnable = TRUE;
    MultiSampleAntialias = TRUE;
    AlphaBlendEnable = FALSE;
    ShadeMode = GOURAUD;
    CullMode = CCW;
    vertexshader = compile vs_2_0 vert();
    pixelshader = compile ps_2_0 frag();
  }
}
