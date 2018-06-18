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
};

texture _MainTex;
sampler _MainTexSampler = sampler_state
{
  Texture = _MainTex;
  MipFilter = LINEAR;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
};

float4x4 _WorldViewProj;
float _Time;
float _MasteredTime;
float _NeedMasteredTime;
int _HitEffectCount = 0;
float4 _PlayerColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  o.uv = v.uv;
  return o;
}

float hex(float2 p, float2 h)
{
  float2 q = abs(p);
  return max(q.x - h.y, max(q.x + q.y * 0.57735, q.y * 1.1547) - h.x);
}

float gra(float v, float r)
{
  return clamp((0.5 * r - abs(0.5 - fmod(v + 0.5, 1.0))) * 2.0 / r, 0.0, 1.0);
}

float4 hexGrid(in float2 uv)
{
  float radius = 0.1;
  float padding = 0.01;
  float grid_radius = radius + padding * 2.0 + 0.0733;
  float2 grid = float2(grid_radius * 1.73, grid_radius);

  float2 p1 = fmod(uv, grid) - grid * float2(0.5, 0.5);
  float2 p2 = fmod(uv + grid * 0.5, grid) - grid * float2(0.5, 0.5);
  float d1 = hex(p1, float2(radius, radius));
  float d2 = hex(p2, float2(radius, radius));
  float d = min(d1, d2);
  float4 main_color = _PlayerColor;
  float4 hex_color = main_color * 0.5;
  float4 grid_color = main_color * gra(uv.y + _MasteredTime * 0.01f, 0.75);
  float4 grid_light_color = float4(1.0, 1.0, 1.0, 1.0);

  grid_light_color = grid_light_color * gra(uv.y + _MasteredTime * 0.01f, 0.25);
  grid_light_color *= grid_light_color;
  grid_color += grid_light_color;

  grid_color.a = 0.75;
  hex_color.a = 0.75;

  float4 c = (d < 0.0 ? 1.0 : 0.0) * hex_color;
  c += grid_color * (d < 0.0 ? 0.0 : 1.0);
  c += grid_light_color * max(0.0, d * 4.0 + 0.1) * 5.0;
  c += grid_light_color * max(0.0, d * 4.0 + 0.5) * 1.0;
  c += max(0.0, _HitEffectCount / 10.0);
  return c;
}

float4 frag(v2f i) : SV_TARGET
{
  i.uv.x *= 2.0;
  i.uv.x += 1.0;
  //i.uv.x *= sin((i.uv.y) * 3.1415926535);
  //i.uv.x *= sin((i.uv.y) * 3.1415926535);
  return hexGrid(i.uv);
}

technique Default
{
  pass
  {
    AlphaBlendEnable = TRUE;
    BlendOp = ADD;
    SrcBlend = SRCALPHA;
    DestBlend = ONE;
    ZEnable = TRUE;
    ZWriteEnable = FALSE;
    CullMode = NONE;
    vertexshader = compile vs_3_0 vert();
    pixelshader = compile ps_3_0 frag();
  }
}
