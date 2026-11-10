#include "GeometryTester.h"

void GeometryTester::TestGeometry(ID3D11Device* device, ID3D11Buffer** vertexBuffer)
{
	// Vertex data for a triangle
	{
		_vertices.resize(3);

		_vertices[0].position = Vector3D{ 0.0f, 1.0f, 0.0f };
		_vertices[0].color = Color{ 1.0f, 0.0f, 0.0f, 1.0f }; // Red

		_vertices[1].position = Vector3D{ 1.0f, -1.0f, 0.0f };
		_vertices[1].color = Color{ 0.0f, 1.0f, 0.0f, 1.0f }; // Green

		_vertices[2].position = Vector3D{ -1.0f, -1.0f, 0.0f };
		_vertices[2].color = Color{ 0.0f, 0.0f, 1.0f, 1.0f }; // Blue
	}

	// VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = sizeof(Vertex) * static_cast<UINT>(_vertices.size());

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = &_vertices[0];

		device->CreateBuffer(&desc, &data, vertexBuffer);
	}
}
