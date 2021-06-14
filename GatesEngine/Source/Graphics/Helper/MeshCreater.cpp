#include "..\..\..\Header\Graphics\Helper\MeshCreater.h"

void GatesEngine::MeshCreater::CreatePlane(Math::Vector2 size, Math::Vector2 uvMax, MeshData<VertexInfo::Vertex_UV_Normal>& meshData)
{
	std::vector<VertexInfo::Vertex_UV_Normal>* vertices = meshData.GetVertices();
	std::vector<unsigned short>* indices = meshData.GetIndices();

	using namespace Math;
	vertices->push_back({ Vector3(-size.x / 2.0f,0, size.y / 2.0f),Vector2(0,0),Vector3(0,1,0) });
	vertices->push_back({ Vector3(size.x / 2.0f,0, size.y / 2.0f),Vector2(uvMax.x,0),Vector3(0,1,0) });
	vertices->push_back({ Vector3(size.x / 2.0f,0,-size.y / 2.0f),Vector2(uvMax.x,uvMax.y),Vector3(0,1,0) });
	vertices->push_back({ Vector3(-size.x / 2.0f,0,-size.y / 2.0f),Vector2(0,uvMax.y),Vector3(0,1,0) });

	indices->push_back(0);
	indices->push_back(1);
	indices->push_back(2);
	indices->push_back(2);
	indices->push_back(3);
	indices->push_back(0);
}

void GatesEngine::MeshCreater::CreateQuad(Math::Vector2 size, Math::Vector2 uvMax, MeshData<VertexInfo::Vertex_UV_Normal>& meshData)
{
	std::vector<VertexInfo::Vertex_UV_Normal>* vertices = meshData.GetVertices();
	std::vector<unsigned short>* indices = meshData.GetIndices();

	using namespace Math;
	vertices->push_back({ Vector3(-size.x / 2.0f, size.y / 2.0f,0),Vector2(0,0),Vector3(0,0,-1) });
	vertices->push_back({ Vector3(size.x / 2.0f, size.y / 2.0f,0),Vector2(uvMax.x,0),Vector3(0,0,-1) });
	vertices->push_back({ Vector3(size.x / 2.0f,-size.y / 2.0f,0),Vector2(uvMax.x,uvMax.y),Vector3(0,0,0 - 1) });
	vertices->push_back({ Vector3(-size.x / 2.0f,-size.y / 2.0f,0),Vector2(0,uvMax.y),Vector3(0,0,-1) });

	indices->push_back(0);
	indices->push_back(1);
	indices->push_back(2);
	indices->push_back(2);
	indices->push_back(3);
	indices->push_back(0);
}

void GatesEngine::MeshCreater::CreateGrid(Math::Vector2 size, float spaceInterval, MeshData<VertexInfo::Vertex_Color>& meshData)
{
	int width = (int)(size.x / spaceInterval);
	int depth = (int)(size.y / spaceInterval);

	std::vector<VertexInfo::Vertex_Color>* vertices = meshData.GetVertices();
	std::vector<unsigned short>* indices = meshData.GetIndices();

	Math::Vector2 offset = Math::Vector2(-size.x / 2, -size.y / 2);
	Math::Vector2 maxOffset = size / 2;

	for (int w = 0; w <= width; ++w)
	{
		float x = w * spaceInterval;
		GatesEngine::Math::Vector4 color = { 1,1,1,0.8f };
		if (offset.x + x == 0)color = {0,0,1,1};
		vertices->push_back({ Math::Vector3(offset.x + x,0,offset.y),color });
		vertices->push_back({ Math::Vector3(offset.x + x,0,maxOffset.y),color });
	}

	for (int d = 0; d <= depth; ++d)
	{
		float z = d * spaceInterval;
		GatesEngine::Math::Vector4 color = { 1,1,1,0.8f };
		if (offset.y + z  == 0)color = { 1,0,0,1 };
		vertices->push_back({ Math::Vector3(offset.x,0   ,offset.y + z),color });
		vertices->push_back({ Math::Vector3(maxOffset.x,0,offset.y + z),color });
	}

	for (int i = 0; i < (int)vertices->size(); i += 2)
	{
		indices->push_back(i);
		indices->push_back(i + 1);
	}
}
