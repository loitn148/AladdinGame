#include "TextureGame.h"


TextureGame::TextureGame()
{
}

TextureGame::~TextureGame()
{
}

bool TextureGame::Init(LPDIRECT3DDEVICE9 device, std::string fileName, int width, int height)
{
	D3DXIMAGE_INFO info;
	HRESULT h = D3DXGetImageInfoFromFile(fileName.c_str(), &info);

	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(
		device, 
		fileName.c_str(), 
		width, 
		height, 
		D3DX_DEFAULT, 
		0, 
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT, 
		D3DX_DEFAULT, 
		0, 
		&info, 
		NULL, 
		&texture)))
	{
		MessageBox(NULL, "Create Texture Error!", "Error", MB_OK);
		return false;
	}
	initialized = true;
	return true;
}

bool TextureGame::isInit()
{
	return initialized;
}
