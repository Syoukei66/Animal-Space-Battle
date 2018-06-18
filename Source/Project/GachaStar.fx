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
float4 _Color;
float4 _SubColor;

/*
  UnityとのUV座標の違いの解消法
  uvのy座標をマイナスに、
  y座標に対する演算の符号を反転
  α値が1.0以上の場合にも対応
*/
v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  o.uv = v.uv;
  o.uv.y *= -1.0;
  return o;
}

float4 frag(v2f i) : SV_TARGET
{
  i.uv.x += step(0.5, i.uv.x) * -(i.uv.x - 0.5) * 2.0;
  float2 uv = i.uv;
  float4 m = tex2D(_UvNoise, uv * 0.05);
  uv.x += m.b;
  uv.y += m.r + _Time * 9.0;
  float v = (sin(_Time * 100.0) + 1.0) * 0.5;
  float4 col = tex2D(_Noise, uv);
  col += _Color * (1.0f - v) + _SubColor * v;
  col *= 1.0 - smoothstep(0.0, 0.7, -i.uv.y);
  col.rgb *= col.a;
  return col;
}

technique Default
{
  pass
  {
    AlphaBlendEnable = TRUE;
    BlendOp = ADD;
    SrcBlend = SRCALPHA;
    DestBlend = INVSRCALPHA;
    ShadeMode = GOURAUD;
    CullMode = NONE;
    ZWriteEnable = FALSE;
    vertexshader = compile vs_3_0 vert();
    pixelshader = compile ps_3_0 frag();
  }
}
