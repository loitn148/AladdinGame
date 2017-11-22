#include "GraphicsGame.h"


GraphicsGame::GraphicsGame()
{
}

GraphicsGame::~GraphicsGame()
{
}

GraphicsGame* GraphicsGame::instance = 0;

GraphicsGame* GraphicsGame::getInstance()
{
	if (!instance)
	{
		instance = new GraphicsGame();
	}
	return instance;
}

bool GraphicsGame::Init(HWND hWnd, bool isWindowed)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = isWindowed;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = 600;
	d3dpp.BackBufferHeight = 450;

	if(!SUCCEEDED(d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&device )))
	{ 
		return false;
	}
	return true;
}

void GraphicsGame::Clear(DWORD color)
{
	device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void GraphicsGame::Begin()
{
	device->BeginScene();
}

void GraphicsGame::End()
{
	device->EndScene();
}

void GraphicsGame::Present()
{
	device->Present(NULL, NULL, NULL, NULL);
}