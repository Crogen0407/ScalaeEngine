#include "GeometryTester.h"

void GeometryTester::TestGeometry(ID3D11Device* device, ID3D11Buffer** vertexBuffer, ID3D11Buffer** indexBuffer)
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

		HRESULT hr = device->CreateBuffer(&desc, &data, vertexBuffer);
		CHECK(hr);
	}

	// Index
	{
		_indices = { 0, 1, 2, 0, 2, 3 };
	}

	// IndexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = sizeof(UINT) * static_cast<UINT>(_indices.size());

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = &_indices[0];

		HRESULT hr = device->CreateBuffer(&desc, &data, indexBuffer);
		CHECK(hr);
	}	
}
