#ifndef _TIMEGAME_H_
#define _TIMEGAME_H_

#include <Windows.h>

#pragma once
class TimeGame
{
private:
	static TimeGame* instance;
	float start;
	float frequency;
	void Update();

public:
	float currentTime;
	float totalTime;
	bool Init();
	void Run();

	static TimeGame* getInstance();
	
	TimeGame();
	~TimeGame();
};

#endif // !_TIMEGAME_H_
