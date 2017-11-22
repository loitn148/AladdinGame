#pragma once
enum  Direct
{
	LEFT = -1,
	RIGHT = 1
};

enum Object
{
	PLAYER,
	APPLE
};

enum IdObject
{
	CHARACTER
};

enum AladdinStatus
{
	RUN = 0,
	STOP = 1,
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

//map
#define MAP_PATH "Resource/map.png"

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

//width - height - velocity
#define HEIGHT_ALADDIN 55
#define WIDTH_ALADDIN 55

#define VELOCITY_X 90.0f
#define VELOCITY_Y 150.0f

#define ACCELERATOR 10.0f
#define GRAVITY 5.0f;
