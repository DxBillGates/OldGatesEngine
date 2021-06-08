#include "TestBehaviour2.h"
#include "Header/GameObject/GameObject.h"
#include "Header\GameObject\GameObjectManager.h"
#include "Header\Scene\Scene.h"
#include "Header\Application\Application.h"

void TestBehaviour2::Update()
{
	t += gameObject->GetManager()->GetScene()->GetApplication()->GetTimer()->GetElapsedTime();
	if (t >= 1)
	{
		t = 0;
	}
	using namespace GatesEngine::Math;
	gameObject->GetTransform().position.y = GatesEngine::Math::Vector3::Lerp(Vector3(), Vector3(0, 200, 0), Easing::EaseInOutExpo(t)).y;
}
