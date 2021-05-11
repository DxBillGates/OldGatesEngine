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
}

bool Game::LoadContents()
{
	sceneManager->AddScene(new SampleScene("SampleScene", this));
	sceneManager->ChangeScene("SampleScene");

	using namespace GatesEngine;
	using namespace GatesEngine::Math;
	testShader = new Shader(&graphicsDevice, std::wstring(L"Default"));
	testShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD ,InputLayout::NORMAL }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV });

	testCBuffer.Create(&graphicsDevice, 0);
	testCBuffer.Map({Math::Matrix4x4::Identity()});

	//“K“–‚Éè‘Å‚¿‚ÅƒƒbƒVƒ…ì‚é
	MeshData<VertexInfo::Vertex_UV_Normal> testMeshData;
	std::vector<VertexInfo::Vertex_UV_Normal>* vertices = testMeshData.GetVertices();
	std::vector<unsigned short>* indices = testMeshData.GetIndices();

	vertices->push_back({Vector3(),Vector2(),Vector3(0,0,-1)});
	vertices->push_back({Vector3(10,0,0),Vector2(),Vector3(0,0,-1)});
	vertices->push_back({Vector3(10,-10,0),Vector2(),Vector3(0,0,-1)});
	vertices->push_back({Vector3(0,-10,0),Vector2(),Vector3(0,0,-1)});

	indices->push_back(0);
	indices->push_back(1);
	indices->push_back(2);
	indices->push_back(2);
	indices->push_back(3);
	indices->push_back(0);
	testMesh.Create(&graphicsDevice, testMeshData);

	auto* g = gameObjectManager.Add(new GameObject());

	return true;
}

bool Game::Initialize()
{
	gameObjectManager.Start();
	return true;
}

bool Game::Update()
{
	testCBuffer.Map({ GatesEngine::Math::Matrix4x4::RotationY(angle) });
	angle += 0.0001f;
	gameObjectManager.Update();
	sceneManager->Update();
	return true;
}

void Game::Draw()
{
	graphicsDevice.ClearRenderTarget({135,206,235,0});
	graphicsDevice.SetDescriptorHeap();
	testShader->Set();
	mainCameraInfo.Set();
	worldLightInfo.Set();
	testCBuffer.Set();
	testMesh.Draw();
	sceneManager->Draw();
	graphicsDevice.ScreenFlip();
}


