#include "SpriteGame.h"


SpriteGame::SpriteGame()
{
	sprite = NULL;
}

SpriteGame::~SpriteGame()
{
	if (sprite)
	{
		sprite->Release();
		sprite = NULL;
	}
}

SpriteGame* SpriteGame::instance = 0;

SpriteGame* SpriteGame::getInstance()
{
	if (!instance)
	{
		instance = new SpriteGame();
	}
	return instance;
}

bool SpriteGame::Init(LPDIRECT3DDEVICE9 device)
{
	if (!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
	{
		MessageBox(NULL, "Create Sprite Error!", NULL, MB_OK);
		return false;
	}
	return true;
}

void SpriteGame::Begin()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void SpriteGame::End()
{
	sprite->End();
}

void SpriteGame::Draw(TextureGame tex, RECT* rect, D3DXVECTOR3 position)
{
	if (sprite)
	{
		sprite->Draw(tex.texture, rect, NULL, &position, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void SpriteGame::ResetTranform()
{
	sprite->SetTransform(&matrix);
}

void SpriteGame::FlipX(int w, int h, D3DXVECTOR3 position)
{
	sprite->GetTransform(&matrix);
	D3DXMATRIX matrixFlip;
	//tao ma tran don vi
	D3DXMatrixIdentity(&matrixFlip);
	//lat quanh truc y
	matrixFlip._11 = -1;
	//di chuyen ve mot luong bang gap 2 khoang canh tu tam
	matrixFlip._41 = (position.x + w / 2) * 2;
	sprite->SetTransform(&( matrix * matrixFlip ));
}

void SpriteGame::FlipY(int w, int h, D3DXVECTOR3 position)
{
	sprite->GetTransform(&matrix);
	D3DXMATRIX matrixFlip;
	//tao ma tran don vi
	D3DXMatrixIdentity(&matrixFlip);
	//lat quanh truc y
	matrixFlip._22 = -1;
	//di chuyen ve mot luong bang gap 2 khoang canh tu tam
	matrixFlip._42 = (position.y + h / 2) * 2;
	sprite->SetTransform(&(matrix * matrixFlip));
}

