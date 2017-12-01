#pragma once

#ifndef _ALADDINCHARACTER_H_
#define _ALADDINCHARACTER_H_

#include "InputGame.h"
#include "TimeGame.h"
#include "Apple.h"
#include <iostream>
using namespace std;

class Apple;
class Animation;

class AladdinCharacter : public InputGame, public GameObject
{
private:
	static AladdinCharacter* _instance;
	HWND _hWnd;
	HINSTANCE _hInstance;

	AladdinStatus _currentAction;
	string _fileName;

	int _currentIndex;
	int _runCount;
	int _camY;

	bool _isPressKeyRight;
	bool _isPressKeyLeft;
	bool _isPressKeyDown;
	bool _isPressKeyUp;

	bool _isJumping;
	bool _isFalling;
	bool _isStoping;
	bool _isClimbingY;
	bool _isClimbingX;

	Animation* _listAction;
	Apple* _myApple;
public:

	static AladdinCharacter* getInstance();
	void SetListAction();
	void Init(HINSTANCE, HWND);
	void UpdatePosition(float time);
	void Draw(float time);
	void Update(float time);
	void OnKeyUp(int keyCode);
	void OnKeyDown(int keyCode);

	//hanh dong
	void Run();
	void StopRun();

	void Stand();
	void StandAttack();
	void StandThrow();
	void LookUp();

	void Sit();
	void SitAttack();
	void SitThrow();

	void Jump();
	void RunJump();
	void RunJumpAttack();
	void RunJumpThrow();
	void Falling();

	void ClimbY();
	void ClimbX();
	void ClimbXStop();
	void ClimbAttack();
	void ClimbThrow();

	void CreateApple();

	AladdinCharacter();
	~AladdinCharacter();
};

#endif // !_ALADDINCHARACTER_H_



