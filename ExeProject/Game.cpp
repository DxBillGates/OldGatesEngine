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

	auto* pointShader = graphicsDevice.GetShaderManager()->Add(new Shader(&graphicsDevice, std::wstring(L"Point")), "PointShader");
	pointShader->Create({ InputLayout::POSITION }, { RangeType::CBV,RangeType::CBV,RangeType::CBV,RangeType::SRV}, BlendMode::BLENDMODE_ALPHA, D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT, true);

	//板ポリ生成
	MeshData<VertexInfo::Vertex_UV_Normal> testMeshData;
	MeshCreater::CreateQuad({ 1,1 }, { 1,1 }, testMeshData);
	graphicsDevice.GetMeshManager()->Add("Plane")->Create(&graphicsDevice, testMeshData);

	//画面サイズ / 10 板ポリ生成
	MeshData<VertexInfo::Vertex_UV_Normal> testMeshData2;
	MeshCreater::CreateQuad({ 1920,1080 }, { 1,1 }, testMeshData2);
	graphicsDevice.GetMeshManager()->Add("ScreenPlane")->Create(&graphicsDevice, testMeshData2);

	MeshData<VertexInfo::Vertex_UV_Normal> testMeshData3;
	MeshCreater::Create2DQuad({ 1920,1080 }, { 1,1 }, testMeshData3);
	graphicsDevice.GetMeshManager()->Add("2DPlane")->Create(&graphicsDevice, testMeshData3);

	//グリッド生成
	MeshData<VertexInfo::Vertex_Color> testLineMeshData;
	MeshCreater::CreateGrid({ 10000,10000 }, 100, testLineMeshData);
	graphicsDevice.GetMeshManager()->Add("Grid")->Create(&graphicsDevice, testLineMeshData);

	//Cube生成
	MeshData<VertexInfo::Vertex_UV_Normal> testMeshData4;
	MeshCreater::CreateCube({ 50,50,50 }, testMeshData4);
	graphicsDevice.GetMeshManager()->Add("Cube")->Create(&graphicsDevice, testMeshData4);

	MeshData<VertexInfo::Vertex_UV_Normal> testMeshData5;
	MeshCreater::CreateSphere({ 50,50,50 },16,16, testMeshData5);
	graphicsDevice.GetMeshManager()->Add("Sphere")->Create(&graphicsDevice, testMeshData5);

	MeshData<VertexInfo::Vertex> testMeshData6;
	testMeshData6.GetVertices()->push_back({});
	testMeshData6.GetIndices()->push_back(0);
	graphicsDevice.GetMeshManager()->Add("Point")->Create(&graphicsDevice, testMeshData6);

	auto* g = gameObjectManager.Add(new GameObject());

	testRenderTex.Create(&graphicsDevice, { 1920,1080 });
	testRenderTex2.Create(&graphicsDevice, { 1920,1080 });
	testRenderTex3.Create(&graphicsDevice, { 1920,1080 });
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
	threshold = 0;
	return true;
}

bool Game::Update()
{
	gameObjectManager.Update();
	sceneManager->Update();
	return true;
}

void Game::Draw()
{
	graphicsDevice.GetCBufferAllocater()->ResetCurrentUseNumber();
	graphicsDevice.GetCBVSRVUAVHeap()->Set();

	//1パス目で普通に描画
	graphicsDevice.ClearRenderTarget({ 0,0,0,1 }, true, &testRenderTex);
	//Test用のGridや2D描画
	sceneManager->Draw();

	graphicsDevice.GetCBVSRVUAVHeap()->Set();
	//2パス目で輝度抽出
	graphicsDevice.ClearRenderTargetOutDsv({ 0,0,0,1 }, true, &testRenderTex4);
	graphicsDevice.GetShaderManager()->GetShader("BrightnessSamplingShader")->Set();
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Translate({ 1920 / 2,1080 / 2,0 }));
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(1, GatesEngine::Math::Matrix4x4::GetOrthographMatrix({ 1920,1080 }));
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, GatesEngine::Math::Vector4(threshold, 0, 0, 0));
	testRenderTex.Set(3);
	graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();

	//3パス目で横にブラー
	graphicsDevice.ClearRenderTargetOutDsv({ 0,0,0,1 }, true, &testRenderTex2);
	graphicsDevice.GetShaderManager()->GetShader("HGaussBlurShader")->Set();
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, testData);
	testRenderTex4.Set(3);
	graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();

	//4パス目で縦にブラー
	graphicsDevice.ClearRenderTargetOutDsv({ 0,0,0,1 }, true, &testRenderTex3);
	graphicsDevice.GetShaderManager()->GetShader("VGaussBlurShader")->Set();
	testRenderTex2.Set(3);
	graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();

	//3パス目で横にブラー
	graphicsDevice.ClearRenderTargetOutDsv({ 0,0,0,1 }, true, &testRenderTex2);
	graphicsDevice.GetShaderManager()->GetShader("HGaussBlurShader")->Set();
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, testData);
	testRenderTex3.Set(3);
	graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();

	//4パス目で縦にブラー
	graphicsDevice.ClearRenderTargetOutDsv({ 0,0,0,1 }, true, &testRenderTex3);
	graphicsDevice.GetShaderManager()->GetShader("VGaussBlurShader")->Set();
	testRenderTex2.Set(3);
	graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();

	//3パス目で横にブラー
	graphicsDevice.ClearRenderTargetOutDsv({ 0,0,0,1 }, true, &testRenderTex2);
	graphicsDevice.GetShaderManager()->GetShader("HGaussBlurShader")->Set();
	graphicsDevice.GetCBufferAllocater()->BindAndAttach(2, testData);
	testRenderTex3.Set(3);
	graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();

	//4パス目で縦にブラー
	graphicsDevice.ClearRenderTargetOutDsv({ 0,0,0,1 }, true, &testRenderTex3);
	graphicsDevice.GetShaderManager()->GetShader("VGaussBlurShader")->Set();
	testRenderTex2.Set(3);
	graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();

	//5パス目で4パス目の結果と1パス目の結果を合成
	graphicsDevice.ClearRenderTargetOutDsv({ 0,0,0,1 }, false);
	graphicsDevice.GetShaderManager()->GetShader("BloomShader")->Set();
	testRenderTex.Set(2);
	testRenderTex3.Set(3);
	graphicsDevice.GetMeshManager()->GetMesh("2DPlane")->Draw();


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


