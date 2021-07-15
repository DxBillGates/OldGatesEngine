#pragma once
#include "Header/Scene/Scene.h"
#include "Header/Graphics/RootSignature.h"
#include "Header/Math/Math.h"
#include "Header/Graphics/GPUParticle/GPUParticleManager.h"
#include "Header/Graphics/GPUParticle/GPUParticleEmitter.h"
#include "Header/Graphics/ComputePipeline.h"
class SampleScene : public GatesEngine::Scene
{
private:
	GatesEngine::ComputePipeline* testComputeShader;

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
