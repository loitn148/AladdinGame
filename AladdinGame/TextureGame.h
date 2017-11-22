#ifndef _TEXTUREGAME_H_
#define _TEXTUREGAME_H_

#include <string>
#include <iostream>
#include <d3dx9.h>
using namespace std;

#pragma once

class TextureGame
{
public:
	LPDIRECT3DTEXTURE9 texture;
	bool Init(LPDIRECT3DDEVICE9, std::string, int, int);
	bool initialized = false;
	bool isInit();

	TextureGame();
	~TextureGame();
};

#endif // _TEXTUREGAME_H_


