#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_


#include <d3dx9.h>
#include <DirectXMath.h>
#include "GraphicsGame.h"
#include "AladdinCharacter.h"
#include "Global.h"
#include <iostream>
using namespace std;

class AladdinCharacter;

class Camera
{
private:
	static Camera* _instance;
	D3DXVECTOR3 _position; //pos in WORLD
	int _width, _height;
	float _vx, _vy; //velocity
public:
	static Camera* getInstance();
	void CameraOnWORLD();
	void Update(AladdinCharacter * aladdin);
	void SetPosition(D3DXVECTOR3 position);
	void SetPositionY(int y);
	RECT GetRect();
	D3DXVECTOR3 GetPosition();
	void Create(D3DXVECTOR3 position, int width, int height);
	Camera();
	~Camera();
};

#endif // !_CAMERA_H_

