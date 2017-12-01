#ifndef _GRAPHICSGAME_H_
#define _GRAPHICSGAME_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Global.h"

#pragma once
class GraphicsGame
{
private:
	LPDIRECT3D9 d3d;
	static GraphicsGame* instance;
	LPD3DXSPRITE sprite;
	LPDIRECT3DSURFACE9 backBuffer;
public:
	LPDIRECT3DDEVICE9 device;
	bool Init(HWND, bool); 
	void Clear(DWORD);
	void Begin();
	void End();
	void Present();

	LPDIRECT3DTEXTURE9 loadTexture(char* fileName, D3DCOLOR transcolor = D3DCOLOR_XRGB(0, 0, 0));
	LPDIRECT3DSURFACE9 loadSurface(char* fileName, D3DCOLOR transcolor = D3DCOLOR_XRGB(0, 0, 0));

	void DrawTexture(LPDIRECT3DTEXTURE9 texture, RECT rect, D3DXVECTOR3 center, D3DXVECTOR3 position,
		D3DXVECTOR2 scale,
		D3DXVECTOR2 scalingCenter,
		D3DXVECTOR2 translation = D3DXVECTOR2(0, 0));
	void DrawSurface(LPDIRECT3DSURFACE9 surface, RECT* sRect, RECT* dRect);

	LPD3DXSPRITE getSprite();

	static GraphicsGame* getInstance();

	LPDIRECT3DSURFACE9 GetBackBuffer();

	GraphicsGame();
	~GraphicsGame();
};


#endif // !_GRAPHICSGAME_H_


