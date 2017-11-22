#include "Background.h"



Background::Background()
{
}


Background::~Background()
{
}

Background* Background::instance = 0;

Background* Background::getInstance()
{
	if (!instance)
	{
		instance = new Background();
	}
	return instance;
}

void Background::Create(char* fileName, LPDIRECT3DDEVICE9 device)
{
	this->device = device;
	HRESULT hr;

	hr = D3DXGetImageInfoFromFile(fileName, &info);

	hr = device->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&sufface,
		NULL);

	hr = D3DXLoadSurfaceFromFile(
		sufface,
		NULL,
		NULL,
		fileName,
		NULL,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0),
		NULL);
}
