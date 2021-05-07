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
	testShader = new Shader(&graphicsDevice,std::wstring(L"Default"));
	testShader->Create({InputLayout::POSITION,InputLayout::TEXCOORD ,InputLayout::NORMAL }, {RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV });

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
	gameObjectManager.Update();
	sceneManager->Update();
	return true;
}

void Game::Draw()
{
	graphicsDevice.ClearRenderTarget({135,206,235,0});
	graphicsDevice.SetDescriptorHeap();
	testShader->Set();
	//mainCamera.SetCmdList();
	//mainWorldLight.SetCmdList();
	sceneManager->Draw();
	graphicsDevice.ScreenFlip();
}


