#include "SampleScene.h"
#include "Header/Application/Application.h"
#include "Header/Graphics/Graphics.h"
//#include "Header/Math/Math.h"
#include <stdio.h>

SampleScene::SampleScene() :Scene()
{
}

SampleScene::SampleScene(const char* sceneName) : Scene(sceneName)
{
}

SampleScene::SampleScene(const char* sceneName, GatesEngine::Application* app) : Scene(sceneName, app)
{
}

SampleScene::~SampleScene()
{
}

void SampleScene::Initialize()
{
	t = 0;
	flag = true;
}

void SampleScene::Update()
{
	if (flag)t += app->GetTimer()->GetElapsedTime();
	else t -= app->GetTimer()->GetElapsedTime();

	if (t < 0)
	{
		t = 0;
		flag = true;
	}

	if (t > 1)
	{
		t = 1;
		flag = false;
	}
}

void SampleScene::Draw()
{
	using namespace GatesEngine::Math;
	float a = Easing::Lerp(0, 1, Easing::EaseInCubic(t));
	float b = Easing::Lerp(0, 1, t);

	graphicsDevice->GetCBufferAllocater()->ResetCurrentUseNumber();
	graphicsDevice->ClearRenderTarget({ 135,206,235,0 });

	//シェーダー、カメラ、ライトをセット
	graphicsDevice->GetShaderManager()->GetShader("DefaultMeshShader")->Set();
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(2, app->GetMainCamera()->GetData());
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ GatesEngine::Math::Vector4(0,1,1,0).Normalize(),GatesEngine::Math::Vector4(1,0,0,1) });

	graphicsDevice->GetCBufferAllocater()->BindAndAttach(0, Matrix4x4::Scale(Vector3(1, a, 1)) * Matrix4x4::Translate(Vector3(-100, 0, 0)));
	graphicsDevice->GetMeshManager()->GetMesh("Plane")->Draw();

	graphicsDevice->GetCBufferAllocater()->BindAndAttach(0, Matrix4x4::Scale(Vector3(1, b, 1)) * Matrix4x4::Translate(Vector3(100, 0, 0)));
	graphicsDevice->GetMeshManager()->GetMesh("Plane")->Draw();

	//2D描画
	graphicsDevice->GetShaderManager()->GetShader("DefaultSpriteShader")->Set();
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(0, Matrix4x4::Translate(Vector3(50, 50, 0)));
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(1, Vector4(1,1,1,a));
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(2, Matrix4x4::GetOrthographMatrix(app->GetWindow()->GetWindowSize()));

	graphicsDevice->GetMeshManager()->GetMesh("Plane")->Draw();

	graphicsDevice->GetCBufferAllocater()->BindAndAttach(0, Matrix4x4::Translate(Vector3(150, 50, 0)));
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(1, Vector4(1, 1, 1, b));

	graphicsDevice->GetMeshManager()->GetMesh("Plane")->Draw();

	graphicsDevice->ClearRenderTarget({ 135,206,235,0 },false);
	//グリッド描画
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(2, app->GetMainCamera()->GetData());
	graphicsDevice->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	graphicsDevice->GetShaderManager()->GetShader("Line")->Set();
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Identity());
	graphicsDevice->GetMeshManager()->GetMesh("Grid")->Draw();
}
