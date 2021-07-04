struct UAVData
{
	float4 pos;
	float4 vel;
};

RWStructuredBuffer<UAVData> real : register(u0);

[numthreads(1, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
	float x = frac(sin(dot(float2(0.016f * DTid.x, 0), float2(12.9898, 78.233))) * 43758.5453);
	float y = frac(sin(dot(float2(0, 0.016f * DTid.x), float2(12.9898, 7.233))) * 43758.5453);
	//float z = frac(sin(dot(float2(0.016f * DTid.x, 0), float2(12.9898, 78.233))) * 43758.5453);

	real[DTid.x].vel.x = x;
	real[DTid.x].vel.y = y;
	real[DTid.x].vel.z = -1.16f;

	real[DTid.x].pos.x += real[DTid.x].vel.x;
	real[DTid.x].pos.y += real[DTid.x].vel.y;
	real[DTid.x].pos.z += real[DTid.x].vel.z;
}