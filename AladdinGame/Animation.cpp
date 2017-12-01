#include "Animation.h"


Animation::Animation(char* fileName, int width, int height, int nFrame, float deltaTime, Direct direct)
{
	this->_image = GraphicsGame::getInstance()->loadTexture(fileName, D3DCOLOR_XRGB(0, 0, 0));
	this->_width = width;
	this->_height = height;
	this->_nFrame = nFrame;
	this->_deltaTime = deltaTime;
	this->_direct = direct;
	this->_index = 0;
	this->_totalTime = 0;
}

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::Create(char* fileName, int width, int height, int nFrame, float deltaTime, Direct direct)
{
	this->_image = GraphicsGame::getInstance()->loadTexture(fileName, D3DCOLOR_XRGB(0, 0, 0));
	this->_width = width;
	this->_height = height;
	this->_nFrame = nFrame;
	this->_deltaTime = deltaTime;
	this->_direct = direct;
	this->_index = 0;
	this->_totalTime = 0;
}

int Animation::NextFrame(float time)
{
	_totalTime += time;
	if (_totalTime >= _deltaTime)
	{
		_index = (_index + 1) % _nFrame;
		_totalTime = 0;
	}
	return _index;
}

void Animation::Draw(D3DXVECTOR3 position, Direct d, float time, D3DXVECTOR2 scale, D3DXVECTOR2 translation)
{
	int widthFrame = _width / _nFrame;
	RECT rect;
	rect.top = 0;
	rect.bottom = _height;
	rect.left = _index * widthFrame;
	rect.right = rect.left + widthFrame;

	if (d == _direct)
	{
		SpriteGame::getInstance()->Draw(_image, &rect, D3DXVECTOR3(0, 0, 0), position, scale, D3DXVECTOR2(position.x, position.y), translation);
	}
	else
	{
		/*SpriteGame::getInstance()->FlipX(widthFrame, height, scale, position);*/
		SpriteGame::getInstance()->Draw(_image,  &rect, D3DXVECTOR3(0, 0, 0), position, D3DXVECTOR2(-scale.x, scale.y),
			D3DXVECTOR2(position.x + widthFrame/2, position.y), translation);
		/*SpriteGame::getInstance()->ResetTranform();*/
	}
	_index = NextFrame(time);
}

int Animation::GetIndex()
{
	return this->_index;
}

void Animation::SetIndex(int inx)
{
	this->_index = inx;
}

int Animation::GetTotalFrame()
{
	return this->_nFrame;
}

