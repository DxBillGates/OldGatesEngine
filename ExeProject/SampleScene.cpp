#include "SampleScene.h"
#include "Header/Application/Application.h"
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
}
