#define _WORLD_VIEW_PROJ
#define _WORLD
#define _CAMERA
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
  float3 normal : NORMAL0;
};

float _Time;
float4 _PlayerColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  o.uv = v.uv;
  o.color = float4(1.0f, 0.0f, 0.0f, 1.0f);
  o.normal = normalize(mul(v.normal, _World));
  return o;
}

float4 frag(v2f i) : SV_TARGET
{
  float L = dot(i.normal, -_CameraDirection);
  float4 color = i.color * max(0.0f, 1.0f - L) * 1.5f;
  return color;
}

technique Default
{
  pass
  {
    ZEnable = FALSE;
    MultiSampleAntialias = TRUE;
    AlphaBlendEnable = TRUE;
    BlendOp = ADD;
    SrcBlend = SRCALPHA;
    DestBlend = ONE;
    ShadeMode = GOURAUD;
    vertexshader = compile vs_3_0 vert();
    pixelshader = compile ps_3_0 frag();
  }
}
