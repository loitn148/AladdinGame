#ifndef _SENCE_H_
#define _SENCE_H_

#pragma once
class Sence
{
public:
	virtual void LoadContent() = 0;
	virtual void Update(float time) = 0;
	virtual void Draw(float time) = 0;
};

#endif //_SENCE_H_