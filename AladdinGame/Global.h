#pragma once

//World
#define WORLD_X 9542 // = map width
#define WORLD_Y 1720  // = map height
#define WORLD_BASE_Y 150 //Position of world when aladdin stand

//Map
#define MAP_WIDTH 9542 //Map width 4771*2
#define MAP_HEIGHT 1720 //Map height 688*2.5

//Width, height of Windows
#define WND_WIDTH 800
#define WND_HEIGHT 600

//width - height - velocity
#define ALADDIN_WIDTH 20 //
#define ALADDIN_HEIGHT_STAND 130
#define ALADDIN_HEIGHT_CLIMB 210
#define ALADDIN_HEIGHT_SIT 80

#define VELOCITY_X 250.0f
#define VELOCITY_JUMP_X 700.0f
#define VELOCITY_Y 500.0f
#define VELOCITY_CLIMB_Y 200.0f

#define GRAVITY 20.0f

//Apple
#define APPLE_VX 1000.0f
#define APPLE_VY 30.0f

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
	RIGHT = 1,
	TOP = -2,
	BOTTOM = 2,
	NONE = 0
};

struct CollisionResult //Ket qua va cham
{
	float _entryTime; //Thoi gian de xay ra va cham
	float _remainingTime; //Thoi gian sau khi va cham
	float _exitTime; //Thoi gian ket thuc va cham
	bool _isCollision; //Kiem tra co xay ra va cham hay khong?
	Direct _directCollision; //Huong va cham
	int _indexObject; //Stt cua object trong list
};

enum Object
{
	PLAYER,
	APPLE,
	GROUND,
	ROPE,
	CROSSBAR,
	NONEOBJECT
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
	CLIMB_X_STOP = 18,
	WAIT1 = 19,
	WAIT2 = 20,
	LOOK_UP_ATTACK = 21,
	PUSH_WALL = 22,
	ROLLING = 23,
	RUN_ATTACK = 24,
	RUN_THROW = 25,
	DIE = 26,
	CLIMB_JUMP = 27

};

enum CollisionBox
{
	BoundingBox,
};

//-----PATH SOURCE-----//

//map path
#define MAP_1_PATH "Resource/map/map-part-1.png"
#define MAP_2_PATH "Resource/map/map-part-2.png"

//Rope path
#define ROPE_PATH "Resource/map/Rope.png"

//CrossBar path
#define CROSSBAR_PATH "Resource/map/Crossbar.png"

//path status

#define RUN_PATH "Resource/aladdin/Run.png"
#define STOP_PATH "Resource/aladdin/StopRun.png"
#define STAND_PATH "Resource/aladdin/Stand.png"
#define STAND_ATTACK_PATH "Resource/aladdin/StandAttack.png"
#define STAND_THROW_PATH "Resource/aladdin/StandThrow.png"
#define SIT_PATH "Resource/aladdin/SitDown.png"
#define SIT_ATTACK_PATH "Resource/aladdin/SitAttack.png"
#define SIT_THROW_PATH "Resource/aladdin/SitThrow.png"
#define JUMP_PATH "Resource/aladdin/Jump.png"
#define LOOK_UP_PATH "Resource/aladdin/LookUp.png"
#define CLIMB_Y_PATH "Resource/aladdin/ClimbY.png"
#define FALLING_PATH "Resource/aladdin/Falling.png"
#define RUN_JUMP_PATH "Resource/aladdin/RunJump.png"
#define JUMP_THROW_PATH "Resource/aladdin/JumpThrow.png"
#define JUMP_ATTACK_PATH "Resource/aladdin/JumpAttack.png"
#define CLIMB_X_PATH "Resource/aladdin/ClimbX.png"
#define CLIMB_ATTACK_PATH "Resource/aladdin/ClimbAttack.png"
#define CLIMB_THROW_PATH "Resource/aladdin/ClimbThrow.png"
#define CLIMB_X_STOP_PATH "Resource/aladdin/ClimbXStop.png"
#define WAIT1_PATH "Resource/aladdin/Wait1.png"
#define WAIT2_PATH "Resource/aladdin/Wait2.png"
#define LOOK_UP_ATTACK_PATH "Resource/aladdin/LookUpAttack.png"
#define PUSH_WALL_PATH "Resource/aladdin/PushWall.png"
#define ROLLING_PATH "Resource/aladdin/Rolling.png"
#define RUN_ATTACK_PATH "Resource/aladdin/RunAttack.png"
#define RUN_THROW_PATH "Resource/aladdin/RunThrow.png"
#define DIE_PATH "Resource/aladdin/Die.png"
#define CLIMB_JUMP_PATH "Resource/aladdin/ClimbJump.png"

//Apple path 
#define APPLE_PATH "Resource/item/apple/Apple.png"
#define BUMB_PATH "Resource/item/apple/Bumb.png"

