#ifndef _GAME_H_
#define _GAME_H_

#include "AladdinCharacter.h"
#include "Camera.h"
#include "Map.h"
#include "SenceManager.h"
#include "PlaySence.h"
#include "Viewport.h"

#pragma once

class Game
{
private:

	HWND _hWnd;
	HINSTANCE _hInstance;
	float _timeLoop;

public:
	bool Init(HWND hWnd, HINSTANCE hInstance);
	void Run();
	void LoadContent();

	Game();
	~Game();
};

#endif // !_GAME_H_


