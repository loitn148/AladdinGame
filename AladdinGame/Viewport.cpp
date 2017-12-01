#include "Viewport.h"


Viewport* Viewport::instance = NULL;
Viewport* Viewport::getInstance()
{
	if (!instance)
	{
		Viewport::instance = new Viewport();
	}
	return Viewport::instance;
}
Viewport::Viewport()
{
	this->_x0 = 0;
	this->_y0 = WND_HEIGHT;
}


Viewport::~Viewport(){}

void Viewport::Init(int x, int y)
{
	this->_x0 = x;
	this->_y0 = y;
}

int Viewport::GetX()
{
	return _x0;
}

int Viewport::GetY()
{
	return _y0;
}

D3DXVECTOR3 Viewport::getViewPortPositon(D3DXVECTOR3 worldPosition)
{
	worldPosition.z = 1;
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1.0f;
	matrix._41 = -_x0;
	matrix._42 = _y0;

	D3DXVECTOR4 viewport;
	D3DXVec3Transform(&viewport, &worldPosition, &matrix);

	D3DXVECTOR3 positionViewport = D3DXVECTOR3(viewport.x, viewport.y, 0);
	return positionViewport;
}


