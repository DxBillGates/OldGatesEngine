#pragma once
#include "Header/Application/Application.h"
#include "Header/GameObject/GameObject.h"
#include "Header/Graphics/Shader.h"
#include "Header/Graphics/CBuffer.h"
#include "Header/Graphics/Mesh.h"
#include "Header/Graphics/RenderTexture.h"
#include "Header/Graphics/DepthStencilTexture.h"

class Game : public GatesEngine::Application
{
private:
	float angle;
	GatesEngine::RenderTexture testRenderTex;
	GatesEngine::RenderTexture testRenderTex2;
	GatesEngine::RenderTexture testRenderTex3;
	GatesEngine::RenderTexture testRenderTex4;
	GatesEngine::DepthStencilTexture testDepthTex;
	std::vector<float> gaussData;

	struct TestData
	{
		float data[8];
	};
	TestData testData;
public:
	Game();
	Game(const GatesEngine::Math::Vector2& wSize, const char* title);
	~Game();
	bool LoadContents()override;
	bool Initialize()override;
	bool Update()override;
	void Draw()override;
	std::vector<float> GetGaussData(size_t count, float s);
};
