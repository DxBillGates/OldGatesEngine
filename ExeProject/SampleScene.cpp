#include "SampleScene.h"
#include "Header/Application/Application.h"
#include "Header/Graphics/Graphics.h"
#include "Header/Math/Math.h"
#include <stdio.h>
#include <d3dcompiler.h>

SampleScene::SampleScene() :Scene()
{
}

SampleScene::SampleScene(const char* sceneName) : Scene(sceneName)
{
}

SampleScene::SampleScene(const char* sceneName, GatesEngine::Application* app) : Scene(sceneName, app)
{
	test.resize(10000);
	posDatas.resize(10000);

	//ルートシグネチャの生成
	rootSignature = new GatesEngine::RootSignature(graphicsDevice, { GatesEngine::RangeType::UAV });
	rootSignature->Create();

	//CSのコンパイル＆生成
	auto hr = D3DCompileFromFile(L"Resources/Shader/testCS.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "cs_5_1", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &shaderBlob, nullptr);

	D3D12_COMPUTE_PIPELINE_STATE_DESC pipeDesc = {};
	pipeDesc.CS.pShaderBytecode = shaderBlob->GetBufferPointer();
	pipeDesc.CS.BytecodeLength = shaderBlob->GetBufferSize();
	pipeDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	pipeDesc.NodeMask = 0;
	pipeDesc.pRootSignature = rootSignature->Get();

	hr = graphicsDevice->GetDevice()->CreateComputePipelineState(&pipeDesc, IID_PPV_ARGS(&pipeline));

	//リソースの生成
	D3D12_HEAP_PROPERTIES heapProp = {};
	heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heapProp.CreationNodeMask = 1;
	heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapProp.VisibleNodeMask = 0;

	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Alignment = 0;
	resDesc.DepthOrArraySize = 1;
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
	resDesc.Format = DXGI_FORMAT_UNKNOWN;
	resDesc.Height = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc = { 1,0 };
	resDesc.Width = (sizeof(UAVData) * (int)test.size() + 0xff) & ~0xff;

	hr = graphicsDevice->GetDevice()->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_UNORDERED_ACCESS, nullptr, IID_PPV_ARGS(&buffer));

	//ポジションデータ格納用バッファ生成
	resDesc.Flags = {};
	resDesc.Format = DXGI_FORMAT_UNKNOWN;
	resDesc.Width = sizeof(GatesEngine::Math::Vector4) * (UINT)test.size();

	hr = graphicsDevice->GetDevice()->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&posBuffer));

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	srvDesc.Buffer.FirstElement = 0;
	srvDesc.Buffer.NumElements = (UINT)test.size();
	srvDesc.Buffer.StructureByteStride = sizeof(GatesEngine::Math::Vector4);
	srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;

	srvNum = graphicsDevice->GetCBVSRVUAVHeap()->GetNextSrvNumber();
	graphicsDevice->GetCBVSRVUAVHeap()->CreateSRV(posBuffer, srvDesc);

	//ヒープの生成
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	heapDesc.NodeMask = 0;
	heapDesc.NumDescriptors = 1;
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

	hr = graphicsDevice->GetDevice()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&heap));

	//ビューの生成
	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
	uavDesc.ViewDimension = D3D12_UAV_DIMENSION::D3D12_UAV_DIMENSION_BUFFER;
	uavDesc.Format = DXGI_FORMAT_UNKNOWN;
	uavDesc.Buffer.NumElements = (UINT)test.size();
	uavDesc.Buffer.StructureByteStride = sizeof(UAVData);

	graphicsDevice->GetDevice()->CreateUnorderedAccessView(buffer, nullptr, &uavDesc, heap->GetCPUDescriptorHandleForHeapStart());

	hr = buffer->Map(0, nullptr, &data);
	hr = posBuffer->Map(0, nullptr,(void**)&posData);
}

SampleScene::~SampleScene()
{
	delete rootSignature;
	COM_RELEASE(pipeline);
	COM_RELEASE(heap);
	buffer->Unmap(0, nullptr);
	COM_RELEASE(buffer);
	COM_RELEASE(shaderBlob);
	COM_RELEASE(posBuffer);
}

void SampleScene::Initialize()
{
}

void SampleScene::Update()
{
	for (int i = 0; i < (UINT)test.size(); ++i)
	{
		posData[i] = test[i].pos;
	}
}

void SampleScene::Draw()
{
	test.assign((UAVData*)data, (UAVData*)data + (UINT)test.size());
	posDatas.assign((GatesEngine::Math::Vector4*)posData, (GatesEngine::Math::Vector4*)posData + (UINT)posDatas.size());

	using namespace GatesEngine::Math;

	graphicsDevice->GetCBufferAllocater()->ResetCurrentUseNumber();
	//graphicsDevice->ClearRenderTarget({ 135,206,235,0 });
	graphicsDevice->ClearRenderTarget({ 0,0,0,0 });

	//グリッド描画
	graphicsDevice->GetShaderManager()->GetShader("Line")->Set();
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(2, app->GetMainCamera()->GetData());
	graphicsDevice->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Identity());
	graphicsDevice->GetMeshManager()->GetMesh("Grid")->Draw();

	graphicsDevice->GetShaderManager()->GetShader("PointShader")->Set();
	graphicsDevice->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(0, GatesEngine::Math::Matrix4x4::Translate({0,0,0}));
	graphicsDevice->GetCBufferAllocater()->BindAndAttach(2, app->GetMainCamera()->GetData());
	graphicsDevice->GetCmdList()->SetGraphicsRootDescriptorTable(3, graphicsDevice->GetCBVSRVUAVHeap()->GetSRVHandleForSRV(srvNum));
	graphicsDevice->GetMeshManager()->GetMesh("Cube")->Draw((UINT)test.size());

	ID3D12GraphicsCommandList* list = graphicsDevice->GetCmdList();
	list->SetComputeRootSignature(rootSignature->Get());
	list->SetPipelineState(pipeline);
	list->SetDescriptorHeaps(1, &heap);

	auto handle = heap->GetGPUDescriptorHandleForHeapStart();
	list->SetComputeRootDescriptorTable(0, handle);

	list->Dispatch((UINT)test.size(), 1, 1);

	//graphicsDevice->ScreenFlip();

}
