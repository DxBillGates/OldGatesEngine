cbuffer Model : register(b0)
{
	matrix modelMatrix;
}

cbuffer CameraInfo : register(b2)
{
	matrix viewMatrix;
	matrix projMatrix;
	float4 cameraPos;
}

StructuredBuffer<float4> posData : register(t0);