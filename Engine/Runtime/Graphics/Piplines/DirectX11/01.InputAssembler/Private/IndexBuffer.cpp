#include "IndexBuffer.h"

void IndexBuffer::Create(const vector<UINT>& indices)
{
	Stride = sizeof(UINT);
	Count = static_cast<UINT>(indices.size());

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = Stride * Count;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = &indices[0];

	HRESULT hr = _device->CreateBuffer(&desc, &data, _buffer.GetAddressOf());
	CHECK(hr);
}
