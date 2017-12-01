#pragma once
#ifndef _SENCEMANAGER_H_
#define _SENCEMANAGER_H_

#include "Sence.h"

class SenceManager
{
private:
	static SenceManager* _instance;
	Sence* _currentSence;
public:
	static SenceManager* getInstance();
	void Update(float time);
	Sence* GetCurrentSence();
	void ReplaceSence(Sence* sence);
	SenceManager();
	~SenceManager();
};

#endif // !_SENCEMANAGER_H_

