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
  float3 normal : NORMAL0;
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
float4 _Diffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);
float _Time;

static const float GRID_COUNT = 50.0f;
static const float GRID_WIDTH = 0.0005f;
static const float PI2 = 2.0f * 3.14159265358979f;

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  o.uv = v.uv;
  o.normal = v.normal;
  return o;
}

float4 frag(v2f i) : SV_TARGET
{
  float d = i.uv.y;
  float4 col = float4(0.05f, 0.1f, 0.2f, 1.0f);
  col.a = 1.0f;
  col.r = pow(d, 6);
  col.gr += pow(d, 9);
  col.gb += pow(d, 10);
  col.r += pow(d, 2) * 0.1f;
  col.rg += d * 0.05;
  col *= d;
  col.a = 1.0f;
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
    ZEnable = FALSE;
    ZWriteEnable = FALSE;
    vertexshader = compile vs_3_0 vert();
    pixelshader = compile ps_3_0 frag();
  }
}
