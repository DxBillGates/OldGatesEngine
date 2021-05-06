#include "..\..\Header\Application\Application.h"

GatesEngine::Application::Application() 
	:timer(Util::Timer()),
	mainWindow(Window()),
	sceneManager(SceneManager::GetInstance()),
	gameObjectManager(GameObjectManager())
{
	using namespace GatesEngine::Math;
	mainWindow.Create(Vector2(1920, 1080), "GatesEngine");
	mainWindow.PreviewWindow();
	graphicsDevice.Create(&mainWindow);
	//graphicsDevice.SetViewport(Vector2(1920,1080));
}

GatesEngine::Application::Application(const Math::Vector2& wSize, const char* title) 
	: timer(Util::Timer()),
	mainWindow(Window()),
	sceneManager(SceneManager::GetInstance()),
	gameObjectManager(GameObjectManager())
{
	mainWindow.Create(wSize, title);
	mainWindow.PreviewWindow();
	graphicsDevice.Create(&mainWindow);
	//graphicsDevice.SetViewport(wSize);
}

GatesEngine::Application::~Application()
{
}

bool GatesEngine::Application::LoadContents()
{
	return true;
}

bool GatesEngine::Application::Initialize()
{
	return true;
}

bool GatesEngine::Application::Update()
{
	return true;
}

void GatesEngine::Application::Draw()
{
}

void GatesEngine::Application::Run()
{
	if (!LoadContents())return;
	if (!Initialize())return;

	while (true)
	{
		if (!Update())break;
		Draw();
		if (!mainWindow.ProcessMessage())break;
	}
}

GatesEngine::Util::Timer* GatesEngine::Application::GetTimer()
{
	return &timer;
}

GatesEngine::SceneManager* GatesEngine::Application::GetSceneManager()
{
	return sceneManager;
}
