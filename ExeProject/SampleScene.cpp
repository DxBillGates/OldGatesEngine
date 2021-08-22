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
	//ルートシグネチャの生成
	rootSignature = new GatesEngine::RootSignature(graphicsDevice, { GatesEngine::RangeType::UAV,GatesEngine::RangeType::SRV });
	rootSignature->Create();

	//CSのコンパイル＆生成
	auto hr = D3DCompileFromFile(L"Resources/Shader/testCS.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "cs_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &shaderBlob, nullptr);

	D3D12_COMPUTE_PIPELINE_STATE_DESC pipeDesc = {};
	pipeDesc.CS.pShaderBytecode = shaderBlob->GetBufferPointer();
	pipeDesc.CS.BytecodeLength = shaderBlob->GetBufferSize();
	pipeDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	pipeDesc.NodeMask = 0;
	pipeDesc.pRootSignature = rootSignature->Get();

	hr = graphicsDevice->GetDevice()->CreateComputePipelineState(&pipeDesc, IID_PPV_ARGS(&pipeline));

	gpuParticleManager = new GatesEngine::GPUParticleManager(graphicsDevice);
	int value = 5000;
	gpuParticleEmitter.Create(gpuParticleManager, value);
	gpuParticleEmitter2.Create(gpuParticleManager, value);
	gpuParticleEmitter3.Create(gpuParticleManager, value);
	gpuParticleEmitter4.Create(gpuParticleManager, value);
}

SampleScene::~SampleScene()
{
	delete rootSignature;
	COM_RELEASE(pipeline);
	COM_RELEASE(shaderBlob);
	delete gpuParticleManager;
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
	graphicsDevice->ClearRenderTarget({ 135,206,235,0 });
	//graphicsdevice->clearrendertarget({ 0,0,0,0 });

	//グリッド描画
	graphicsDevice->GetShaderManager()->GetShader("Line")->Set();
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(2, app->GetMainCamera()->GetData());
	graphicsDevice->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Identity());
	graphicsDevice->GetMeshManager()->GetMesh("Grid")->Draw();
	static float angle = 0;
	angle += 0.02f;
	graphicsDevice->GetShaderManager()->GetShader("DefaultMeshShader")->Set();
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ {0,-1,0,0},{1,1,1,1} });
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(2, app->GetMainCamera()->GetData());
	graphicsDevice->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(0,GatesEngine::Math::Matrix4x4::Scale(100) * GatesEngine::Math::Matrix4x4::RotationY(angle));
	graphicsDevice->GetMeshManager()->GetMesh("Sphere")->Draw();


	gpuParticleEmitter.Draw(app->GetMainCamera(),pipeline,rootSignature->Get(),10);
	gpuParticleEmitter2.Draw(app->GetMainCamera(), pipeline, rootSignature->Get(), 100);
	gpuParticleEmitter3.Draw(app->GetMainCamera(), pipeline, rootSignature->Get(), 500);
	gpuParticleEmitter4.Draw(app->GetMainCamera(), pipeline, rootSignature->Get(), 1000);

	//graphicsDevice->ScreenFlip();

}
