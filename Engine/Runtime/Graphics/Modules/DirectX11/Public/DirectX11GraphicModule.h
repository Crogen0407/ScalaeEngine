#pragma once
#include "../../IGraphicModule.h"
#include "../../../Geometry/Vertex.h"
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
	void CreateInputLayout( );
	void CreateVS();
	void CreatePS();

	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateSRV();
	void CreateConstantBuffer();

	void LoadShaderFormFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);

public:
	void RenderBegin() override;
	void RenderEnd() override;

private:
	// DirectX 11 device and context
	ComPtr<ID3D11Device> _device						 = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext			 = nullptr;
	ComPtr<IDXGISwapChain> _swapChain					 = nullptr;

	// RTV
	ComPtr<ID3D11RenderTargetView> _renderTargetView	 = nullptr;
	
	// Misc
	D3D11_VIEWPORT _viewport = { 0 };

	// Geometry
	GeometryTester* _geometryTester;
	ComPtr<ID3D11Buffer> _vertexBuffer					 = nullptr;
	ComPtr<ID3D11Buffer> _indexBuffer					 = nullptr;
														 
	ComPtr<ID3D11VertexShader> _vertexShader			 = nullptr;
	ComPtr<ID3DBlob> _vsBlob							 = nullptr;
	ComPtr<ID3D11PixelShader> _pixelShader				 = nullptr;
	ComPtr<ID3DBlob> _psBlob							 = nullptr;
														 
	// Input layout										 
	ComPtr<ID3D11InputLayout> _inputLayout				 = nullptr;
														 
	// RS												 
	ComPtr<ID3D11RasterizerState> _rasterizerState		 = nullptr;

	// SRV
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;

	ComPtr<ID3D11SamplerState> _samplerState		     = nullptr;
	ComPtr<ID3D11BlendState> _blendState				 = nullptr;

	TransformData _transformData;
	ComPtr<ID3D11Buffer> _constantBuffer				 = nullptr;
};