#pragma once
#include "../../../../Geometry/Vertex.h"
#include <vector>

class VertexBuffer
{
public:
	VertexBuffer(ComPtr<ID3D11Device> device) : _device(device) {}

	template<typename T>
	void Create(const vector<T>& vertices)
	{
		Stride = sizeof(T);
		Count = static_cast<UINT>(vertices.size());

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = Stride * Count;

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = &vertices[0];

		HRESULT hr = _device->CreateBuffer(&desc, &data, _buffer.GetAddressOf());
		CHECK(hr);
	}

	ComPtr<ID3D11Buffer> GetData() { return _buffer; }

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11Buffer> _buffer;

public:
	ReadOnlyProperty<UINT, VertexBuffer> Stride;
	ReadOnlyProperty<UINT, VertexBuffer> Offset;
	ReadOnlyProperty<UINT, VertexBuffer> Count;
};