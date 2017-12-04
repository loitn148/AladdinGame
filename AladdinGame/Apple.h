#pragma once

#ifndef _APPLE_H_
#define _APPLE_H_

#include "GameObject.h"
#include "Animation.h"
#include "Camera.h"
#include "Collision.h"
#include "StaticObject.h"

class Apple : public GameObject
{
public:
	void Draw(float time);
	void Update(float time);
	Apple(D3DXVECTOR3 position, float vx, float vy);
	Apple();
	~Apple();
	bool _isDead;
protected:
	Animation* _listApple;
	int _currentState;
};

#endif // !_APPLE_H_



