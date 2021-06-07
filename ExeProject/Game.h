#pragma once
#include "Header/Application/Application.h"
#include "Header/GameObject/GameObject.h"
#include "Header/Graphics/Shader.h"
#include "Header/Graphics/CBuffer.h"
#include "Header/Graphics/Mesh.h"
#include "Header/Graphics/RenderTexture.h"

class Game : public GatesEngine::Application
{
private:
	GatesEngine::CBuffer<GatesEngine::B0> testCBuffer;
	GatesEngine::CBuffer<GatesEngine::B0> testCBuffer2;
	GatesEngine::CBuffer<GatesEngine::B0> testCBuffer3;
	GatesEngine::CBuffer<GatesEngine::Math::Vector4> bloomInfo;
	GatesEngine::Shader* testShader;
	GatesEngine::Shader* testTexShader;
	GatesEngine::Shader* testLineShader;
	GatesEngine::Shader* testPostEffectShader;
	GatesEngine::Mesh testMesh;
	GatesEngine::Mesh testLineMesh;
	float angle;
	float binfo;
	GatesEngine::RenderTexture testRenderTex;
public:
	Game();
	Game(const GatesEngine::Math::Vector2& wSize, const char* title);
	~Game();
	bool LoadContents()override;
	bool Initialize()override;
	bool Update()override;
	void Draw()override;
};
