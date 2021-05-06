#pragma once
#include "Header/Application/Application.h"
#include "Header/GameObject/GameObject.h"

class Game : public GatesEngine::Application
{
private:
public:
	Game();
	Game(const GatesEngine::Math::Vector2& wSize, const char* title);
	~Game();
	bool LoadContents()override;
	bool Initialize()override;
	bool Update()override;
	void Draw()override;
};
