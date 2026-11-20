#pragma once

// 각종 include
#include<tchar.h>
#include<memory>
#include<ctime>
#include<cmath>
#include<functional>
#include<cassert>
#include<Windows.h>
#include<wincodec.h>  
#include<iostream>
using std::cout;
using std::endl;
using std::wstring;
using std::string;

// Types
#include "../Types/Types.h"

// DX11
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXMath.h>
#include "DirectXTex.h"
#include "DirectXTex.inl"
#include "SimpleMath.h"
using namespace DirectX;
using namespace Microsoft::WRL;
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

// 각종 define
#define PI 3.14159265f
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512
#define CHECK(p) assert(SUCCEEDED(p))

// 디버깅용 콘솔창
#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#pragma comment(lib, "DirectXTex_debug.lib")
#else
#pragma comment(lib, "DirectXTex.lib")
#endif