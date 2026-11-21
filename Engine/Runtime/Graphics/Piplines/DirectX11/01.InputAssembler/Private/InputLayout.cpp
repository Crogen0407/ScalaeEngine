#include "InputLayout.h"

void InputLayout::Create(ComPtr<ID3DBlob> vsBlob)
{
	D3D11_INPUT_ELEMENT_DESC desc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	HRESULT hr;
	hr = _device->CreateInputLayout(desc, ARRAYSIZE(desc), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), _inputLayout.GetAddressOf());
	CHECK(hr);
}
