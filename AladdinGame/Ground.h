#pragma once
#ifndef _GROUND_H_
#define _GROUND_H_

#include "GameObject.h"

class Ground : public GameObject
{
public:
	Ground(D3DXVECTOR3 position, int width, int height);
	~Ground();
};

#endif // !_GROUND_H_
