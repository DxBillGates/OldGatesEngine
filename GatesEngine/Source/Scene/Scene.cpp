#include "..\..\Header\Scene\Scene.h"
#include <stdio.h>

GatesEngine::Scene::Scene() :sceneName("scene"), changeNextSceneFlag(false)
{
#ifdef _DEBUG
	printf("ñºñ≥ÇµÇÃSceneê∂ê¨\n");
#endif 
}

GatesEngine::Scene::Scene(const char* sceneName) :sceneName(sceneName), changeNextSceneFlag(false)
{
#ifdef _DEBUG
	printf("%sê∂ê¨\n", sceneName);
#endif 
}

GatesEngine::Scene::Scene(const char* sceneName, Application* app) :sceneName(sceneName), changeNextSceneFlag(false)
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
