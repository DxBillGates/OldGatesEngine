#include "DefaultShader.hlsli"

float4 main(DefaultVSOutput vsOutput) : SV_TARGET
{
	float3 lightDir = normalize(worldLightDir.xyz);
	float3 normal = normalize(vsOutput.normal);
	float intensity = saturate(dot(-lightDir, normal));
	float4 result = float4(intensity, intensity, intensity, 1) * lightColor;
	return result;
}