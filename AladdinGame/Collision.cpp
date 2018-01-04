#include "Collision.h"


CollisionResult Collision::SweptAABB(Rect item1, D3DXVECTOR2 v1, Rect item2, D3DXVECTOR2 v2, float time)
{
	v1.x = (v1.x - v2.x)*time; //Gia su v1 di chuyen, v2 dung yen
	v1.y = (v1.y - v2.y)*time;

	float xEntry, yEntry; //Khoang cach giua 2 vat khi chua va cham
	float xExit, yExit; //Khoang cach giua 2 vat sau khi va cham

	if (v1.x >= 0.0f)
	{
		xEntry = item2.left - item1.right;
		xExit = item2.right - item1.left;
	}
	else
	{
		xEntry = item2.right - item1.left;
		xExit = item2.left - item1.right;
	}

	if (v1.y >= 0.0f)
	{
		yEntry = item2.bottom - item1.top;
		yExit = item2.top - item1.bottom;
	}
	else
	{
		yEntry = item2.top - item1.bottom;
		yExit = item2.bottom - item1.top;
	}

	float txEntry, tyEntry; //Thoi gian den va cham
	float txExit, tyExit; //Thoi gian thoat khoi va cham

	if (v1.x == 0)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = xEntry / v1.x;
		txExit = xExit / v1.x;
	}
	
	if (v1.y == 0)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = yEntry / v1.y;
		tyExit = yExit / v1.y;
	}

	//Kiem tra va cham
	CollisionResult _collisionResult;
	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(txExit, tyExit);

	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f)
	{
		_collisionResult._directCollision = NONE;
		_collisionResult._isCollision = false;
	}
	else
	{
		_collisionResult._isCollision = true;
		//Xac dinh huong va cham
		if (txEntry > tyEntry)
		{
			if (xEntry < 0.0f) //Right of item2
			{
				_collisionResult._directCollision = RIGHT;
			}
			else //Left of item2
			{
				_collisionResult._directCollision = LEFT;
			}
		}
		else
		{
			if (yEntry < 0.0f) //Top of item2
			{
				_collisionResult._directCollision = TOP;
			}
			else //Bottom of item2
			{
				_collisionResult._directCollision = BOTTOM;
			}
		}
	}
	_collisionResult._entryTime = entryTime;
	_collisionResult._exitTime = exitTime;
	_collisionResult._remainingTime = 1.0f - entryTime;

	return _collisionResult;
}

Collision::Collision()
{
}


Collision::~Collision()
{
}
