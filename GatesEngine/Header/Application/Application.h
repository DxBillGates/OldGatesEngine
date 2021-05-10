#pragma once
#include "..\..\Header\Math\Vector2.h"
#include "..\..\Header\Util\Timer.h"
#include "..\Window\Window.h"
#include "..\..\Header\Scene\SceneManager.h"
#include "..\..\Header\GameObject\GameObjectManager.h"
#include "..\Graphics\GraphicsDevice.h"
#include "..\Graphics\CBuffer.h"

namespace GatesEngine
{
	class Application
	{
	private:
	protected:
		Util::Timer timer;
		Window mainWindow;
		SceneManager* sceneManager;
		GameObjectManager gameObjectManager;
		GraphicsDevice graphicsDevice;
		CBuffer<B2> mainCameraInfo;
		CBuffer<B3> worldLightInfo;
	public:
		Application();
		Application(const Math::Vector2& wSize, const char* title);
		virtual ~Application();
		virtual bool LoadContents();
		virtual bool Initialize();
		virtual bool Update();
		virtual void Draw();
		virtual void Run();

		Util::Timer* GetTimer();
		SceneManager* GetSceneManager();
	};
}