#include "InputGame.h"


InputGame::InputGame()
{
	diObject = NULL;
	diDevice = NULL;
}


InputGame::~InputGame()
{
}

void InputGame::InitKeyBoard(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;
	hr = DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(VOID**)&diObject,
		NULL);

	if (hr != DI_OK) return;

	hr = diObject->CreateDevice(GUID_SysKeyboard, &diDevice, NULL);
	if (hr != DI_OK) return;

	hr = diDevice->SetDataFormat(&c_dfDIKeyboard);
	if (hr != DI_OK) return;

	hr = diDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (hr != DI_OK) return;

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = diDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return;

	hr = diDevice->Acquire();
	if (hr != DI_OK) return;
}

void InputGame::ProcessKeyBoard(HWND _hWnd)
{

	// Collect all key states first
	diDevice->GetDeviceState(sizeof(keyStates), keyStates);


	if (isKeyDown(DIK_ESCAPE))
	{
		PostMessage(_hWnd, WM_QUIT, 0, 0);
	}

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = diDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);

	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);
	}
}

int InputGame::isKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

void InputGame::OnKeyUp(int KeyCode) {  }

void InputGame::OnKeyDown(int KeyCode) { }

void InputGame::CleanUp()
{

	if (diDevice != NULL)
	{
		diDevice->Release();
	}

	if (diObject != NULL)
	{
		diObject->Release();
	}

	if (diDevice)
	{
		diDevice->Unacquire();
		diDevice->Release();
	}
}
