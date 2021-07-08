#pragma once
#include "Header/Scene/Scene.h"
#include "Header/Graphics/RootSignature.h"
#include "Header/Math/Math.h"
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
public:
	SampleScene();
	SampleScene(const char* sceneName);
	SampleScene(const char* sceneName, GatesEngine::Application* app);
	~SampleScene();
	void Initialize();
	void Update();
	void Draw();
};
