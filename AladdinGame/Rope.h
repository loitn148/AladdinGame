#pragma once
#ifndef _ROPE_H_
#define _ROPE_H_

#include "GameObject.h"

class Rope :public GameObject
{
public:
	Rope(D3DXVECTOR3 position, int width, int height);
	~Rope();
};


#endif // !_ROPE_H_


