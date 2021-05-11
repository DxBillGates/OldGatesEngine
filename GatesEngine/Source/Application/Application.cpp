#include "..\..\Header\Application\Application.h"

GatesEngine::Application::Application()
	:Application({ 1920,1080 }, "GatesEngine")
{
}

GatesEngine::Application::Application(const Math::Vector2& wSize, const char* title)
	: timer(Util::Timer())
	, mainWindow(Window())
	, sceneManager(SceneManager::GetInstance())
	, gameObjectManager(GameObjectManager())
	, mainCameraInfo({})
	, worldLightInfo({})
{
	mainWindow.Create(wSize, title);
	mainWindow.PreviewWindow();
	graphicsDevice.Create(&mainWindow);

	Math::Vector3 cameraPos{ 0,0,-20 }, cameraTargetPos{ 0,0,0 }, cameraUp{0,1,0};
	mainCameraInfo.Create(&graphicsDevice, 2);
	mainCameraInfo.Map({ Math::Matrix4x4::GetViewMatrixLookAt(cameraPos,cameraTargetPos,cameraUp),
						 Math::Matrix4x4::GetPerspectiveMatrix(90,mainWindow.GetWindowAspect()),
						 Math::Vector4(cameraPos) });

	worldLightInfo.Create(&graphicsDevice,3);
	worldLightInfo.Map({ Math::Vector4(0,1,1,0).Normalize(),Math::Vector4(1,0,0,1) });
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
