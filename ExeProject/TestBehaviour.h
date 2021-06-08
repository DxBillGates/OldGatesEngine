#pragma once
#include "Header/Component/Behaviour.h"
class TestBehaviour : public GatesEngine::Behaviour
{
private:
	float t = 0;
public:
	void Update() override;
};
