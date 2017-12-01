#include "Map.h"

Map::Map()
{
	this->_position = D3DXVECTOR3(0, WORLD_Y, 0);
	LoadResource();
}

Map::Map(int x, int y, int z)
{
	this->_position = D3DXVECTOR3(x, y, z);
	LoadResource();
}

Map::~Map()
{
}

void Map::SetCamera(Camera* camera)
{
	this->_camera = camera;
}

void Map::LoadResource()
{
	this->_mapRect.left = 0;
	this->_mapRect.top = 0;
	this->_mapRect.right = 4771;
	this->_mapRect.bottom = 688;

	this->_mapTexture = GraphicsGame::getInstance()->loadTexture(MAP_1_PATH, D3DCOLOR_XRGB(0,0,0));
}

void Map::Draw()
{
	D3DXVECTOR3 cameraPosition = Viewport::getInstance()->getViewPortPositon(Camera::getInstance()->GetPosition());

	D3DXVECTOR2 translation = D3DXVECTOR2(-cameraPosition.x, -cameraPosition.y);

	D3DXVECTOR3 inPosition = Viewport::getInstance()->getViewPortPositon(this->_position);

	GraphicsGame::getInstance()->DrawTexture(_mapTexture, _mapRect, D3DXVECTOR3(0, 0, 0), inPosition, D3DXVECTOR2(2, 2.5), D3DXVECTOR2(inPosition.x, inPosition.y), translation);
}
