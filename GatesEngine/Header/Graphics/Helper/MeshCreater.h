#pragma once
#include "..\MeshData.h"
#include "..\VertexInfo.h"

namespace GatesEngine
{
	namespace MeshCreater
	{
		void CreatePlane(Math::Vector2 size, Math::Vector2 uvMax, MeshData<VertexInfo::Vertex_UV_Normal>& meshData);
		void CreateQuad(Math::Vector2 size, Math::Vector2 uvMax, MeshData<VertexInfo::Vertex_UV_Normal>& meshData);
		void CreateGrid(Math::Vector2 size, float spaceInterval, MeshData<VertexInfo::Vertex_Color>& meshData);
	}
}