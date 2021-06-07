cbuffer Model : register(b0)
{
	matrix modelMatrix;
}

cbuffer Material : register(b1)
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
}

cbuffer CameraInfo : register(b2)
{
	matrix viewMatrix;
	matrix projMatrix;
	float4 cameraPos;
}

cbuffer LightInfo : register(b3)
{
	float4 worldLightDir;
	float4 lightColor;
}

cbuffer BloomInfo : register(b4)
{
	float4 threshold;
};

float3 GetPosition(matrix mat)
{
	return float3(-mat[0][3], -mat[1][3], -mat[2][3]);
}

struct DefaultVSInput
{
	float4 pos : POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
};

struct DefaultVSOutput
{
	float4 svpos : SV_POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
};

struct LineVSOutput
{
	float4 svpos : SV_POSITION;
	float4 pos : POSITION;
	float4 color : COLOR;
};

struct TestPEVSOutput
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
};