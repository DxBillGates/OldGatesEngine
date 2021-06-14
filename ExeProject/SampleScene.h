#pragma once
#include "Header/Scene/Scene.h"
class SampleScene : public GatesEngine::Scene
{
private:
	float t;
	bool flag;
public:
	SampleScene();
	SampleScene(const char* sceneName);
	SampleScene(const char* sceneName, GatesEngine::Application* app);
	~SampleScene();
	void Initialize();
	void Update();
	void Draw();
};
