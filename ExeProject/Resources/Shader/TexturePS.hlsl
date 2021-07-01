#include "DefaultSpriteShader.hlsli"

Texture2D<float4> tex : register(t0);
Texture2D<float> depthTex : register(t1);
SamplerState smp : register(s0);

float4 main(DefaultSpriteVSOutput input) : SV_TARGET
{
	float4 texColor = tex.Sample(smp,input.uv);
	//float dep = pow(depthTex.Sample(smp,vsOutput.uv),20);
	//dep = 1 - dep;
	return float4(texColor.rgb,1);
	//return float4(dep,dep,dep,1);
}