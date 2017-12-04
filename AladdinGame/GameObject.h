#pragma once

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Global.h"
#include "Viewport.h"
#include "Rect.h"
#include "Collision.h"

class GameObject
{
protected:
	Object _id; //Object id
	float _dx, _dy; //_d = v * t
	D3DXVECTOR3 _position; //pos in WORLD
	int _width, _height; //size
	float _v0, _vx, _vy; //velocity
	float _ax, _ay; //accelerator
	Direct _direct; //direct
	Transform _transform; //vector transform
	Rect _rectBound; //rectangle bound object
public:
	Object GetId();
	float GetV0();
	float GetVx();
	float GetVy();
	float GetAx();
	float GetAy();
	Rect GetRect();
	int GetWidth();
	int GetHeight();
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetCenterPosition();

	void SetId(Object obj);
	void SetPosition(D3DXVECTOR3 position);
	void SetV0(float v0);
	void SetVx(float vx);
	void SetVy(float vy);
	void SetAx(float ax);
	void SetAy(float ay);
	void SetRect(Rect rect);
	void UpdateRect();

	void Create(D3DXVECTOR3 position, int width, int height, Rect rect);

	D3DXVECTOR3 GetPositionInViewport();

	GameObject();
	~GameObject();
};

#endif // !_GAMEOBJECT_H_



