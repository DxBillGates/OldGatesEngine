#include "Game.h"
#include "SampleScene.h"
#include "Header/Graphics/Graphics.h"

Game::Game() :Application()
{
}

Game::Game(const GatesEngine::Math::Vector2& wSize, const char* title) : Application(wSize, title)
{
}

Game::~Game()
{
}

bool Game::LoadContents()
{
	sceneManager->AddScene(new SampleScene("SampleScene", this));
	sceneManager->ChangeScene("SampleScene");

	using namespace GatesEngine;
	using namespace GatesEngine::Math;

	auto* testTexShader = graphicsDevice.GetShaderManager()->Add(new Shader(&graphicsDevice, std::wstring(L"Texture")), "Texture");
	testTexShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD ,InputLayout::NORMAL }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::SRV,RangeType::SRV }, BlendMode::BLENDMODE_ALPHA, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, false);

	auto* testLineShader = graphicsDevice.GetShaderManager()->Add(new Shader(&graphicsDevice, std::wstring(L"Line")), "Line");
	testLineShader->Create({ InputLayout::POSITION,InputLayout::COLOR }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::SRV,RangeType::SRV }, BlendMode::BLENDMODE_ALPHA, D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, true);

	auto* defaultMeshShader = graphicsDevice.GetShaderManager()->Add(new Shader(&graphicsDevice, std::wstring(L"DefaultMesh")), "DefaultMeshShader");
	defaultMeshShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD ,InputLayout::NORMAL }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV });

	auto* defaultSpriteShader = graphicsDevice.GetShaderManager()->Add(new Shader(&graphicsDevice, std::wstring(L"DefaultSprite")), "DefaultSpriteShader");
	defaultSpriteShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD }, { RangeType::CBV,RangeType::CBV,RangeType::CBV });

	auto* testMultiRTVShader = graphicsDevice.GetShaderManager()->Add(new Shader(&graphicsDevice, std::wstring(L"TestMultiRTV")), "testMultiRTVShader");
	testMultiRTVShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD ,InputLayout::NORMAL }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::SRV }, BlendMode::BLENDMODE_ALPHA, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, false, 2);

	//�|������
	MeshData<VertexInfo::Vertex_UV_Normal> testMeshData;
	MeshCreater::CreateQuad({ 100,100 }, { 1,1 }, testMeshData);
	graphicsDevice.GetMeshManager()->Add("Plane")->Create(&graphicsDevice, testMeshData);

	//��ʃT�C�Y / 10 �|������
	MeshData<VertexInfo::Vertex_UV_Normal> testMeshData2;
	MeshCreater::CreateQuad({ 1920,1080 }, { 1,1 }, testMeshData2);
	graphicsDevice.GetMeshManager()->Add("ScreenPlane")->Create(&graphicsDevice, testMeshData2);

	MeshData<VertexInfo::Vertex_UV_Normal> testMeshData3;
	MeshCreater::Create2DQuad({ 1920,1080 }, { 1,1 }, testMeshData3);
	graphicsDevice.GetMeshManager()->Add("2DPlane")->Create(&graphicsDevice, testMeshData3);

	//�O���b�h����
	MeshData<VertexInfo::Vertex_Color> testLineMeshData;
	MeshCreater::CreateGrid({ 10000,10000 }, 100, testLineMeshData);
	graphicsDevice.GetMeshManager()->Add("Grid")->Create(&graphicsDevice, testLineMeshData);

	auto* g = gameObjectManager.Add(new GameObject());

	testRenderTex.Create(&graphicsDevice, { 1920,1080 });
	testRenderTex2.Create(&graphicsDevice, { 1920,1080 });
	testRenderTex3.Create(&graphicsDevice, { 1920,1080 });

	graphicsDevice.GetCBVSRVUAVHeap()->CreateSRV(graphicsDevice.GetDepthBuffer());

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
	angle += 1.0f * timer.GetElapsedTime();
	gameObjectManager.Update();
	sceneManager->Update();
	return true;
}

void Game::Draw()
{
	//RenderTexture�g���Ȃ��o�[�W����
	//graphicsDevice.ClearRenderTarget({ 1,1,1,1 },true, &testRenderTex);

	graphicsDevice.GetCBVSRVUAVHeap()->Set();
	//graphicsDevice.GetShaderManager()->GetShader("DefaultMeshShader")->Set();
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::RotationY(angle));
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, mainCamera.GetData());
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ GatesEngine::Math::Vector4(0,1,1,0).Normalize(),GatesEngine::Math::Vector4(1,0,0,1) });	
	//graphicsDevice.GetMeshManager()->GetMesh("Plane")->Draw();
	//testRenderTex.EndDraw();

	//graphicsDevice.ClearRenderTargetOutDsv({ 135,206,235,0 });

	//graphicsDevice.GetShaderManager()->GetShader("Texture")->Set();
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Translate({ -30,0,0 }));
	//graphicsDevice.GetCmdList()->SetGraphicsRootDescriptorTable(5, graphicsDevice.GetCBVSRVUAVHeap()->GetSRVHandleForSRV(1));
	//testRenderTex.Set();
	//graphicsDevice.GetMeshManager()->GetMesh("Plane")->Draw();

	//graphicsDevice.ClearRenderTargetOutDsv({ 135,206,235,0 },false);

	//graphicsDevice.GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	//graphicsDevice.GetShaderManager()->GetShader("Line")->Set();
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(0,GatesEngine::Math::Matrix4x4::Identity());
	//graphicsDevice.GetMeshManager()->GetMesh("Grid")->Draw();


	//RenderTexture�g��Ȃ��o�[�W����
	//graphicsDevice.ClearRenderTarget({ 135,206,235,0 });

	//graphicsDevice.GetShaderManager()->GetShader("Default")->Set();
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::RotationY(angle));
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, mainCamera.GetData());
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ GatesEngine::Math::Vector4(0,1,1,0).Normalize(),GatesEngine::Math::Vector4(1,0,0,1) });
	//graphicsDevice.GetMeshManager()->GetMesh("Plane")->Draw();

	//graphicsDevice.GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	//graphicsDevice.GetShaderManager()->GetShader("Line")->Set();
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Identity());
	//graphicsDevice.GetMeshManager()->GetMesh("Grid")->Draw();
	
	//Test�p��Grid��2D�`��
	sceneManager->Draw();

	//�o�b�N�o�b�t�@�ɉ�镽�ʂ�`��
	graphicsDevice.ClearRenderTarget({ 135,206,235,0 }, false);
	graphicsDevice.GetShaderManager()->GetShader("DefaultMeshShader")->Set();
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::RotationY(angle));
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, mainCamera.GetData());
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ GatesEngine::Math::Vector4(0,1,1,0).Normalize(),GatesEngine::Math::Vector4(1,0,0,1) });
	graphicsDevice.GetMeshManager()->GetMesh("Plane")->Draw();

	//1�p�X�ڂɂɉ�镽�ʂ�`��
	graphicsDevice.ClearRenderTarget({ 1,1,1,1 }, true, &testRenderTex);
	graphicsDevice.GetShaderManager()->GetShader("DefaultMeshShader")->Set();
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::RotationY(angle));
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, mainCamera.GetData());
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ GatesEngine::Math::Vector4(0,1,1,0).Normalize(),GatesEngine::Math::Vector4(1,0,0,1) });
	graphicsDevice.GetMeshManager()->GetMesh("Plane")->Draw();

	//2�p�X�ڂɕ`�悵�����ʂ��e�N�X�`�������ĐF���]�Ƃڂ����e�N�X�`����2�����o��
	graphicsDevice.SetMultiRenderTarget({ &testRenderTex2,&testRenderTex3 });
	graphicsDevice.GetShaderManager()->GetShader("testMultiRTVShader")->Set();
	testRenderTex.Set(4);
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Translate({1920/2,1080/2,0}));
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, GatesEngine::Math::Matrix4x4::GetOrthographMatrix({1920,1080}));
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ GatesEngine::Math::Vector4(0,1,1,0).Normalize(),GatesEngine::Math::Vector4(1,0,0,1) });
	graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();

	//�o�b�N�o�b�t�@�Ƀp�X�ڂŏo�͂���2���̃e�N�X�`����`��
	graphicsDevice.ClearRenderTarget({ 135,206,235,0 }, false);
	graphicsDevice.GetShaderManager()->GetShader("Texture")->Set();
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, mainCamera.GetData());

	testRenderTex2.Set(4);
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Translate({ -100, 0, 0 }));
	graphicsDevice.GetMeshManager()->GetMesh("Plane")->Draw();

	testRenderTex3.Set(4);
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Translate({  100, 0, 0 }));
	graphicsDevice.GetMeshManager()->GetMesh("Plane")->Draw();


	graphicsDevice.ScreenFlip();
}


