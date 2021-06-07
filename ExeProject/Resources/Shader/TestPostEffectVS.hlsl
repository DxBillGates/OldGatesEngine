#include "DefaultShader.hlsli"
TestPEVSOutput main(float4 pos : POSITION, float2 uv : TEXCOORD,float3 normal : NORMAL)
{
	TestPEVSOutput o;
	o.pos = mul(projMatrix, mul(viewMatrix, mul(modelMatrix, pos)));
	o.uv = uv;
	return o;
}