#ifndef _SPRITEGAME_H_
#define _SPRITEGAME_H_

#include <d3dx9.h>
#include "TextureGame.h"

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
	void Draw(TextureGame, RECT*, D3DXVECTOR3);
	void ResetTranform();
	void FlipX(int, int, D3DXVECTOR3);
	void FlipY(int, int, D3DXVECTOR3);

	static SpriteGame* getInstance();

	SpriteGame();
	~SpriteGame();
};

#endif // !_SPRITEGAME_H_



