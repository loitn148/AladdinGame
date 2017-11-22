#ifndef _INPUTGAME_H_
#define _INPUTGAME_H_

#include <dinput.h>

#define KEY_DOWN(code) ( IsKeyDown(code) )
#define KEYBOARD_BUFFER_SIZE 1024

#pragma once

class InputGame
{
protected:
	BYTE keyStates[256];
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];
	LPDIRECTINPUT8 diObject;
	LPDIRECTINPUTDEVICE8 diDevice;
	HRESULT hr;
	int isKeyDown(int keyCode);
public:
	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
	void ProcessKeyBoard(HWND hWnd);
	void InitKeyBoard(HINSTANCE hInstance, HWND hWnd);	
	void CleanUp();

	InputGame();
	~InputGame();
};

#endif // !_INPUTGAME_H_



