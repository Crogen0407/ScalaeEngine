#include "Engine.h"
#include "../Graphics/Modules/DirectX11/Public/DirectX11GraphicModule.h"

Engine::Engine(HWND hWnd)
{
	_targetGraphicModule = new DirectX11GraphicModule();
	_targetGraphicModule->Initialize(hWnd);
}

void Engine::GameLoop()
{
	Render();
	Update();
}

void Engine::Render()
{
	_targetGraphicModule->RenderBegin();
	_targetGraphicModule->RenderEnd();
}

void Engine::Update()
{
}
