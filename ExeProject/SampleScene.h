#pragma once
#include "Header/Scene/Scene.h"
#include "Header/Graphics/RootSignature.h"
#include "Header/Math/Math.h"
#include "Header/Graphics/GPUParticle/GPUParticleManager.h"
#include "Header/Graphics/GPUParticle/GPUParticleEmitter.h"
class SampleScene : public GatesEngine::Scene
{
private:
	struct UAVData
	{
		GatesEngine::Math::Vector4 pos;
		GatesEngine::Math::Vector4 vel;
	};

	GatesEngine::RootSignature* rootSignature;
	ID3DBlob* shaderBlob;
	ID3D12PipelineState* pipeline;
	ID3D12DescriptorHeap* heap;
	ID3D12Resource* buffer;
	ID3D12Resource* posBuffer;
	ID3D12Resource* addVectorBuffer;
	std::vector<UAVData> test;
	std::vector<GatesEngine::Math::Vector4> posDatas;
	UAVData* data;
	GatesEngine::Math::Vector4* posData;
	UAVData* addVectorData;
	int srvNum;
	bool flag;
	UAVData randomVector;

	GatesEngine::GPUParticleManager* gpuParticleManager;
	GatesEngine::GPUParticleEmitter gpuParticleEmitter;
	GatesEngine::GPUParticleEmitter gpuParticleEmitter2;
	GatesEngine::GPUParticleEmitter gpuParticleEmitter3;
	GatesEngine::GPUParticleEmitter gpuParticleEmitter4;
public:
	SampleScene();
	SampleScene(const char* sceneName);
	SampleScene(const char* sceneName, GatesEngine::Application* app);
	~SampleScene();
	void Initialize();
	void Update();
	void Draw();
};
