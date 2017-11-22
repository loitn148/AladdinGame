#ifndef _GRAPHICSGAME_H_
#define _GRAPHICSGAME_H_

#include <d3d9.h>

#pragma once
class GraphicsGame
{
private:
	LPDIRECT3D9 d3d;
	static GraphicsGame* instance;
public:
	LPDIRECT3DDEVICE9 device;
	bool Init(HWND, bool); 
	void Clear(DWORD);
	void Begin();
	void End();
	void Present();

	static GraphicsGame* getInstance();

	GraphicsGame();
	~GraphicsGame();
};


#endif // !_GRAPHICSGAME_H_


