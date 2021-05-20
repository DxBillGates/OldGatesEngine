#include "Game.h"
#include "SampleScene.h"

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
}

bool Game::LoadContents()
{
	sceneManager->AddScene(new SampleScene("SampleScene", this));
	sceneManager->ChangeScene("SampleScene");

	using namespace GatesEngine;
	using namespace GatesEngine::Math;
	testShader = new Shader(&graphicsDevice, std::wstring(L"Default"));
	testShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD ,InputLayout::NORMAL }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV});

	testTexShader = new Shader(&graphicsDevice, std::wstring(L"Texture"));
	testTexShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD ,InputLayout::NORMAL }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::SRV,RangeType::SRV },BlendMode::BLENDMODE_ALPHA,D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,false);

	testCBuffer.Create(&graphicsDevice, 0);
	testCBuffer.Map({Math::Matrix4x4::Identity()});
	testCBuffer2.Create(&graphicsDevice, 0);
	testCBuffer2.Map({ Math::Matrix4x4::Identity() });
	testCBuffer2.Map({ Math::Matrix4x4::Translate({-30,0,0}) });
	//“K“–‚Éè‘Å‚¿‚ÅƒƒbƒVƒ…ì‚é
	MeshData<VertexInfo::Vertex_UV_Normal> testMeshData;
	std::vector<VertexInfo::Vertex_UV_Normal>* vertices = testMeshData.GetVertices();
	std::vector<unsigned short>* indices = testMeshData.GetIndices();

	vertices->push_back({Vector3(),Vector2(0,0),Vector3(0,0,-1)});
	vertices->push_back({Vector3(10,0,0),Vector2(1,0),Vector3(0,0,-1)});
	vertices->push_back({Vector3(10,-10,0),Vector2(1,1),Vector3(0,0,-1)});
	vertices->push_back({Vector3(0,-10,0),Vector2(0,1),Vector3(0,0,-1)});

	indices->push_back(0);
	indices->push_back(1);
	indices->push_back(2);
	indices->push_back(2);
	indices->push_back(3);
	indices->push_back(0);
	testMesh.Create(&graphicsDevice, testMeshData);

	auto* g = gameObjectManager.Add(new GameObject());

	testRenderTex.Create(&graphicsDevice, { 1920,1080 });

	graphicsDevice.GetDescriptorHeapManager()->CreateSRV(graphicsDevice.GetDepthBuffer());

	return true;
}

bool Game::Initialize()
{
	gameObjectManager.Start();
	timer.SetFrameRate(144);
	return true;
}

bool Game::Update()
{
	testCBuffer.Map({ GatesEngine::Math::Matrix4x4::RotationY(angle) * GatesEngine::Math::Matrix4x4::Translate({0,0,0}) });
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
	mainCameraInfo.Set();
	worldLightInfo.Set();
	testCBuffer.Set();
	
	testMesh.Draw();
	sceneManager->Draw();
	testRenderTex.EndDraw();

	graphicsDevice.ClearRenderTargetWithOutDsv({ 135,206,235,0 });
	testTexShader->Set();
	mainCameraInfo.Set();
	//worldLightInfo.Set();
	testCBuffer2.Set();

	graphicsDevice.GetCmdList()->SetGraphicsRootDescriptorTable(5, graphicsDevice.GetDescriptorHeapManager()->GetSRVHandleForGPU(1));
	testRenderTex.Set();

	testMesh.Draw();


	graphicsDevice.ScreenFlip();
}


