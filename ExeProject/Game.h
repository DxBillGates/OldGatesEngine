#pragma once
#include "Header/Application/Application.h"
#include "Header/GameObject/GameObject.h"
#include "Header/Graphics/Shader.h"
#include "Header/Graphics/CBuffer.h"
#include "Header/Graphics/Mesh.h"
#include "Header/Graphics/RenderTexture.h"
#include "Header/Graphics/ShaderManager.h"

class Game : public GatesEngine::Application
{
private:
	GatesEngine::CBuffer<GatesEngine::B0> testCBuffer;
	GatesEngine::CBuffer<GatesEngine::B0> testCBuffer2;
	GatesEngine::CBuffer<GatesEngine::B0> testCBuffer3;
	GatesEngine::Shader* testShader;
	GatesEngine::Shader* testTexShader;
	GatesEngine::Shader* testLineShader;
	GatesEngine::Mesh testMesh;
	GatesEngine::Mesh testLineMesh;
	float angle;
	GatesEngine::RenderTexture testRenderTex;
	GatesEngine::ShaderManager testShaderManager;
public:
	Game();
	Game(const GatesEngine::Math::Vector2& wSize, const char* title);
	~Game();
	bool LoadContents()override;
	bool Initialize()override;
	bool Update()override;
	void Draw()override;
};
