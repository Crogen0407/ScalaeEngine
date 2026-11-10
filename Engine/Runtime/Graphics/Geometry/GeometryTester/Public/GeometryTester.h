#pragma once
#include <vector>
#include "../../Vertex.h"

class GeometryTester
{
public:
	void TestGeometry(ID3D11Device* device, ID3D11Buffer** vertexBuffer);
	int GetVertexCount()
	{
		return _vertices.size();
	}
private:
	std::vector<Vertex> _vertices;
};