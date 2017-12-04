#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "SpriteGame.h"
#include "GraphicsGame.h"
#include "Global.h"
#include "Rect.h"
#include "vector"


#pragma once

class Animation
{
private:
	LPDIRECT3DTEXTURE9 _image;
	int _width, _height;
	int _nFrame; //number frame of iamge
	float _deltaTime; // Thoi gian chuyen frame
	float _totalTime; //Thoi gian chay frame: currentTime >= delayTime: chuyen frame
	int _index; //Frame dang hien thi
	Direct _direct;
	std::vector<Rect> _rectSprite;
public:
	int NextFrame(float time); //frame tiep theo
	void Draw(D3DXVECTOR3 position, Direct direct, float, D3DXVECTOR2 scale, D3DXVECTOR2 translation); //ve frame hien tai
	void Create(char* fileName, int width, int height, int nFrame, float deltaTime, Direct direct);
	void Create(char* fileName, int nFrame, std::vector<Rect> rect, float timeFrame, Direct direct);
	int GetIndex();
	void SetIndex(int inx);
	int GetTotalFrame();

	Animation(char* fileName, int width, int height, int nFrame, float deltaTime, Direct direct);
	Animation();
	~Animation();
};

#endif // !_ANIMATION_H_



