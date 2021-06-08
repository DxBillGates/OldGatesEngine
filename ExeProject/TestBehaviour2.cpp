#include "TestBehaviour2.h"
#include "Header/GameObject/GameObject.h"
#include "Header\GameObject\GameObjectManager.h"
#include "Header\Scene\Scene.h"
#include "Header\Application\Application.h"
#include "Header/Input/Input.h"

void TestBehaviour2::Update()
{
	//t += gameObject->GetManager()->GetScene()->GetApplication()->GetTimer()->GetElapsedTime();
	//if (t >= 1)
	//{
	//	t = 0;
	//}
	//using namespace GatesEngine::Math;
	//gameObject->GetTransform().position.y = GatesEngine::Math::Vector3::Lerp(Vector3(), Vector3(0, 200, 0), Easing::EaseInOutExpo(t)).y;
	//gameObject->GetTransform().rotation = GatesEngine::Math::Vector3::Lerp(Vector3(), Vector3(0, 200, 0), Easing::EaseInOutExpo(t));
	if (GatesEngine::Input::GetInstance()->GetKeyboard()->CheckHitKey(GatesEngine::Keys::SPACE))
	{
		gameObject->GetTransform().position.y += 0.1f;
	}
}
