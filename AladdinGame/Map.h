#pragma once
#include <d3dx9.h>
#include "GraphicsGame.h"
#include "Camera.h"
#include "Global.h"

class Map
{
private: 
	D3DXVECTOR3 _position;
	RECT _mapRect;

	Camera* _camera;
public:
	LPDIRECT3DTEXTURE9 _mapTexture;
	void SetCamera(Camera* camera);
	void LoadResource();
	void Draw();
	Map(int x, int y, int z);
	Map();
	~Map();
};

