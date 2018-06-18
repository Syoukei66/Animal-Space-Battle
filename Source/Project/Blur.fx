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

float4 frag(v2f i) : SV_TARGET
{
  float4 col = tex2D(_MainTexSampler, i.uv);

  float2 uv = _UV1 - _UV0;

  float tx = uv.x / _Width * 1.0f;

  float4 px0 = tex2D(_MainTexSampler, float2(i.uv.x + tx * (-1), i.uv.y));
  float4 px1 = tex2D(_MainTexSampler, float2(i.uv.x + tx * (-2), i.uv.y));
  float4 px2 = tex2D(_MainTexSampler, float2(i.uv.x + tx * (-3), i.uv.y));
  float4 px3 = tex2D(_MainTexSampler, float2(i.uv.x + tx * (-4), i.uv.y));
  float4 px4 = tex2D(_MainTexSampler, float2(i.uv.x + tx * (-5), i.uv.y));

  float4 px5 = tex2D(_MainTexSampler, float2(i.uv.x + tx * (1), i.uv.y));
  float4 px6 = tex2D(_MainTexSampler, float2(i.uv.x + tx * (2), i.uv.y));
  float4 px7 = tex2D(_MainTexSampler, float2(i.uv.x + tx * (3), i.uv.y));
  float4 px8 = tex2D(_MainTexSampler, float2(i.uv.x + tx * (4), i.uv.y));
  float4 px9 = tex2D(_MainTexSampler, float2(i.uv.x + tx * (5), i.uv.y));

  float4 px = col * 0.20f;
  px0 *= 0.12f;
  px1 *= 0.10f;
  px2 *= 0.08f;
  px3 *= 0.06f;
  px4 *= 0.04f;

  px5 *= 0.12f;
  px6 *= 0.10f;
  px7 *= 0.08f;
  px8 *= 0.06f;
  px9 *= 0.04f;

  float4 psx = px + px0 + px1 + px2 + px3 + px4 + px5 + px6 + px7 + px8 + px9;

  float ty = uv.y / _Height;

  float4 py0 = tex2D(_MainTexSampler, float2(i.uv.x, i.uv.y + ty * (-1)));
  float4 py1 = tex2D(_MainTexSampler, float2(i.uv.x, i.uv.y + ty * (-2)));
  float4 py2 = tex2D(_MainTexSampler, float2(i.uv.x, i.uv.y + ty * (-3)));
  float4 py3 = tex2D(_MainTexSampler, float2(i.uv.x, i.uv.y + ty * (-4)));
  float4 py4 = tex2D(_MainTexSampler, float2(i.uv.x, i.uv.y + ty * (-5)));

  float4 py5 = tex2D(_MainTexSampler, float2(i.uv.x, i.uv.y + ty * (1)));
  float4 py6 = tex2D(_MainTexSampler, float2(i.uv.x, i.uv.y + ty * (2)));
  float4 py7 = tex2D(_MainTexSampler, float2(i.uv.x, i.uv.y + ty * (3)));
  float4 py8 = tex2D(_MainTexSampler, float2(i.uv.x, i.uv.y + ty * (4)));
  float4 py9 = tex2D(_MainTexSampler, float2(i.uv.x, i.uv.y + ty * (5)));

  float4 py = col * 0.20f;
  py0 *= 0.12f;
  py1 *= 0.10f;
  py2 *= 0.08f;
  py3 *= 0.06f;
  py4 *= 0.04f;

  py5 *= 0.12f;
  py6 *= 0.10f;
  py7 *= 0.08f;
  py8 *= 0.06f;
  py9 *= 0.04f;

  float4 psy = py + py0 + py1 + py2 + py3 + py4 + py5 + py6 + py7 + py8 + py9;

  return max(psx - 1.0f, 0.0f) + max(psy - 1.0f, 0.0f);
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
