#include "SampleScene.h"
#include "Header/Application/Application.h"
#include "Header/Graphics/Graphics.h"
#include "Header/Math/Math.h"
#include <stdio.h>
#include <d3dcompiler.h>

SampleScene::SampleScene() :Scene()
{
}

SampleScene::SampleScene(const char* sceneName) : Scene(sceneName)
{
}

SampleScene::SampleScene(const char* sceneName, GatesEngine::Application* app) : Scene(sceneName, app)
{
	testComputeShader = new GatesEngine::ComputePipeline(graphicsDevice, L"test");
	testComputeShader->Create({ GatesEngine::RangeType::UAV,GatesEngine::RangeType::SRV });

	gpuParticleManager = new GatesEngine::GPUParticleManager(graphicsDevice);
	int value = 10000;
	gpuParticleEmitter.Create(gpuParticleManager, value);
	gpuParticleEmitter2.Create(gpuParticleManager, value);
	gpuParticleEmitter3.Create(gpuParticleManager, value);
	gpuParticleEmitter4.Create(gpuParticleManager, value);
}

SampleScene::~SampleScene()
{
	delete gpuParticleManager;
	delete testComputeShader;
}

void SampleScene::Initialize()
{
}

void SampleScene::Update()
{
	gpuParticleEmitter.Update();
	gpuParticleEmitter2.Update();
	gpuParticleEmitter3.Update();
	gpuParticleEmitter4.Update();
}

void SampleScene::Draw()
{
	using namespace GatesEngine::Math;

	//graphicsDevice->GetCBufferAllocater()->ResetCurrentUseNumber();
	//graphicsDevice->ClearRenderTarget({ 135,206,235,0 });
	//graphicsDevice->ClearRenderTarget({ 0,0,0,0 });

	//ƒOƒŠƒbƒh•`‰æ
	//graphicsDevice->GetShaderManager()->GetShader("Line")->Set();
	//graphicsDevice->GetCBufferAllocater()->BindAndAttach(2, app->GetMainCamera()->GetData());
	//graphicsDevice->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	//graphicsDevice->GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Identity());
	//graphicsDevice->GetMeshManager()->GetMesh("Grid")->Draw();

	graphicsDevice->GetShaderManager()->GetShader("DefaultMeshShader")->Set();
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ {0,0,1,0},{1,1,1,1} });
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(2, app->GetMainCamera()->GetData());
	graphicsDevice->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(0,GatesEngine::Math::Matrix4x4::Identity());
	graphicsDevice->GetMeshManager()->GetMesh("Cube")->Draw();


	gpuParticleEmitter.Draw(app->GetMainCamera() ,testComputeShader,1000);
	gpuParticleEmitter2.Draw(app->GetMainCamera(),testComputeShader, 100);
	gpuParticleEmitter3.Draw(app->GetMainCamera(),testComputeShader, 500);
	gpuParticleEmitter4.Draw(app->GetMainCamera(),testComputeShader, 1000);

	//graphicsDevice->ScreenFlip();

}
