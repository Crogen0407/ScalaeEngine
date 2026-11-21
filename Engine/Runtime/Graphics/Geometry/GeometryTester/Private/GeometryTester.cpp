#include "GeometryTester.h"

void GeometryTester::TestGeometry(ComPtr<ID3D11Device> device, ComPtr<ID3DBlob> vsBlob)
{
	// Vertex data for a triangle
	{
		_vertices.resize(4);

		// 12
		// 03
		_vertices[0].position = { -0.5f, -0.5f, 0.0f };
		_vertices[0].color = { 1.0f, 0.0f, 0.0f, 1.0f }; // Red
		_vertices[0].uv = { 0.f, 1.f };

		_vertices[1].position = { -0.5f, 0.5f, 0.0f };
		_vertices[1].color = { 0.0f, 1.0f, 0.0f, 1.0f }; // Green
		_vertices[1].uv = { 0.f, 0.f };

		_vertices[2].position = { 0.5f, 0.5f, 0.0f };
		_vertices[2].color = { 0.0f, 0.0f, 1.0f, 1.0f }; // Blue
		_vertices[2].uv = { 1.f, 0.f };

		_vertices[3].position = { 0.5f, -0.5f, 0.0f };
		_vertices[3].color = { 1.0f, 1.0f, 1.0f, 1.0f }; // White
		_vertices[3].uv = { 1.f, 1.f };

		_indices = { 0, 1, 2, 0, 2, 3 };
	}

	_vertexBuffer = new ::VertexBuffer(device);
	_vertexBuffer->Create(_vertices);

	_indexBuffer = new ::IndexBuffer(device);
	_indexBuffer->Create(_indices);

	_inputLayout = new ::InputLayout(device);
	_inputLayout->Create(vsBlob);
}
