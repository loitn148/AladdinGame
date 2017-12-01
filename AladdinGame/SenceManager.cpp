#include "SenceManager.h"


SenceManager * SenceManager::_instance = 0;
SenceManager * SenceManager::getInstance()
{
	if (!SenceManager::_instance)
	{
		SenceManager::_instance = new SenceManager();
	}
	return SenceManager::_instance;
}

void SenceManager::Update(float time)
{
	this->_currentSence->Update(time);
}

Sence * SenceManager::GetCurrentSence()
{
	return this->_currentSence;
}

void SenceManager::ReplaceSence(Sence * sence)
{
	if (this->_currentSence)
		delete(this->_currentSence);
	this->_currentSence = sence;
}

SenceManager::SenceManager()
{
}


SenceManager::~SenceManager()
{
}
