#ifndef _SPRITEGAME_H_
#define _SPRITEGAME_H_

#include <d3dx9.h>
#include "GraphicsGame.h"

#pragma once

class SpriteGame
{
private:
	static SpriteGame* instance;
	LPD3DXSPRITE sprite;
	D3DXMATRIX matrix;
public:
	bool Init(LPDIRECT3DDEVICE9);
	void Begin();
	void End();
	void Draw(LPDIRECT3DTEXTURE9 texture, RECT* rect, D3DXVECTOR3 center, D3DXVECTOR3 position,
		D3DXVECTOR2 scale,
		D3DXVECTOR2 scalingCenter,
		D3DXVECTOR2 translation = D3DXVECTOR2(0, 0));
	void ResetTranform();
	void FlipX(int width, int height, D3DXVECTOR3 position);
	void FlipY(int width, int height, D3DXVECTOR3 position);
	LPD3DXSPRITE getSrpite() { return sprite; }

	static SpriteGame* getInstance();

	SpriteGame();
	~SpriteGame();
};

#endif // !_SPRITEGAME_H_



