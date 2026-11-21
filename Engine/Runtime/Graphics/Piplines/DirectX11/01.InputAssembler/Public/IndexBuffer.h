#pragma once

class IndexBuffer
{
public:
	IndexBuffer(ComPtr<ID3D11Device> device) : _device(device) { }

	void Create(const vector<UINT>& indices);

	ComPtr<ID3D11Buffer> GetData() { return _buffer; }

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11Buffer> _buffer;

public:
	ReadOnlyProperty<UINT, IndexBuffer> Stride;
	ReadOnlyProperty<UINT, IndexBuffer> Offset;
	ReadOnlyProperty<UINT, IndexBuffer> Count;
};