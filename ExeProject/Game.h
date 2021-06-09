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
	float angle;
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
