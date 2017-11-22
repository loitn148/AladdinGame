#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "TextureGame.h"
#include "SpriteGame.h"
#include "GraphicsGame.h"
#include "Global.h"

#pragma once

class Animation
{
private:
	TextureGame image;
	int width;
	int height;
	int nFrame; //number frame of iamge
	float delayTime; // Thoi gian chuyen frame
	float currentTime; //Thoi gian chay frame: currentTime >= delayTime: chuyen frame
	int index; //Frame dang hien thi
	Direct direct;
public:
	int Update(float time); //frame tiep theo
	void Draw(D3DXVECTOR3, Direct, float); //ve frame hien tai
	void Create(char*, int, int, int, float, Direct);
	int GetIndex();
	void SetIndex(int inx);
	int GetTotalFrame();

	Animation(char*, int, int, int, float, Direct);
	Animation();
	~Animation();
};

#endif // !_ANIMATION_H_



