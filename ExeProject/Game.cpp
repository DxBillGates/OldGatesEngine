#include "Game.h"
#include "SampleScene.h"
#include "..\GatesEngine\Header\Graphics\Helper\MeshCreater.h"
#include "Header/Graphics/Manager/ShaderManager.h"
#include "Header/Graphics/Manager/MeshManager.h"
#include "Header/Graphics/CBufferAllocater.h"

Game::Game():Application()
{
}

Game::Game(const GatesEngine::Math::Vector2& wSize, const char* title):Application(wSize,title)
{
}

Game::~Game()
{
}

bool Game::LoadContents()
{
	sceneManager->AddScene(new SampleScene("SampleScene", this));
	sceneManager->ChangeScene("SampleScene");

	using namespace GatesEngine;
	using namespace GatesEngine::Math;
	auto* testShader = graphicsDevice.GetShaderManager()->Add(new Shader(&graphicsDevice, std::wstring(L"Default")),"Default");
	testShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD ,InputLayout::NORMAL }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV});

	auto* testTexShader = graphicsDevice.GetShaderManager()->Add(new Shader(&graphicsDevice, std::wstring(L"Texture")),"Texture");
	testTexShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD ,InputLayout::NORMAL }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::SRV,RangeType::SRV },BlendMode::BLENDMODE_ALPHA,D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,false);

	auto* testLineShader = graphicsDevice.GetShaderManager()->Add(new Shader(&graphicsDevice, std::wstring(L"Line")),"Line");
	testLineShader->Create({ InputLayout::POSITION,InputLayout::COLOR }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::SRV,RangeType::SRV }, BlendMode::BLENDMODE_ALPHA, D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, true);


	//板ポリ生成
	MeshData<VertexInfo::Vertex_UV_Normal> testMeshData;
	MeshCreater::CreateQuad({ 100,100 }, { 1,1 }, testMeshData);
	graphicsDevice.GetMeshManager()->Add("Plane")->Create(&graphicsDevice, testMeshData);

	//グリッド生成
	MeshData<VertexInfo::Vertex_Color> testLineMeshData;
	MeshCreater::CreateGrid({ 10000,10000 }, 100, testLineMeshData);
	graphicsDevice.GetMeshManager()->Add("Grid")->Create(&graphicsDevice, testLineMeshData);

	auto* g = gameObjectManager.Add(new GameObject());

	testRenderTex.Create(&graphicsDevice, { 1920,1080 });

	graphicsDevice.GetCBVSRVUAVHeap()->CreateSRV(graphicsDevice.GetDepthBuffer());

	return true;
}

bool Game::Initialize()
{
	gameObjectManager.Start();
	timer.SetFrameRate(144);
	timer.SetIsShow(false);
	return true;
}

bool Game::Update()
{
	angle += 1.0f * timer.GetElapsedTime();
	gameObjectManager.Update();
	sceneManager->Update();
	return true;
}

void Game::Draw()
{
	//RenderTexture使うないバージョン
	//graphicsDevice.ClearRenderTarget({ 1,1,1,1 }, &testRenderTex);

	//graphicsDevice.GetShaderManager()->GetShader("Default")->Set();
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::RotationY(angle));
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, mainCamera.GetData());
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ GatesEngine::Math::Vector4(0,1,1,0).Normalize(),GatesEngine::Math::Vector4(1,0,0,1) });	
	//graphicsDevice.GetMeshManager()->GetMesh("Plane")->Draw();
	//testRenderTex.EndDraw();

	//graphicsDevice.ClearRenderTargetOutDsv({ 135,206,235,0 });

	//graphicsDevice.GetShaderManager()->GetShader("Texture")->Set();
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Translate({ -30,0,0 }));
	//graphicsDevice.GetCmdList()->SetGraphicsRootDescriptorTable(5, graphicsDevice.GetCBVSRVUAVHeap()->GetSRVHandleForSRV(1));
	//testRenderTex.Set();
	//graphicsDevice.GetMeshManager()->GetMesh("Plane")->Draw();

	//graphicsDevice.GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	//graphicsDevice.GetShaderManager()->GetShader("Line")->Set();
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(0,GatesEngine::Math::Matrix4x4::Identity());
	//graphicsDevice.GetMeshManager()->GetMesh("Grid")->Draw();


	//RenderTexture使わないバージョン
	graphicsDevice.ClearRenderTarget({ 135,206,235,0 });

	graphicsDevice.GetShaderManager()->GetShader("Default")->Set();
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::RotationY(angle));
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, mainCamera.GetData());
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ GatesEngine::Math::Vector4(0,1,1,0).Normalize(),GatesEngine::Math::Vector4(1,0,0,1) });
	graphicsDevice.GetMeshManager()->GetMesh("Plane")->Draw();

	graphicsDevice.GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	graphicsDevice.GetShaderManager()->GetShader("Line")->Set();
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Identity());
	graphicsDevice.GetMeshManager()->GetMesh("Grid")->Draw();

	//sceneManager->Draw();
	graphicsDevice.ScreenFlip();
}


