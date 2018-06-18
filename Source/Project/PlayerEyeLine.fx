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
float4 _PlayerColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  o.uv = v.uv;
  return o;
}

const float WAVE_COUNT = 5;
const float PI = 3.14159265358979f;

float4 frag(v2f i) : SV_TARGET
{
//  float4 col = float4(1.0f, 1.0f, 1.0f, 1.0f);
//  float d = i.uv.y;
//  i.uv.y = fmod((i.uv.y + _Time * 0.025f / WAVE_COUNT) * WAVE_COUNT, 1.0f);
//  col.a = pow(d, 2);
//  col.rgb = 1.0f - (1.0f - i.uv.y) * (1.0f - _PlayerColor.rgb);
//  return col;
  return _PlayerColor * 2.0f;
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
    //CullMode = NONE;
    vertexshader = compile vs_2_0 vert();
    pixelshader = compile ps_2_0 frag();
  }
}
