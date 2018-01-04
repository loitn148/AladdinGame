#pragma once
#ifndef _STATICOBJECT_H_
#define _STATICOBJECT_H_

#include "Ground.h"
#include "Rope.h"
#include "CrossBar.h"
#include <vector>

class StaticObject
{
private:
	static StaticObject* _instance;

	std::vector<Ground> _listGround;
	std::vector<CrossBar> _listCrossBar;
	std::vector<Rope> _listRope;
public:
	static StaticObject* getInstance();
	
	void CreateGround();
	std::vector<Ground> GetGround();
	CollisionResult GroundCollision(GameObject * obj, float time);

	void CreateRope();
	std::vector<Rope> GetRope();
	CollisionResult RopeCollision(GameObject* obj, float time);

	void CreateCrossBar();
	std::vector<CrossBar> GetCrossBar();
	CollisionResult CrossBarCollision(GameObject* obj, float time);

	void CreateStaticObject();
	/*CollisionResult StaticObjectCollision(GameObject* obj, float time);*/

	StaticObject();
	~StaticObject();
};

#endif // !_STATICOBJECT_H_



