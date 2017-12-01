#include "TimeGame.h"


TimeGame::TimeGame()
{
}

TimeGame::~TimeGame()
{
}

TimeGame* TimeGame::instance = NULL;

TimeGame* TimeGame::getInstance()
{
	if (!TimeGame::instance)
	{
		TimeGame::instance = new TimeGame();
	}
	return TimeGame::instance;
}

bool TimeGame::Init()
{
	LARGE_INTEGER i;

	if (!QueryPerformanceFrequency(&i))
	{
		return false;
	}
	this->frequency = (float)(i.QuadPart);
	this->currentTime = 0;
	this->totalTime = 0;

	QueryPerformanceCounter(&i);
	this->start = (float)(i.QuadPart);
}

void TimeGame::Update()
{
	LARGE_INTEGER i;
	QueryPerformanceCounter(&i);
	currentTime = ((float)(i.QuadPart) - start) / frequency;
	totalTime += currentTime;
	start = (float)(i.QuadPart);
}

void TimeGame::Run()
{
	Update();
}