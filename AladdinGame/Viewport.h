#pragma once
#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include <d3dx9.h>
#include "Global.h"

class Viewport
{
private:
	static Viewport* instance;
	int _x0, _y0; //pos of viewport on WORLD
public:
	int GetX();
	int GetY();
	void Init(int x, int y);
	static Viewport* getInstance();
	D3DXVECTOR3 getViewPortPositon(D3DXVECTOR3 worldPosition);
	Viewport();
	~Viewport();
};

#endif // !_VIEWPORT_H_

