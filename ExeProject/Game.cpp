#include "Game.h"
#include "SampleScene.h"
#include "..\GatesEngine\Header\Graphics\Helper\MeshCreater.h"
#include "TestBehaviour.h"
#include "TestBehaviour2.h"

Game::Game():Application()
{
}

Game::Game(const GatesEngine::Math::Vector2& wSize, const char* title):Application(wSize,title)
{
}

Game::~Game()
{
	delete testShader;
	delete testTexShader;
	delete testLineShader;
}

bool Game::LoadContents()
{
	auto* s = sceneManager->AddScene(new SampleScene("SampleScene", this));
	gameObjectManager.SetScene(s);
	sceneManager->ChangeScene("SampleScene");

	using namespace GatesEngine;
	using namespace GatesEngine::Math;
	testShader = new Shader(&graphicsDevice, std::wstring(L"Default"));
	testShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD ,InputLayout::NORMAL }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV});

	testTexShader = new Shader(&graphicsDevice, std::wstring(L"Texture"));
	testTexShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD ,InputLayout::NORMAL }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::SRV,RangeType::SRV },BlendMode::BLENDMODE_ALPHA,D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,false);

	testLineShader = new Shader(&graphicsDevice, std::wstring(L"Line"));
	testLineShader->Create({ InputLayout::POSITION,InputLayout::COLOR }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::SRV,RangeType::SRV }, BlendMode::BLENDMODE_ALPHA, D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, false);

	testCBuffer.Create(&graphicsDevice, 0);
	testCBuffer.Map({Math::Matrix4x4::Identity()});
	testCBuffer2.Create(&graphicsDevice, 0);
	testCBuffer2.Map({ Math::Matrix4x4::Identity() });
	testCBuffer2.Map({ Math::Matrix4x4::Translate({-30,0,0}) });
	testCBuffer3.Create(&graphicsDevice, 0);
	testCBuffer3.Map({ Math::Matrix4x4::Identity() });
	
	//板ポリ生成
	MeshData<VertexInfo::Vertex_UV_Normal> testMeshData;
	MeshCreater::CreateQuad({ 100,100 }, { 1,1 }, testMeshData);
	testMesh.Create(&graphicsDevice, testMeshData);

	//グリッド生成
	MeshData<VertexInfo::Vertex_Color> testLineMeshData;
	MeshCreater::CreateGrid({ 10000,10000 }, 100, testLineMeshData);
	testLineMesh.Create(&graphicsDevice, testLineMeshData);

	g = gameObjectManager.Add(new GameObject());
	g->GetTransform().position = Vector3(100, 100, 100);
	g->AddBehavior<TestBehaviour>();
	g->AddBehavior<TestBehaviour2>();

	testRenderTex.Create(&graphicsDevice, { 1920,1080 });

	graphicsDevice.GetDescriptorHeapManager()->CreateSRV(graphicsDevice.GetDepthBuffer());

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
	testCBuffer.Map({ GatesEngine::Math::Matrix4x4::RotationY(angle) * GatesEngine::Math::Matrix4x4::Translate({0,0,0}) });
	testCBuffer2.Map({ GatesEngine::Math::Matrix4x4::Translate(g->GetTransform().position) });
	angle += 1.0f * timer.GetElapsedTime();
	gameObjectManager.Update();
	sceneManager->Update();
	return true;
}

void Game::Draw()
{
	graphicsDevice.ClearRenderTarget({ 1,1,1,1 }, &testRenderTex);
	graphicsDevice.SetDescriptorHeap();
	testShader->Set();
	//testTexShader->Set();
	mainCamera.Set();
	worldLightInfo.Set();
	testCBuffer.Set();
	
	testMesh.Draw();
	sceneManager->Draw();
	testRenderTex.EndDraw();

	graphicsDevice.ClearRenderTargetOutDsv({ 135,206,235,0 });

	testTexShader->Set();
	//worldLightInfo.Set();
	testCBuffer2.Set();
	graphicsDevice.GetCmdList()->SetGraphicsRootDescriptorTable(5, graphicsDevice.GetDescriptorHeapManager()->GetSRVHandleForGPU(1));
	testRenderTex.Set();
	testMesh.Draw();

	graphicsDevice.GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	testLineShader->Set();
	testCBuffer3.Set();
	testLineMesh.Draw();

	graphicsDevice.ScreenFlip();
}


