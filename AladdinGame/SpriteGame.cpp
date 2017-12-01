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

SpriteGame* SpriteGame::instance = NULL;

SpriteGame* SpriteGame::getInstance()
{
	if (!SpriteGame::instance)
	{
		SpriteGame::instance = new SpriteGame();
	}
	return SpriteGame::instance;
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


void SpriteGame::Draw(LPDIRECT3DTEXTURE9 texture, RECT* rect, D3DXVECTOR3 center, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 scalingCenter, D3DXVECTOR2 translation)
{
	GraphicsGame::getInstance()->DrawTexture(texture, *rect, center, position, scale, scalingCenter, translation);
}


void SpriteGame::ResetTranform()
{
	sprite->SetTransform(&matrix);
}

void SpriteGame::FlipX(int width, int height, D3DXVECTOR3 position)
{
	sprite->GetTransform(&matrix);
	D3DXMATRIX matrixFlip;
	//tao ma tran don vi
	D3DXMatrixIdentity(&matrixFlip);
	//lat quanh truc y
	matrixFlip._11 = -1;
	//di chuyen ve mot luong bang gap 2 khoang canh tu tam
	matrixFlip._41 = (position.x + width / 2) * 2;
	sprite->SetTransform(&( matrix * matrixFlip ));
}

void SpriteGame::FlipY(int width, int height, D3DXVECTOR3 position)
{
	sprite->GetTransform(&matrix);
	D3DXMATRIX matrixFlip;
	//tao ma tran don vi
	D3DXMatrixIdentity(&matrixFlip);
	//lat quanh truc y
	matrixFlip._22 = -1;
	//di chuyen ve mot luong bang gap 2 khoang canh tu tam
	matrixFlip._42 = (position.y + height / 2) * 2;
	sprite->SetTransform(&(matrix * matrixFlip));
}

