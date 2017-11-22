#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include  <d3d9.h>
#include <cmath>
#include "Global.h"

#pragma once
class GameObject
{
public:
	int id; //id object
	Object type; //loai object
	float x; //toa do
	float y;
	int width; //kich thuoc
	int height;
	float vx; //van toc
	float vy;
	float a; //gia toc
	Direct direct;

	void Create(int, int, int, int);
	void Create(LPDIRECT3DDEVICE9, int, int, int, int);
	virtual void Update(float time);
	virtual void Draw(float time);

	GameObject();
	~GameObject();
protected:
	LPDIRECT3DDEVICE9 device;
};

#endif // !_GAMEOBJECT_H_



