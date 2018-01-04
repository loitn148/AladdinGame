#pragma once
#ifndef _RECT_H_
#define _RECT_H_

#include <d3d9.h>
#include <d3dx9.h>

class Rect : public RECT
{
private:
	D3DXVECTOR3 center;
public:
	D3DXVECTOR3 GetCenter();
	Rect(int top, int left, int bottom, int right, D3DXVECTOR3 deltaCenter = D3DXVECTOR3(0, 0, 0));
	Rect();
	~Rect();
};

#endif // !_RECT_H_



