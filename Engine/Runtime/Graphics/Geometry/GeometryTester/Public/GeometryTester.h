#pragma once
#include <vector>
#include "../../Vertex.h"

class GeometryTester
{
public:
	void TestGeometry(ID3D11Device* device, ID3D11Buffer** vertexBuffer, ID3D11Buffer** indexBuffer);
	int GetVertexCount()
	{
		return _vertices.size();
	}
	int GetIndicesCount()
	{
		return _indices.size();
	}
private:
	std::vector<Vertex> _vertices;
	std::vector<UINT> _indices;
};