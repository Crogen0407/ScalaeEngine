#pragma once
#include <vector>
#include "../../Vertex.h"
#include "../../../Piplines/DirectX11/01.InputAssembler/Public/VertexBuffer.h"
#include "../../../Piplines/DirectX11/01.InputAssembler/Public/IndexBuffer.h"
#include "../../../Piplines/DirectX11/01.InputAssembler/Public/InputLayout.h"

class GeometryTester
{
public:
	void TestGeometry(ComPtr<ID3D11Device> device, ComPtr<ID3DBlob> vsBlob);
	int GetVertexCount()
	{
		return _vertices.size();
	}
	int GetIndicesCount()
	{
		return _indices.size();
	}

	ComPtr<ID3D11Buffer> GetVertexBuffer() { return _vertexBuffer->GetData(); }
	ComPtr<ID3D11Buffer> GetIndexBuffer() { return _indexBuffer->GetData(); }
	ComPtr<ID3D11InputLayout> GetInputLayout() { return _inputLayout->GetData(); }

private:
	VertexBuffer* _vertexBuffer;
	IndexBuffer* _indexBuffer;
	InputLayout* _inputLayout;

	std::vector<Vertex> _vertices;
	std::vector<UINT> _indices;
};