#ifndef _ALADDINCHARACTER_H_
#define _ALADDINCHARACTER_H_

#pragma once

#include "Animation.h"
#include "InputGame.h"
#include "GameObject.h"
#include "Global.h"
#include "TimeGame.h"
#include <iostream>
using namespace std;

class AladdinCharacter :public GameObject, public InputGame
{
private:
	static AladdinCharacter* instance;
	bool isActionDone; //kiem tra hanh dong da thuc hien xong chua
	HWND hWnd;
	HINSTANCE hInstance;

	AladdinStatus currentAction;
	string fileName;

	int currentIndex;
	int countIndex;

	int press_key_run;
	int press_key_sit;
	int press_key_lookup;
	int press_key_d;

	bool isJumping;
	bool isFalling;
	bool isClimbingY;
	
	Animation* listAction;
public:

	static AladdinCharacter* getInstance();
	void SetListAction();
	void Init(HINSTANCE, HWND);
	void UpdateAction();
	void UpdatePosition(float);
	void Draw(float);
	void Update(float);
	void OnKeyUp(int);
	void OnKeyDown(int);

	//hanh dong
	void Run();
	void Stop();
	void Stand();
	void StandAttack();
	void StandThrow();
	void Sit();
	void SitAttack();
	void SitThrow();
	void Jump();
	void RunJump();
	void RunJumpAttack();
	void RunJumpThrow();
	void Falling();
	void LookUp();
	void ClimbY();
	void ClimbX();
	void ClimbXStop();
	void ClimbAttack();
	void ClimbThrow();

	AladdinCharacter();
	~AladdinCharacter();
};

#endif // !_ALADDINCHARACTER_H_



