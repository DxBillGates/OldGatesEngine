#include "Game.h"
#include "SampleScene.h"
#include "Header/Graphics/Shader.h"

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
	Shader* testShader = new Shader(&graphicsDevice,std::wstring(L"Simple"));
	testShader->Create({InputLayout::POSITION,InputLayout::TEXCOORD ,InputLayout::NORMAL }, {RangeType::CBV,RangeType::CBV});


	using namespace GatesEngine;
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
	graphicsDevice.ClearRenderTarget({1,0,0,0});
	sceneManager->Draw();
	graphicsDevice.ScreenFlip();
}


