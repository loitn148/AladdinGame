#include "PlaySence.h"



void PlaySence::LoadContent()
{
	this->_aladdin = AladdinCharacter::getInstance();
	_aladdin->Create(D3DXVECTOR3(100, WORLD_BASE_Y + ALADDIN_HEIGHT, 0), ALADDIN_WIDTH, ALADDIN_HEIGHT);
	_aladdin->Init(_hInstance, _hWnd);

	this->_camera = Camera::getInstance();
	_camera->Create(D3DXVECTOR3(0, WND_HEIGHT, 0), WND_WIDTH, WND_HEIGHT);

	this->_map = new Map();
}

void PlaySence::Update(float time)
{
	this->_camera->Update(this->_aladdin);
	this->_aladdin->Update(time);
}

void PlaySence::Draw(float time)
{
	this->_map->Draw();
	this->_aladdin->Draw(time);
}

PlaySence::PlaySence(HWND hWnd, HINSTANCE hInstance)
{
	this->_hWnd = hWnd;
	this->_hInstance = hInstance;
}

PlaySence::PlaySence()
{
	this->_hWnd = NULL;
	this->_hInstance = NULL;
}

PlaySence::~PlaySence()
{}
