#include "Game.h"


Game::Game()
{
	_timeLoop = 0;
}


Game::~Game()
{
}

bool Game::Init(HWND hWnd, HINSTANCE hInstance)
{
	this->_hWnd = hWnd;
	this->_hInstance = hInstance;

	GraphicsGame::getInstance()->Init(hWnd, true);

	if (!GraphicsGame::getInstance()->Init(hWnd, true))
	{
		return false;
	}

	SpriteGame::getInstance()->Init(GraphicsGame::getInstance()->device);
	TimeGame::getInstance()->Init();
	
	Viewport::getInstance()->Init(0, WND_HEIGHT);
	this->LoadContent();
	return true;
}

void Game::Run()
{
	TimeGame::getInstance()->Run();

	_timeLoop += TimeGame::getInstance()->currentTime;
	if (_timeLoop >= 1.0f / 60)
	{
		/*if (GraphicsGame::getInstance()->device->BeginScene())
		{
			GraphicsGame::getInstance()->getSprite()->Begin(D3DXSPRITE_ALPHABLEND);
			GraphicsGame::getInstance()->device->ColorFill(
				GraphicsGame::getInstance()->GetBackBuffer(),
				NULL,
				D3DCOLOR_XRGB(0, 0, 0));*/
			SenceManager::getInstance()->GetCurrentSence()->Update(_timeLoop);

			GraphicsGame::getInstance()->Begin();
			SpriteGame::getInstance()->Begin();

			SenceManager::getInstance()->GetCurrentSence()->Draw(_timeLoop);
			
			SpriteGame::getInstance()->End();
			GraphicsGame::getInstance()->End();
			GraphicsGame::getInstance()->Present();

		/*}*/

		_timeLoop = 0;
	}
}

void Game::LoadContent()
{
	PlaySence* sence = new PlaySence(_hWnd, _hInstance);
	sence->LoadContent();
	SenceManager::getInstance()->ReplaceSence(sence);
}
