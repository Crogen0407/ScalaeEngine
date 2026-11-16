#include "DirectX11GraphicModule.h"
#include "../../../Geometry/GeometryTester/Public/GeometryTester.h"

void DirectX11GraphicModule::Initialize(HWND hWnd)
{
	CeateDeviceAndSwapChain(hWnd);
	CreateRenderTargetView();
	SetViewport();

	CreateGeometry();
	CreateVS();
	CreateInputLayout();
	CreatePS();

	CreateSRV();
	CreateConstantBuffer();
}

void DirectX11GraphicModule::CeateDeviceAndSwapChain(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC desc = {};
	ZeroMemory(&desc, sizeof(desc));
	{
		desc.BufferDesc.Width = SCREEN_WIDTH;
		desc.BufferDesc.Height = SCREEN_HEIGHT;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count = 1; // No multi-sampling
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1; // Double buffering
		desc.OutputWindow = hWnd;
		desc.Windowed = true; // Windowed mode
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	// Create device and swap chain
	HRESULT hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		_swapChain.GetAddressOf(),
		_device.GetAddressOf(),
		nullptr,
		_deviceContext.GetAddressOf()
	);

	CHECK(hr);
}

void DirectX11GraphicModule::CreateRenderTargetView()
{
	HRESULT hr;

	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
	CHECK(hr);

	hr = _device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTargetView.GetAddressOf());
	CHECK(hr);
}

void DirectX11GraphicModule::SetViewport()
{
	_viewport.TopLeftX = 0;
	_viewport.TopLeftY = 0;
	_viewport.Width = static_cast<float>(SCREEN_WIDTH);
	_viewport.Height = static_cast<float>(SCREEN_HEIGHT);
	_viewport.MinDepth = 0.0f;
	_viewport.MaxDepth = 1.0f;
}

void DirectX11GraphicModule::CreateGeometry()
{
	_geometryTester = new GeometryTester();
	_geometryTester->TestGeometry(_device.Get(), _vertexBuffer.GetAddressOf(), _indexBuffer.GetAddressOf());
}

void DirectX11GraphicModule::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC desc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	HRESULT hr;
	hr = _device->CreateInputLayout(desc, ARRAYSIZE(desc), _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), _inputLayout.GetAddressOf());
	CHECK(hr);
}

void DirectX11GraphicModule::CreateVS()
{
	LoadShaderFormFile(L"Default.hlsl", "VS", "vs_5_0", _vsBlob);
	HRESULT hr = _device->CreateVertexShader(_vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf());
	CHECK(hr);
}

void DirectX11GraphicModule::CreatePS()
{
	LoadShaderFormFile(L"Default.hlsl", "PS", "ps_5_0", _psBlob);
	HRESULT hr = _device->CreatePixelShader(_psBlob->GetBufferPointer(), _psBlob->GetBufferSize(), nullptr, _pixelShader.GetAddressOf());
	CHECK(hr);
}

void DirectX11GraphicModule::CreateSRV()
{
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	HRESULT hr = ::LoadFromWICFile(L"stellive.png", WIC_FLAGS_NONE, &md, img);
	CHECK(hr);

	hr = ::CreateShaderResourceView(_device.Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourceView.GetAddressOf());
	CHECK(hr);
}

void DirectX11GraphicModule::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(TransformData);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = _device->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());
	CHECK(hr);
}

void DirectX11GraphicModule::LoadShaderFormFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob)
{
	const UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	HRESULT hr = ::D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlags,
		0,
		blob.GetAddressOf(),
		nullptr
	);

	wchar_t cwd[MAX_PATH];
	::GetCurrentDirectoryW(MAX_PATH, cwd);
	::OutputDebugStringW((wstring(L"CWD: ") + cwd + L"\n").c_str());

	CHECK(hr);
}

void DirectX11GraphicModule::RenderBegin()
{
	// Clear the render target view
	const float clearColor[4] = { 0.0f, 0.2f, 0.4f, 1.0f }; // RGBA
	_deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);
	_deviceContext->ClearRenderTargetView(_renderTargetView.Get(), clearColor);
	_deviceContext->RSSetViewports(1, &_viewport);

	// IA
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
	_deviceContext->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	_deviceContext->IASetInputLayout(_inputLayout.Get());
	_deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// VS
	_deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
	_deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());

	// RS

	// PS
	_deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);
	_deviceContext->PSSetShaderResources(0, 1, _shaderResourceView.GetAddressOf());

	// OM

	//_deviceContext->Draw(_geometryTester->GetVertexCount(), 0);
	_deviceContext->DrawIndexed(_geometryTester->GetIndicesCount(), 0, 0);


	_transformData.offset.x += 0.0009f;
	_transformData.offset.y = 0.3f;

	D3D11_MAPPED_SUBRESOURCE subResource;
	ZeroMemory(&subResource, sizeof(subResource));

	_deviceContext->Map(_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	memcpy(subResource.pData, &_transformData, sizeof(_transformData));
	_deviceContext->Unmap(_constantBuffer.Get(), 0);
}

void DirectX11GraphicModule::RenderEnd()
{
	// Present the back buffer to the screen
	_swapChain->Present(1, 0); // VSync enabled
}