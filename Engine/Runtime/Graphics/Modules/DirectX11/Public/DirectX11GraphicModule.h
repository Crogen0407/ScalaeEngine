#pragma once
#include "../../IGraphicModule.h"
class GeometryTester;
class DirectX11GraphicModule : public IGraphicModule
{
public:
	void Initialize(HWND hWnd) override;

public:
	void CeateDeviceAndSwapChain(HWND hWnd);
	void CreateRenderTargetView();
	void SetViewport();

public:
	void CreateGeometry();
	void CreateInputLayout();
	void CreateVS();
	void CreatePS();
	void LoadShaderFormFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);

public:
	void RenderBegin() override;
	void RenderEnd() override;

private:
	// DirectX 11 device and context
	ComPtr<ID3D11Device> _device			         = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext       = nullptr;
	ComPtr<IDXGISwapChain> _swapChain		         = nullptr;

	// RTV
	ComPtr<ID3D11RenderTargetView> _renderTargetView = nullptr;
	
	// Input layout
	ComPtr<ID3D11InputLayout> _inputLayout           = nullptr;

	// Misc
	D3D11_VIEWPORT _viewport = { 0 };

	// Geometry
	GeometryTester* _geometryTester;
	ComPtr<ID3D11Buffer> _vertexBuffer;
	ComPtr<ID3D11VertexShader> _vertexShader         = nullptr;
	ComPtr<ID3DBlob> _vsBlob                         = nullptr;
	ComPtr<ID3D11PixelShader> _pixelShader           = nullptr;
	ComPtr<ID3DBlob> _psBlob                         = nullptr;
};