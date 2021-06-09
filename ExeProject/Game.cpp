#include "Game.h"
#include "SampleScene.h"
#include "..\GatesEngine\Header\Graphics\Helper\MeshCreater.h"

Game::Game() :Application()
{
}

Game::Game(const GatesEngine::Math::Vector2& wSize, const char* title) : Application(wSize, title)
{
}

Game::~Game()
{
	delete testShader;
	delete testTexShader;
	delete testLineShader;
}

bool Game::LoadContents()
{
	sceneManager->AddScene(new SampleScene("SampleScene", this));
	sceneManager->ChangeScene("SampleScene");

	using namespace GatesEngine;
	using namespace GatesEngine::Math;
	testShader = new Shader(&graphicsDevice, std::wstring(L"Default"));
	testShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD ,InputLayout::NORMAL }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV });

	testTexShader = new Shader(&graphicsDevice, std::wstring(L"Texture"));
	testTexShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD ,InputLayout::NORMAL }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::SRV,RangeType::SRV }, BlendMode::BLENDMODE_ALPHA, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, false);

	testLineShader = new Shader(&graphicsDevice, std::wstring(L"Line"));
	testLineShader->Create({ InputLayout::POSITION,InputLayout::COLOR }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::SRV,RangeType::SRV }, BlendMode::BLENDMODE_ALPHA, D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, false);

	testCBuffer.Create(&graphicsDevice, 0);
	testCBuffer.Map({ Math::Matrix4x4::Identity() });
	testCBuffer2.Create(&graphicsDevice, 0);
	testCBuffer2.Map({ Math::Matrix4x4::Identity() });
	testCBuffer2.Map({ Math::Matrix4x4::Translate({-30,0,0}) });
	testCBuffer3.Create(&graphicsDevice, 0);
	testCBuffer3.Map({ Math::Matrix4x4::Identity() });

	//�|������
	MeshData<VertexInfo::Vertex_UV_Normal> testMeshData;
	MeshCreater::CreateQuad({ 100,100 }, { 1,1 }, testMeshData);
	testMesh.Create(&graphicsDevice, testMeshData);

	//�O���b�h����
	MeshData<VertexInfo::Vertex_Color> testLineMeshData;
	MeshCreater::CreateGrid({ 10000,10000 }, 100, testLineMeshData);
	testLineMesh.Create(&graphicsDevice, testLineMeshData);

	auto* g = gameObjectManager.Add(new GameObject());

	testRenderTex.Create(&graphicsDevice, { 1920,1080 });

	graphicsDevice.GetDescriptorHeapManager()->CreateSRV(graphicsDevice.GetDepthBuffer());

	//�萔�o�b�t�@��256*value�o�C�g���m��
	int value = 10000;
	testHeap.SetGraphicsDevice(&graphicsDevice);
	testHeap.Create({ (float)value,64,0 });

	test.SetGraphicsDevice(&graphicsDevice);
	test.SetHeap(&testHeap);
	test.CreateBuffer();


	Matrix4x4 a = Matrix4x4::Identity();

	return true;
}

bool Game::Initialize()
{
	gameObjectManager.Start();
	timer.SetFrameRate(144);
	timer.SetIsShow(false);
	return true;
}

bool Game::Update()
{
	testCBuffer.Map({ GatesEngine::Math::Matrix4x4::RotationY(angle) * GatesEngine::Math::Matrix4x4::Translate({0,0,0}) });
	angle += 1.0f * timer.GetElapsedTime();
	gameObjectManager.Update();
	sceneManager->Update();
	test.ResetCurrentUseNumber();
	return true;
}

void Game::Draw()
{
	graphicsDevice.ClearRenderTarget({ 1,1,1,1 }, &testRenderTex);
	testShader->Set();

	GatesEngine::Math::Matrix4x4 m = GatesEngine::Math::Matrix4x4::RotationY(angle);
	test.BindAndAttachData(0, &m, sizeof(m));
	GatesEngine::B2& cameraData = mainCamera.GetData();
	test.BindAndAttachData(2, &cameraData, sizeof(cameraData));
	GatesEngine::B3 light = { GatesEngine::Math::Vector4(0,1,1,0).Normalize(),GatesEngine::Math::Vector4(1,0,0,1) };
	test.BindAndAttachData(3, &light, sizeof(light));

	//graphicsDevice.SetDescriptorHeap();
	//testTexShader->Set();
	//mainCamera.Set();
	//worldLightInfo.Set();
	//testCBuffer.Set();

	testMesh.Draw();
	sceneManager->Draw();
	testRenderTex.EndDraw();

	graphicsDevice.ClearRenderTargetOutDsv({ 135,206,235,0 });
	graphicsDevice.SetDescriptorHeap();

	//graphicsDevice.SetDescriptorHeap();
	//testTexShader->Set();
	mainCamera.Set();
	worldLightInfo.Set();
	testTexShader->Set();
	//worldLightInfo.Set();
	testCBuffer2.Set();
	graphicsDevice.GetCmdList()->SetGraphicsRootDescriptorTable(5, graphicsDevice.GetDescriptorHeapManager()->GetSRVHandleForGPU(1));
	testRenderTex.Set();
	testMesh.Draw();

	graphicsDevice.GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	testLineShader->Set();
	testCBuffer3.Set();
	testLineMesh.Draw();

	graphicsDevice.ScreenFlip();
}


