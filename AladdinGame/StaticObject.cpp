#include "StaticObject.h"


StaticObject* StaticObject::_instance = NULL;
StaticObject * StaticObject::getInstance()
{
	if (StaticObject::_instance == NULL)
	{
		StaticObject::_instance = new StaticObject();
	}
	return StaticObject::_instance;
}

void StaticObject::CreateGround()
{
	this->_listGround.push_back(Ground(D3DXVECTOR3(1150, 0, 0), 2300, 150));
	this->_listGround.push_back(Ground(D3DXVECTOR3(3620, 0, 0), 7242, 75));
}

std::vector<Ground> StaticObject::GetGround()
{
	return this->_listGround;
}

CollisionResult StaticObject::GroundCollision(GameObject * obj, float time)
{
	CollisionResult result;
	for (int i = 0; i < _listGround.size(); i++)
	{
		result = Collision::SweptAABB(obj->GetRect(), D3DXVECTOR2(obj->GetVx(), obj->GetVy()),
			this->_listGround.at(i).GetRect(), D3DXVECTOR2(this->_listGround.at(i).GetVx(), this->_listGround.at(i).GetVy()), time);
		if (result._isCollision)
			return result;
	}
	return result;
}

void StaticObject::CreateRope()
{
	this->_listRope.push_back(Rope(D3DXVECTOR3(4180, 165, 0), 15, 775));
	this->_listRope.push_back(Rope(D3DXVECTOR3(9430, 285, 0), 15, 575));
}

std::vector<Rope> StaticObject::GetRope()
{
	return this->_listRope;
}

CollisionResult StaticObject::RopeCollision(GameObject * obj, float time)
{
	CollisionResult result;
	for (int i = 0; i < _listRope.size(); i++)
	{
		result = Collision::SweptAABB(obj->GetRect(), D3DXVECTOR2(obj->GetVx(), obj->GetVy()),
			this->_listRope.at(i).GetRect(), D3DXVECTOR2(this->_listRope.at(i).GetVx(), this->_listRope.at(i).GetVy()), time);
		if (result._isCollision)
		{
			result._indexObject = i;
			return result;
		}
			
	}
	return result;
}

void StaticObject::CreateCrossBar()
{
	this->_listCrossBar.push_back(CrossBar(D3DXVECTOR3(9120, 875, 0), 820, 20));
}

std::vector<CrossBar> StaticObject::GetCrossBar()
{
	return this->_listCrossBar;
}

CollisionResult StaticObject::CrossBarCollision(GameObject * obj, float time)
{
	CollisionResult result;
	for (int i = 0; i < _listCrossBar.size(); i++)
	{
		result = Collision::SweptAABB(obj->GetRect(), D3DXVECTOR2(obj->GetVx(), obj->GetVy()),
			this->_listCrossBar.at(i).GetRect(), D3DXVECTOR2(this->_listCrossBar.at(i).GetVx(), this->_listCrossBar.at(i).GetVy()), time);
		if (result._isCollision)
			return result;
	}
	return result;
}

void StaticObject::CreateStaticObject()
{
	CreateGround();
	CreateRope();
	CreateCrossBar();
}

//CollisionResult StaticObject::StaticObjectCollision(GameObject * obj, float time)
//{
//	CollisionResult result;
//	return result;
//}

StaticObject::StaticObject()
{
}

StaticObject::~StaticObject()
{
}
