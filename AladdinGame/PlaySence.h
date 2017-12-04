#pragma once
#ifndef _PLAYSENCE_H_
#define _PLAYSENCE_H_

#include "Sence.h"
#include "AladdinCharacter.h"
#include "Camera.h"
#include "Viewport.h"
#include "TimeGame.h"
#include "Map.h"
#include "StaticObject.h"

class PlaySence : public Sence
{
private:
	HWND _hWnd;
	HINSTANCE _hInstance;

	AladdinCharacter* _aladdin;
	Camera* _camera;
	Map* _map;
	StaticObject* _staticObj;
public:
	void LoadContent();
	void Update(float time);
	void Draw(float time);

	PlaySence(HWND hWnd, HINSTANCE hInstance);
	PlaySence();
	~PlaySence();
};

#endif // !_PLAYSENCE_H_



