#pragma once

//World
#define WORLD_X 9542 // = map width
#define WORLD_Y 1720  // = map height
#define WORLD_BASE_Y 100 //Position of world when aladdin stand

//Map
#define MAP_WIDTH 9542 //Map width 4771*2
#define MAP_HEIGHT 1376 //Map height 688*2

//Width, height of Windows
#define WND_WIDTH 800
#define WND_HEIGHT 600

//width - height - velocity
#define ALADDIN_WIDTH 121 //width 55*1.5
#define ALADDIN_HEIGHT 138 //height 55*2.5

#define VELOCITY_X 200.0f
#define VELOCITY_Y 200.0f

#define GRAVITY 5.0f

//Apple
#define APPLE_VX 200.0f
#define APPLE_VY 200.0f

//Camera
#define DELTA_CAMERA 5

struct Transform
{
	D3DXVECTOR3 _positionInViewport; //pos in view port
	D3DXVECTOR2 _translation; //pos translation
	D3DXVECTOR2 _scale; //vector scale
	D3DXVECTOR2 _scalingCenter; //pos to scale: center of object
};

enum Direct
{
	LEFT = -1,
	RIGHT = 1
};

enum Object
{
	PLAYER,
	APPLE
};

enum AladdinStatus
{
	RUN = 0,
	STOP_RUN = 1,
	STAND = 2,
	STAND_ATTACK = 3,
	STAND_THROW = 4,
	SIT = 5,
	SIT_ATTACK = 6,
	SIT_THROW = 7,
	JUMP = 8,
	LOOK_UP = 9,
	CLIMB_Y = 10,
	FALLING = 11,
	RUN_JUMP = 12,
	JUMP_THROW = 13,
	JUMP_ATTACK = 14,
	CLIMB_X = 15,
	CLIMB_ATTACK = 16,
	CLIMB_THROW = 17, 
	CLIMB_X_STOP = 18
};

enum KeyPress
{
	PressKeyUp,
	PressKeyDown,
	PressKeyLeft,
	PressKeyRight,
	PressKeyA,
	PressKeyS,
	PressKeyD
};

//-----PATH SOURCE-----//

//map path
#define MAP_1_PATH "Resource/map/map-part-1.png"
#define MAP_2_PATH "Resource/map/map-part-2.png"

//path status

#define RUN_PATH "Resource/aladdin/dichuyen.png"
#define STOP_PATH "Resource/aladdin/dunglai.png"
#define STAND_PATH "Resource/aladdin/dungyen.png"
#define STAND_ATTACK_PATH "Resource/aladdin/dungchem.png"
#define STAND_THROW_PATH "Resource/aladdin/dungnemtao.png"
#define SIT_PATH "Resource/aladdin/ngoi.png"
#define SIT_ATTACK_PATH "Resource/aladdin/ngoichem.png"
#define SIT_THROW_PATH "Resource/aladdin/ngoinemtao.png"
#define JUMP_PATH "Resource/aladdin/nhay.png"
#define LOOK_UP_PATH "Resource/aladdin/nhinlen.png"
#define CLIMB_Y_PATH "Resource/aladdin/leoday.png"
#define FALLING_PATH "Resource/aladdin/roixuong.png"
#define RUN_JUMP_PATH "Resource/aladdin/chaynhay.png"
#define JUMP_THROW_PATH "Resource/aladdin/nhaynemtao.png"
#define JUMP_ATTACK_PATH "Resource/aladdin/nhaychem.png"
#define CLIMB_X_PATH "Resource/aladdin/dudaydichuyen.png"
#define CLIMB_ATTACK_PATH "Resource/aladdin/dudaychem.png"
#define CLIMB_THROW_PATH "Resource/aladdin/dudaynemtao.png"
#define CLIMB_X_STOP_PATH "Resource/aladdin/dudaydungyen.png"

//Apple path 
#define APPLE_PATH "Resource/item/apple/apple.png"