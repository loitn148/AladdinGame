#include "GameObject.h"


GameObject::GameObject()
{}

GameObject::~GameObject()
{}

Object GameObject::GetId()
{
	return this->_id;
}

float GameObject::GetV0()
{
	return this->_v0;
}

float GameObject::GetVx()
{
	return this->_vx;
}

float GameObject::GetVy()
{
	return this->_vy;
}

float GameObject::GetAx()
{
	return this->_ax;
}

float GameObject::GetAy()
{
	return this->_ay;
}

Rect GameObject::GetRect()
{
	return this->_rectBound;
}

int GameObject::GetWidth()
{
	return this->_width;
}

int GameObject::GetHeight()
{
	return this->_height;
}

D3DXVECTOR3 GameObject::GetPosition()
{
	return this->_position;
}

D3DXVECTOR3 GameObject::GetCenterPosition()
{
	D3DXVECTOR3 center = D3DXVECTOR3(_position.x + _width / 2, _position.y + _height / 2, 0);
	return center;
}

D3DXVECTOR3 GameObject::GetPositionInViewport()
{
	D3DXVECTOR3 curPos = this->GetPosition();
	return Viewport::getInstance()->getViewPortPositon(curPos);
}

void GameObject::SetId(Object id)
{
	this->_id = id;
}

void GameObject::SetPosition(D3DXVECTOR3 position)
{
	this->_position = position;
}

void GameObject::SetV0(float v0)
{
	this->_v0 = v0;
}

void GameObject::SetVx(float vx)
{
	this->_vx = vx;
}

void GameObject::SetVy(float vy)
{
	this->_vy = vy;
}

void GameObject::SetAx(float ax)
{
	this->_ax = ax;
}

void GameObject::SetAy(float ay)
{
	this->_ay = ay;
}

void GameObject::SetRect(Rect rect)
{
	this->_rectBound = rect;
}

void GameObject::UpdateRect()
{
	_rectBound.top = _position.y + _height;
	_rectBound.left = _position.x - _width / 2;
	_rectBound.bottom = _position.y;
	_rectBound.right = _rectBound.left + _width;
}

void GameObject::Create(D3DXVECTOR3 position, int width, int height, Rect rect)
{
	this->_position = position;
	this->_width = width;
	this->_height = height;
	this->_vx = 0;
	this->_vy = 0;
	this->_direct = RIGHT;
	this->_rectBound = rect;
}
