#ifndef _GAME_H_
#define _GAME_H_

#include "AladdinCharacter.h"
#include "Background.h"

#pragma once

class Game
{
private:
	HWND hWnd;
	HINSTANCE hInstance;
	float currentTime;
public:
	bool Init(HWND hWnd, HINSTANCE hInstance);
	void Run();
	void Update();
	void Draw();

	LPDIRECT3DSURFACE9 backBuffer;

	Game();
	~Game();
};

#endif // !_GAME_H_


