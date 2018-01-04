#include "Rope.h"

Rope::Rope(D3DXVECTOR3 position, int width, int height)
{
	this->_vx = this->_vy = 0;
	this->_position = position;
	this->_width = width;
	this->_height = height;
	this->_id = ROPE;
	UpdateRect();
}

Rope::~Rope()
{
}
