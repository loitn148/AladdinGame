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
	_listApple = new Animation[2];

	std::vector<Rect> _temp;

	//Apple Collision Land
	_temp.push_back(Rect(28, 51, 38, 58));
	_temp.push_back(Rect(28, 30, 46, 50));
	_temp.push_back(Rect(26, 0, 48, 29));
	_temp.push_back(Rect(0, 0, 25, 31));
	_temp.push_back(Rect(0, 32, 27, 62));

	_listApple[0].Create(BUMB_PATH, _temp.size(), _temp, 0.05f, RIGHT);
	_temp.clear();

	//Apple
	_temp.push_back(Rect(0, 28, 7, 35));
	_temp.push_back(Rect(0, 0, 7, 9));
	_temp.push_back(Rect(0, 20, 8, 27));
	_temp.push_back(Rect(0, 10, 6, 19));

	_listApple[1].Create(APPLE_PATH, _temp.size(), _temp, 0.05f, RIGHT);
	_temp.clear();

	
	this->_currentState = 1; //Trai tao
	this->_id = APPLE;
	this->_position = position;
	this->_vx = vx;
	this->_vy = vy;
	this->_isDead = false;
	this->_width = 10;
	this->_height = 10;
	UpdateRect();
}

void Apple::Update(float time)
{
	CollisionResult result;
	_vy -= APPLE_VY;
	_position.x += _vx*time;
	_position.y += _vy*time;

	UpdateRect();

	switch (_currentState)
	{
	case 1: //Trai tao
		result = StaticObject::getInstance()->GroundCollision(this, time);
		if (result._isCollision)
		{
			_currentState = 0; //Hieu ung cham dat
			_vx = 0;
			_vy = 0;
		}
			
		break;
	case 0: //Hieu ung cham dat
		if(_listApple[_currentState].GetIndex() == _listApple[_currentState].GetTotalFrame() - 1 )
			this->_isDead = true;
		break;
	}
}

void Apple::Draw(float time)
{
	if (!_isDead)
	{
		this->_transform._positionInViewport = this->GetPositionInViewport();
		D3DXVECTOR3 cameraPosition = Viewport::getInstance()->getViewPortPositon(Camera::getInstance()->GetPosition());
		this->_transform._translation = D3DXVECTOR2(-cameraPosition.x, -cameraPosition.y);

		_listApple[_currentState].Draw(this->_transform._positionInViewport, _direct, time, D3DXVECTOR2(1.5, 1.5), _transform._translation);
	}
}
