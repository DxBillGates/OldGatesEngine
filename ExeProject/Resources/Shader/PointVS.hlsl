#include "PointShader.hlsli"

float4 main(float4 pos : POSITION, uint index : SV_InstanceID) : SV_POSITION
{
	float4 svpos;
	svpos = mul(projMatrix, mul(viewMatrix, mul(modelMatrix, pos + posData[index])));
	return svpos;
}