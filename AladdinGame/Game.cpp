#include "Game.h"


Game::Game()
{
	backBuffer = NULL;
	currentTime = 0;
}


Game::~Game()
{
	if (GraphicsGame::getInstance())
	{
		/*delete graphics;
		graphics = nullptr;*/
	}
}

bool Game::Init(HWND hWnd, HINSTANCE hInstance)
{
	this->hWnd = hWnd;
	this->hInstance = hInstance;

	if (!GraphicsGame::getInstance()->Init(hWnd, true))
	{
		return false;
	}
	GraphicsGame::getInstance()->device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	SpriteGame::getInstance()->Init(GraphicsGame::getInstance()->device);
	TimeGame::getInstance()->Init();
	Background::getInstance()->Create(MAP_PATH, GraphicsGame::getInstance()->device);

	AladdinCharacter::getInstance()->Create(GraphicsGame::getInstance()->device, 600, 800, 55, 55);
	AladdinCharacter::getInstance()->Init(hInstance, hWnd);
	return true;
}

void Game::Run()
{
	TimeGame::getInstance()->Run();
	currentTime += TimeGame::getInstance()->currentTime;
	if (currentTime >= 1.0f / 60)
	{
		Update();
		Draw();
		currentTime = 0;
	}
}

void Game::Update()
{
	AladdinCharacter::getInstance()->Update(currentTime);
}
void Game::Draw()
{
	GraphicsGame::getInstance()->Clear(D3DCOLOR_XRGB(255, 255, 255));
	GraphicsGame::getInstance()->Begin();
	SpriteGame::getInstance()->Begin();
	GraphicsGame::getInstance()->device->StretchRect(Background::getInstance()->sufface, NULL, backBuffer, NULL, D3DTEXF_NONE);
	AladdinCharacter::getInstance()->Draw(currentTime);
	SpriteGame::getInstance()->End();
	GraphicsGame::getInstance()->End();
	GraphicsGame::getInstance()->Present();
}
