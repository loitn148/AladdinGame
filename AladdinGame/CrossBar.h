#pragma once
#ifndef _CROSSBAR_H_
#define _CROSSBAR_H_

#include "GameObject.h"

class CrossBar : public GameObject
{
public:
	CrossBar(D3DXVECTOR3 position, int width, int height);
	~CrossBar();
};

#endif // !_CROSSBAR_H_



