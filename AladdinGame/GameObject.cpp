#include "GameObject.h"


GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Create(int x, int y, int w, int h)
{
	this->x = (float)x;
	this->y = (float)y;
	this->width = w;
	this->height = h;
	this->vx = 0;
	this->vy = 0;
	this->direct = RIGHT;
}

void GameObject::Create(LPDIRECT3DDEVICE9 device, int x, int y, int w, int h)
{
	this->device = device;
	Create(x, y, w, h);
}

void GameObject::Update(float time){}

void GameObject::Draw(float time){}
