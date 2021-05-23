#include "DefaultShader.hlsli"

LineVSOutput main(float4 pos : POSITION)
{
	LineVSOutput o;
	o.svpos = mul(projMatrix, mul(viewMatrix, mul(modelMatrix, pos)));
	o.pos = pos;
	return o;
}