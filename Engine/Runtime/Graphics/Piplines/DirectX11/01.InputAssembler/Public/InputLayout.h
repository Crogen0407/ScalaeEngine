#pragma once

class InputLayout
{
public:
	InputLayout(ComPtr<ID3D11Device> device) : _device(device) { }

	void Create(ComPtr<ID3DBlob> vsBlob);

	ComPtr<ID3D11InputLayout> GetData() { return _inputLayout; }
private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11InputLayout> _inputLayout;
};