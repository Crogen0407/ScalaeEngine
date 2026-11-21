#pragma once

class State
{
	State(ComPtr<ID3D11Device> device) : _device(device) { }
	virtual ~State() = default;

protected:
	ComPtr<ID3D11Device> _device;
};