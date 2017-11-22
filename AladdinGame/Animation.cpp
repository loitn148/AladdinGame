#include "Animation.h"


Animation::Animation(char* fileName, int w, int h, int nF, float dt, Direct d)
{
	image.Init(GraphicsGame::getInstance()->device, fileName, w, h);
	width = w;
	height = h;
	nFrame = nF;
	delayTime = dt;
	direct = d;
	index = 0;
	currentTime = 0;
}

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::Create(char* fileName, int w, int h, int nF, float dt, Direct d)
{
	image.Init(GraphicsGame::getInstance()->device, fileName, w, h);
	width = w;
	height = h;
	nFrame = nF;
	delayTime = dt;
	direct = d;
	index = 0;
	currentTime = 0;
}

int Animation::Update(float time)
{
	currentTime += time;
	if (currentTime >= delayTime)
	{
		index = (index + 1) % nFrame;
		currentTime = 0;
	}
	return index;
}

void Animation::Draw(D3DXVECTOR3 position, Direct d, float time)
{
	int widthFrame = width / nFrame;
	RECT rect;
	rect.top = 0;
	rect.bottom = height;
	rect.left = index * widthFrame;
	rect.right = rect.left + widthFrame;

	if (d == direct)
	{
		SpriteGame::getInstance()->Draw(image, &rect, position);
	}
	else
	{
		SpriteGame::getInstance()->FlipX(widthFrame, height, position);
		SpriteGame::getInstance()->Draw(image, &rect, position);
		SpriteGame::getInstance()->ResetTranform();
	}
	index = Update(time);
}

int Animation::GetIndex()
{
	return index;
}

void Animation::SetIndex(int inx)
{
	this->index = inx;
}

int Animation::GetTotalFrame()
{
	return nFrame;
}

