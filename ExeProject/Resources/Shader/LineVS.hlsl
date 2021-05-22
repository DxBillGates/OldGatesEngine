#include "DefaultShader.hlsli"

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	return mul(projMatrix, mul(viewMatrix, mul(modelMatrix, pos)));
}