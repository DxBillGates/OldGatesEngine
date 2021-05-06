#include "SimpleShader.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
	float4 texColor = tex.Sample(smp,input.uv);

	float3 light = normalize(float3(1, -1, 1));
	float diffuse = saturate(dot(-light, input.normal));
	float brightness = diffuse + 0.1f;
	float4 shadeColor = float4(brightness, brightness, brightness, 1);
	return shadeColor/* * texColor*/;

	//float3 lightdir = float3(0, 0, 1);
	//lightdir = normalize(lightdir);
	//float3 lightcolor = float3(1, 1, 1);
	//float3 diffuse = float3(0.5f, 0.5f, 0.5f);
	//return float4(dot(-lightdir, input.normal) * diffuse.xyz * lightcolor + 0.3f, 1.0f) * color * texColor;
}