#include "GraphicsGame.h"


GraphicsGame::GraphicsGame()
{
}

GraphicsGame::~GraphicsGame()
{
}

GraphicsGame* GraphicsGame::instance = NULL;

GraphicsGame* GraphicsGame::getInstance()
{
	if (!GraphicsGame::instance)
	{
		GraphicsGame::instance = new GraphicsGame();
	}
	return GraphicsGame::instance;
}

LPDIRECT3DSURFACE9 GraphicsGame::GetBackBuffer()
{
	return this->backBuffer;
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
	d3dpp.BackBufferWidth = WND_WIDTH;
	d3dpp.BackBufferHeight = WND_HEIGHT;

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

	this->device->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f,
		0);

	this->device->GetBackBuffer(
		0,
		0,
		D3DBACKBUFFER_TYPE_MONO,
		&this->backBuffer);

	if (D3DXCreateSprite(this->device, &this->sprite) != D3D_OK)
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

LPDIRECT3DTEXTURE9 GraphicsGame::loadTexture(char * fileName, D3DCOLOR transcolor)
{
	LPDIRECT3DTEXTURE9 texture;
	D3DXIMAGE_INFO info;
	HRESULT hr;
	
	hr = D3DXGetImageInfoFromFile(fileName, &info);
	
	hr = D3DXCreateTextureFromFileEx(
		this->device,
		fileName,
		info.Width,
		info.Height,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&info,
		NULL,
		&texture);
	if (hr != D3D_OK) {
		MessageBox(NULL, "Create Texture Error!", "Error", MB_OK);
		return false;
	}
	return texture;
}

LPDIRECT3DSURFACE9 GraphicsGame::loadSurface(char * fileName, D3DCOLOR transcolor)
{
	LPDIRECT3DSURFACE9 surface;
	D3DXIMAGE_INFO info;
	if (D3DXGetImageInfoFromFile(fileName, &info))
		return NULL;

	this->device->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&surface,
		NULL);
	if (D3DXLoadSurfaceFromFile(
		surface,
		NULL,
		NULL,
		fileName,
		NULL,
		D3DX_FILTER_TRIANGLE,
		transcolor,
		&info) != D3D_OK)
	{
		return NULL;
	}
	return surface;
}

void GraphicsGame::DrawTexture(LPDIRECT3DTEXTURE9 texture, RECT rect, D3DXVECTOR3 center, 
	D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 scalingCenter , D3DXVECTOR2 translation)
{

	D3DXMATRIX oldMatrix;
	D3DXMATRIX	matrix;

	D3DXMatrixTransformation2D(
		&matrix,
		&scalingCenter,
		0,
		&scale,
		NULL,
		0,
		&translation);

	sprite->GetTransform(&oldMatrix);
	sprite->SetTransform(&matrix);

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	sprite->Draw(
		texture,
		&rect,
		&center,
		&position,
		D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();

	sprite->SetTransform(&oldMatrix);
}

void GraphicsGame::DrawSurface(LPDIRECT3DSURFACE9 surface, RECT * sRect, RECT * dRect)
{
	this->device->StretchRect(
		surface,
		sRect,
		this->backBuffer,
		dRect,
		D3DTEXF_NONE);
}

LPD3DXSPRITE GraphicsGame::getSprite()
{
	return this->sprite;
}
