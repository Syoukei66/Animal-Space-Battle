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
  float4 color : COLOR0;
};

texture _MainTex;
sampler _MainTexSampler = sampler_state
{
  Texture = _MainTex;
  MipFilter = LINEAR;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
};

float4 _CameraPosition = float4(0.0f, 0.0f, 0.0f, 1.0f);
float4 _CameraDirection = float4(0.0f, 0.0f, 1.0f, 1.0f);
float4 _LightDirection = float4(0.0f, 0.0f, 1.0f, 1.0f);
float4x4 _WorldViewProj;
float4 _Diffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);
float _Time;
float _GridRadius = 1.0f;

static const float GRID_COUNT = 100.0f;
static const float CIRCLE_COUNT = 150.0f;
static const float GRID_WIDTH = 0.00025f;
static const float PI2 = 2.0f * 3.14159265358979f;

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  o.uv = v.uv;
  o.normal = v.normal;
  o.color = _Diffuse;
  float r = length(o.vertex.xyz);
  float3 len = o.vertex - _CameraPosition;
  float dl = 1.0f - length(len) / r;
  o.color.gb *= 1.0f - max(0.0f, dl - 0.5f);
  return o;
}

float4 frag(v2f i) : SV_TARGET
{
  float grid_d = 1.0f / GRID_COUNT;
  float dx = fmod(i.uv.x, grid_d) - grid_d * 0.5f;
  float dy = fmod(i.uv.y, grid_d) - grid_d * 0.5f;
  float4 col = abs(dx) < GRID_WIDTH || abs(dy) < GRID_WIDTH ? i.color : 0.0f;
  float v = (sin(i.uv.y * PI2 * CIRCLE_COUNT + _Time * 0.02f) + 1.0f) * 0.5f;
  float v2 = (sin(i.uv.x * PI2 * CIRCLE_COUNT + _Time * 0.02f) + 1.0f) * 0.5f;
  v = v * v2 * step(0.5f, v) * step(0.5f, v2);
  col.rgb += v * 0.1f;
  col.a *= v * v * 0.5f;
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
    CullMode = NONE;
    vertexshader = compile vs_3_0 vert();
    pixelshader = compile ps_3_0 frag();
  }
}
