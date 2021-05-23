#include "DefaultShader.hlsli"

float4 main(LineVSOutput i) : SV_TARGET
{
	float r,b;
	r = (i.pos.x == 0) ? 0 : 1;
	b = (i.pos.z == 0) ? 0 : 1;
	return float4(r,r * b,b,1);
}