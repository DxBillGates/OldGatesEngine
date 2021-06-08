#include "..\..\Header\Scene\Scene.h"
#include <stdio.h>

GatesEngine::Scene::Scene() :Scene("unnamedScene", nullptr)
{
}

GatesEngine::Scene::Scene(const char* sceneName) :Scene(sceneName,nullptr)
{
}

GatesEngine::Scene::Scene(const char* sceneName, Application* app) :sceneName(sceneName), changeNextSceneFlag(false),pApp(app)
{
#ifdef _DEBUG
	printf("%sê∂ê¨\n", sceneName);
#endif 
}

GatesEngine::Scene::~Scene()
{
}

const char* GatesEngine::Scene::GetSceneName()
{
	return sceneName;
}

bool GatesEngine::Scene::IsChangeScene()
{
	return changeNextSceneFlag;
}

GatesEngine::Application* GatesEngine::Scene::GetApplication()
{
	return pApp;
}
