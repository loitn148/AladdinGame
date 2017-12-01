#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
using namespace std;

#pragma once

class Background
{
private:
	static  Background* instance;
	D3DXIMAGE_INFO info;
	LPDIRECT3DDEVICE9 device;
public:
	LPDIRECT3DSURFACE9 sufface;
	void Create(char* fileName, LPDIRECT3DDEVICE9 device);

	static Background* getInstance();

	Background();
	~Background();
};

#endif // !_BACKGROUND_H_




