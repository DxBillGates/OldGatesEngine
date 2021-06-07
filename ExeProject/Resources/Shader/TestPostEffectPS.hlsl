#include "DefaultShader.hlsli"

Texture2D<float4> tex : register(t0);
Texture2D<float> depthTex : register(t1);
SamplerState smp : register(s0);

float4 main(TestPEVSOutput i) : SV_TARGET
{
	float2 pixel = float2(1/1920.0f,1/1080.0f);
	float4 addNearPixelColor = float4(0,0,0,0);


	//¶ã‚©‚çƒTƒ“ƒvƒŠƒ“ƒO
	float sampleCount = threshold;
	float2 offset = i.uv + float2(-pixel.x, -pixel.y) * sampleCount;
	float count = 0;
	for (int j = 0; j < sampleCount*2; ++j)
	{
		for (int k = 0; k < sampleCount * 2; ++k)
		{
			addNearPixelColor += tex.Sample(smp, offset + float2(pixel.x * j,pixel.y * k));
			++count;
		}
	}
	float4 r = addNearPixelColor / count;

	float4 texColor = tex.Sample(smp,i.uv);
	return saturate(r);
}