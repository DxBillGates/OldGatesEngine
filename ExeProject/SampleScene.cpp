#include "SampleScene.h"
#include "Header/Application/Application.h"
#include "Header/Graphics/Graphics.h"
#include <stdio.h>

SampleScene::SampleScene() :Scene()
{
}

SampleScene::SampleScene(const char* sceneName) : Scene(sceneName)
{
}

SampleScene::SampleScene(const char* sceneName, GatesEngine::Application* app) : Scene(sceneName, app)
{
}

SampleScene::~SampleScene()
{
}

void SampleScene::Initialize()
{
}

void SampleScene::Update()
{
}

void SampleScene::Draw()
{
	graphicsDevice->GetCBufferAllocater()->ResetCurrentUseNumber();
	graphicsDevice->ClearRenderTarget({ 135,206,235,0 });

	graphicsDevice->GetShaderManager()->GetShader("Default")->Set();
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(2, app->GetMainCamera()->GetData());
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ GatesEngine::Math::Vector4(0,1,1,0).Normalize(),GatesEngine::Math::Vector4(1,0,0,1) });

	static float a = 0;
	a += 0.016f;
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			graphicsDevice->GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::RotationY(a) * GatesEngine::Math::Matrix4x4::Translate({ 100 * (float)i,0,100 * (float)j, }));
			graphicsDevice->GetMeshManager()->GetMesh("Plane")->Draw();
		}
	}

	graphicsDevice->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	graphicsDevice->GetShaderManager()->GetShader("Line")->Set();
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Identity());
	graphicsDevice->GetMeshManager()->GetMesh("Grid")->Draw();
}
