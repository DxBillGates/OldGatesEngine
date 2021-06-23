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

	auto* testVGaussBlurShader = graphicsDevice.GetShaderManager()->Add(new Shader(&graphicsDevice, std::wstring(L"VGaussBlur")), "VGaussBlurShader");
	testVGaussBlurShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::SRV }, BlendMode::BLENDMODE_ALPHA, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, false);

	auto* testHGaussBlurShader = graphicsDevice.GetShaderManager()->Add(new Shader(&graphicsDevice, std::wstring(L"HGaussBlur")), "HGaussBlurShader");
	testHGaussBlurShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::SRV }, BlendMode::BLENDMODE_ALPHA, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, false);

	auto* testDOFShader = graphicsDevice.GetShaderManager()->Add(new Shader(&graphicsDevice, std::wstring(L"DepthOfField")), "DepthOfFieldShader");
	testDOFShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD }, { RangeType::CBV,RangeType::CBV,RangeType::SRV,RangeType::SRV,RangeType::SRV,RangeType::CBV }, BlendMode::BLENDMODE_ALPHA, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, false);

	auto* testBrightnessSamplingShader = graphicsDevice.GetShaderManager()->Add(new Shader(&graphicsDevice, std::wstring(L"BrightnessSampling")), "BrightnessSamplingShader");
	testBrightnessSamplingShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::SRV}, BlendMode::BLENDMODE_ALPHA, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, false);

	auto* bloomShader = graphicsDevice.GetShaderManager()->Add(new Shader(&graphicsDevice, std::wstring(L"Bloom")), "BloomShader");
	bloomShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD }, { RangeType::CBV,RangeType::CBV,RangeType::SRV,RangeType::SRV }, BlendMode::BLENDMODE_ALPHA, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, false);

	auto* rgbShiftShader = graphicsDevice.GetShaderManager()->Add(new Shader(&graphicsDevice, std::wstring(L"RGBShift")), "RGBShiftShader");
	rgbShiftShader->Create({ InputLayout::POSITION,InputLayout::TEXCOORD }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::SRV}, BlendMode::BLENDMODE_ALPHA, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, false);
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

	//Cube����
	MeshData<VertexInfo::Vertex_UV_Normal> testMeshData4;
	MeshCreater::CreateCube({ 50,50,50 }, testMeshData4);
	graphicsDevice.GetMeshManager()->Add("Cube")->Create(&graphicsDevice, testMeshData4);

	MeshData<VertexInfo::Vertex_UV_Normal> testMeshData5;
	MeshCreater::CreateSphere({ 50,50,50 },16,16, testMeshData5);
	graphicsDevice.GetMeshManager()->Add("Sphere")->Create(&graphicsDevice, testMeshData5);

	auto* g = gameObjectManager.Add(new GameObject());

	testRenderTex.Create(&graphicsDevice, { 1920,1080 });
	testRenderTex2.Create(&graphicsDevice, { 1920,1080 });
	testRenderTex3.Create(&graphicsDevice, { 1920,1080 });

	graphicsDevice.GetCBVSRVUAVHeap()->CreateSRV(graphicsDevice.GetDepthBuffer());

	testDepthTex.Create(&graphicsDevice, { 1920,1080 });
	testRenderTex4.Create(&graphicsDevice, { 1920,1080 });

	return true;
}

bool Game::Initialize()
{
	gameObjectManager.Start();
	timer.SetFrameRate(144);
	timer.SetIsShow(true);
	gaussData = GetGaussData(8, 5.0f);
	for (int i = 0; i < 8; ++i)
	{
		testData.data[i] = gaussData[i];
	}
	effectFlag = Effects::DOF;
	threshold = 1;
	return true;
}

bool Game::Update()
{
	//�|�X�g�G�t�F�N�g�̕ύX
	if (input->GetKeyboard()->CheckPressTrigger(GatesEngine::Keys::D1))
	{
		effectFlag = Effects::DOF;
		threshold = 1;
	}
	if (input->GetKeyboard()->CheckPressTrigger(GatesEngine::Keys::D2))
	{
		effectFlag = Effects::BLOOM;
		threshold = 1;
	}
	if (input->GetKeyboard()->CheckPressTrigger(GatesEngine::Keys::D3))
	{
		effectFlag = Effects::RGBSHIFT;
		threshold = 1;
	}

	//�V�F�[�_�[�ɑ���l��ύX
	if (input->GetKeyboard()->CheckHitKey(GatesEngine::Keys::UP))
	{
		switch (effectFlag)
		{
		case Effects::DOF:
			threshold += 0.0001f;
			break;
		case Effects::BLOOM:
			threshold += 0.001f;
			break;
		case Effects::RGBSHIFT:
			threshold += 0.0005f;
			break;
		}

		if (threshold > 1)
		{
			threshold = 1;
		}
	}
	if (input->GetKeyboard()->CheckHitKey(GatesEngine::Keys::DOWN))
	{
		switch (effectFlag)
		{
		case Effects::DOF:
			threshold -= 0.0001f;
			break;
		case Effects::BLOOM:
			threshold -= 0.001f;
			break;
		case Effects::RGBSHIFT:
			threshold -= 0.0005f;
			break;
		}

		if (threshold < 0)
		{
			threshold = 0;
		}
	}
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

	////�o�b�N�o�b�t�@�ɉ�镽�ʂ�`��
	//graphicsDevice.ClearRenderTarget({ 135,206,235,0 }, false);
	//graphicsDevice.GetShaderManager()->GetShader("DefaultMeshShader")->Set();
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::RotationY(angle));
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, mainCamera.GetData());
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ GatesEngine::Math::Vector4(0,1,1,0).Normalize(),GatesEngine::Math::Vector4(1,0,0,1) });
	//graphicsDevice.GetMeshManager()->GetMesh("Plane")->Draw();

	////1�p�X�ڂɂɉ�镽�ʂ�`��
	//graphicsDevice.ClearRenderTarget({ 1,1,1,1 }, true, &testRenderTex);
	//graphicsDevice.GetShaderManager()->GetShader("DefaultMeshShader")->Set();
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::RotationY(angle));
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, mainCamera.GetData());
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ GatesEngine::Math::Vector4(0,1,1,0).Normalize(),GatesEngine::Math::Vector4(1,0,0,1) });
	//graphicsDevice.GetMeshManager()->GetMesh("Plane")->Draw();

	////2�p�X�ڂɕ`�悵�����ʂ��e�N�X�`�������ĐF���]�Ƃڂ����e�N�X�`����2�����o��
	//graphicsDevice.SetMultiRenderTarget({ &testRenderTex2,&testRenderTex3 });
	//graphicsDevice.GetShaderManager()->GetShader("testMultiRTVShader")->Set();
	//testRenderTex.Set(4);
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Translate({1920/2,1080/2,0}));
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, GatesEngine::Math::Matrix4x4::GetOrthographMatrix({1920,1080}));
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ GatesEngine::Math::Vector4(0,1,1,0).Normalize(),GatesEngine::Math::Vector4(1,0,0,1) });
	//graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();

	////�o�b�N�o�b�t�@��2�p�X�ڂŏo�͂���2���̃e�N�X�`����`��
	//graphicsDevice.ClearRenderTarget({ 135,206,235,0 }, false);
	//graphicsDevice.GetShaderManager()->GetShader("Texture")->Set();
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, mainCamera.GetData());

	//testRenderTex2.Set(4);
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Translate({ -100, 0, 0 }));
	//graphicsDevice.GetMeshManager()->GetMesh("Plane")->Draw();

	//testRenderTex3.Set(4);
	//graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Translate({  100, 0, 0 }));
	//graphicsDevice.GetMeshManager()->GetMesh("Plane")->Draw();


	switch (effectFlag)
	{
	//��ʊE�[�x
	case Effects::DOF:
		//1�p�X�ڂŕ��ʂɕ`��
		graphicsDevice.ClearRenderTarget({ 0,0,0,1 }, true, &testRenderTex, &testDepthTex);


		graphicsDevice.GetShaderManager()->GetShader("DefaultMeshShader")->Set(false);
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::RotationY(angle) * GatesEngine::Math::Matrix4x4::RotationX(angle));
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, mainCamera.GetData());
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ GatesEngine::Math::Vector4(0,0,1,0).Normalize(),GatesEngine::Math::Vector4(0,1,1,1) });
		graphicsDevice.GetMeshManager()->GetMesh("Cube")->Draw();

		graphicsDevice.GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		for (int i = 0; i < 10; ++i)
		{
			graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Scale({ 10,10,10 }) * GatesEngine::Math::Matrix4x4::RotationY(0 * i * 0.1f) * GatesEngine::Math::Matrix4x4::RotationX(0) * GatesEngine::Math::Matrix4x4::Translate({ 50 * (float)i,100,100 * (float)i }));
			graphicsDevice.GetMeshManager()->GetMesh("Sphere")->Draw();
		}
		//�O���b�h�`��
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(2,mainCamera.GetData());
		graphicsDevice.GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		graphicsDevice.GetShaderManager()->GetShader("Line")->Set();
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Identity());
		graphicsDevice.GetMeshManager()->GetMesh("Grid")->Draw();

		//2�p�X�ڂŉ��Ƀu���[
		graphicsDevice.ClearRenderTargetOutDsv({ 0,0,0,1 }, true, &testRenderTex2);
		graphicsDevice.GetShaderManager()->GetShader("HGaussBlurShader")->Set();
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Translate({ 1920 / 2,1080 / 2,0 }));
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(1, GatesEngine::Math::Matrix4x4::GetOrthographMatrix({ 1920,1080 }));
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, testData);
		testRenderTex.Set(3);
		graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();

		//3�p�X�ڂŏc�Ƀu���[
		graphicsDevice.ClearRenderTargetOutDsv({ 0,0,0,1 }, true, &testRenderTex3);
		graphicsDevice.GetShaderManager()->GetShader("VGaussBlurShader")->Set();
		testRenderTex2.Set(3);
		graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();

		//4�p�X�ڂŃu���[�e�N�X�`���ƒʏ�`�悵�����ʂ�[�x�e�N�X�`���̏����Q�Ƃ���Lerp�������ʂ�`��
		graphicsDevice.ClearRenderTargetOutDsv({ 135,206,235,0 }, false);
		graphicsDevice.GetShaderManager()->GetShader("DepthOfFieldShader")->Set();
		testRenderTex.Set(2);
		testRenderTex3.Set(3);
		//graphicsDevice.GetCmdList()->SetGraphicsRootDescriptorTable(4, graphicsDevice.GetCBVSRVUAVHeap()->GetSRVHandleForSRV(3));
		testDepthTex.Set(4);
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(5,GatesEngine::Math::Vector4(threshold,0,0,0));
		graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();
		break;
	//Bloom
	case Effects::BLOOM:
		//1�p�X�ڂŕ��ʂɕ`��
		graphicsDevice.ClearRenderTarget({ 0,0,0,1 }, true, &testRenderTex, &testDepthTex);
		graphicsDevice.GetShaderManager()->GetShader("DefaultMeshShader")->Set(false);
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::RotationY(angle) * GatesEngine::Math::Matrix4x4::RotationX(angle));
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, mainCamera.GetData());
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ GatesEngine::Math::Vector4(0,0,1,0).Normalize(),GatesEngine::Math::Vector4(0,1,1,1) });
		graphicsDevice.GetMeshManager()->GetMesh("Cube")->Draw();

		for (int i = 0; i < 10; ++i)
		{
			graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Scale({10,10,10}) * GatesEngine::Math::Matrix4x4::RotationY(angle * i * 0.1f) * GatesEngine::Math::Matrix4x4::RotationX(angle) * GatesEngine::Math::Matrix4x4::Translate({ 50 * (float)i,100,100 * (float)i }));
			graphicsDevice.GetMeshManager()->GetMesh("Sphere")->Draw();
		}

		//�O���b�h�`��
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, mainCamera.GetData());
		graphicsDevice.GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		graphicsDevice.GetShaderManager()->GetShader("Line")->Set();
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Identity());
		graphicsDevice.GetMeshManager()->GetMesh("Grid")->Draw();

		//2�p�X�ڂŋP�x���o
		graphicsDevice.ClearRenderTargetOutDsv({ 0,0,0,1 }, true, &testRenderTex4);
		graphicsDevice.GetShaderManager()->GetShader("BrightnessSamplingShader")->Set();
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Translate({ 1920 / 2,1080 / 2,0 }));
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(1, GatesEngine::Math::Matrix4x4::GetOrthographMatrix({ 1920,1080 }));
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, GatesEngine::Math::Vector4(threshold, 0, 0, 0));
		testRenderTex.Set(3);
		graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();

		//3�p�X�ڂŉ��Ƀu���[
		graphicsDevice.ClearRenderTargetOutDsv({ 0,0,0,1 }, true, &testRenderTex2);
		graphicsDevice.GetShaderManager()->GetShader("HGaussBlurShader")->Set();
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, testData);
		testRenderTex4.Set(3);
		graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();

		//4�p�X�ڂŏc�Ƀu���[
		graphicsDevice.ClearRenderTargetOutDsv({ 0,0,0,1 }, true, &testRenderTex3);
		graphicsDevice.GetShaderManager()->GetShader("VGaussBlurShader")->Set();
		testRenderTex2.Set(3);
		graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();

		//5�p�X�ڂ�4�p�X�ڂ̌��ʂ�1�p�X�ڂ̌��ʂ�����
		graphicsDevice.ClearRenderTargetOutDsv({ 0,0,0,1 }, false);
		graphicsDevice.GetShaderManager()->GetShader("BloomShader")->Set();
		testRenderTex.Set(2);
		testRenderTex3.Set(3);
		graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();
		break;
	//RGBShift
	case Effects::RGBSHIFT:
		//1�p�X�ڂŕ��ʂɕ`��
		graphicsDevice.ClearRenderTarget({ 0,0,0,1 }, true, &testRenderTex, &testDepthTex);
		graphicsDevice.GetShaderManager()->GetShader("DefaultMeshShader")->Set(false);
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::RotationY(angle) * GatesEngine::Math::Matrix4x4::RotationX(angle));
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, mainCamera.GetData());
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(3, GatesEngine::B3{ GatesEngine::Math::Vector4(0,0,1,0).Normalize(),GatesEngine::Math::Vector4(1,1,1,1) });
		graphicsDevice.GetMeshManager()->GetMesh("Cube")->Draw();

		for (int i = 0; i < 10; ++i)
		{
			graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::RotationY(angle * i * 0.1f) * GatesEngine::Math::Matrix4x4::RotationX(angle) * GatesEngine::Math::Matrix4x4::Translate({ 50 * (float)i,100,100 * (float)i }));
			graphicsDevice.GetMeshManager()->GetMesh("Sphere")->Draw();
		}

		//�O���b�h�`��
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, mainCamera.GetData());
		graphicsDevice.GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		graphicsDevice.GetShaderManager()->GetShader("Line")->Set();
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Identity());
		graphicsDevice.GetMeshManager()->GetMesh("Grid")->Draw();

		//2�p�X�ڂŕ`�挋�ʂ����炵�ĕ`��
		graphicsDevice.ClearRenderTargetOutDsv({ 0,0,0,1 }, false);
		graphicsDevice.GetShaderManager()->GetShader("RGBShiftShader")->Set();
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Translate({ 1920 / 2,1080 / 2,0 }));
		graphicsDevice.GetCBufferAllocater()->BindAndAttach(1, GatesEngine::Math::Matrix4x4::GetOrthographMatrix({ 1920,1080 }));

		//float range = 0.05f;
		//float shift = (float)std::rand() / RAND_MAX * range - range / 2.0f;
		float shift = 0.004f;

		graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, GatesEngine::Math::Vector4(threshold, 0, 0, 0));
		testRenderTex.Set(3);
		graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();
		break;
	}



	//graphicsDevice.ClearRenderTargetOutDsv({ 135,206,235,0 }, false);
	//graphicsDevice.GetShaderManager()->GetShader("DepthOfFieldShader")->Set();
	//testRenderTex.Set(2);
	//testRenderTex3.Set(3);
	////graphicsDevice.GetCmdList()->SetGraphicsRootDescriptorTable(4, graphicsDevice.GetCBVSRVUAVHeap()->GetSRVHandleForSRV(3));
	//testDepthTex.Set(4);
	//graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();


	graphicsDevice.ScreenFlip();
}

std::vector<float> Game::GetGaussData(size_t count, float s)
{
	std::vector<float> weights(count);
	float x = 0.0f;
	float total = 0.0f;
	for (auto& wgt : weights) 
	{
		wgt = expf(-(x * x) / (2 * s * s));
		total += wgt;
		x += 1.0f;
	}

	total = total * 2.0f - 1.0f;
	
	for (auto& wgt : weights) 
	{
		wgt /= total;
	}
	return weights;
}


