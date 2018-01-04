#pragma once
#ifndef _COLLISION_H_
#define _COLLISION_H_


#include <d3dx9.h>
#include "Rect.h"
#include "Global.h"
#include <iostream>
using namespace std;

class Collision
{
public:
	static CollisionResult SweptAABB(Rect item1, D3DXVECTOR2 v1, Rect item2, D3DXVECTOR2 v2, float time);
	Collision();
	~Collision();
};

#endif // !_COLLISION_H_




