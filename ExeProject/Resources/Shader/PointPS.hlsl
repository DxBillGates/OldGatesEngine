#include "PointShader.hlsli"

float4 main(PSInput input) : SV_TARGET
{
	float frc = frac(sin(dot(float2(input.pos.x, input.pos.y), float2(12.9898, 78.233))) * 43758.5453);
	return float4(normalize(input.pos.xyz), 1.0f);
}