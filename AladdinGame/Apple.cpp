#include "Apple.h"

Apple::Apple()
{
	this->_id = APPLE;
}


Apple::~Apple()
{
}

Apple::Apple(D3DXVECTOR3 position, float vx, float vy) 
{
	_animation = new Animation[1];
	_animation[0].Create(APPLE_PATH, 5, 5, 1, 0.01f, RIGHT);
	this->_position = position;
	this->_vx = vx;
	this->_vy = vy;
	this->_isDead = false;
}

void Apple::Update(float time)
{
	_vy -= 2;
	_position.x += _vx*time;
	_position.y += _vy*time;
	if (_position.y - this->_height <= WORLD_BASE_Y)
		_isDead = true;
}

void Apple::Draw(float time)
{
	if (!_isDead)
	{
		this->_transform._positionInViewport = this->GetPositionInViewport();
		D3DXVECTOR3 cameraPosition = Viewport::getInstance()->getViewPortPositon(Camera::getInstance()->GetPosition());
		this->_transform._translation = D3DXVECTOR2(-cameraPosition.x, -cameraPosition.y);

		_animation->Draw(this->_transform._positionInViewport, _direct, time, D3DXVECTOR2(1, 1), _transform._translation);
	}
}
