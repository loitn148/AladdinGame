#include "Camera.h"


Camera* Camera::_instance = NULL;
Camera* Camera::getInstance()
{
	if (!Camera::_instance)
	{
		Camera::_instance = new Camera();
	}
	return Camera::_instance;
}
void Camera::CameraOnWORLD()
{
	D3DXVECTOR3 tl_position = this->_position;
	D3DXVECTOR3 tr_position = D3DXVECTOR3(this->_position.x + this->_width, this->_position.y, 0);
	D3DXVECTOR3 br_position = D3DXVECTOR3(this->_position.x + this->_width, this->_position.y - this->_height, 0);
	D3DXVECTOR3 bl_position = D3DXVECTOR3(this->_position.x, this->_position.y - this->_height, 0);

	//TopLeft
	if (tl_position.x < 0)
		this->_position.x = 0;
	if (tl_position.y > WORLD_Y)
		this->_position.y = WORLD_Y;

	//TopRight
	if (tr_position.x > WORLD_X)
		this->_position.x = WORLD_X - this->_width;
	if (tr_position.y > WORLD_Y)
		this->_position.y = WORLD_Y;

	//BottomRight
	if (br_position.x > WORLD_X)
		this->_position.x = WORLD_X - this->_width;
	if (br_position.y < 0)
		this->_position.y = this->_height;

	//BottomLeft
	if (bl_position.x < 0)
		this->_position.x = 0;
	if (bl_position.y < 0)
		this->_position.y = this->_height;
}
Camera::Camera()
{
	this->_position = D3DXVECTOR3(0, WND_HEIGHT, 0);
	_width = WND_WIDTH;
	_height = WND_HEIGHT;
}

Camera::~Camera(){}


void Camera::Update(AladdinCharacter* aladdin)
{	
	D3DXVECTOR3 aladdinPos = aladdin->GetPosition();

	float halfWidth = (float) _width / 2;
	float halfHeight = (float) _height / 2;

	float cameraXCenter = _position.x + halfWidth;
	float cameraYCenter = _position.y - halfHeight;

	this->_vx = 0;
	this->_vy = 0;

	//Left
	if (aladdinPos.x < cameraXCenter - DELTA_CAMERA)
		this->_vx = aladdinPos.x - cameraXCenter + DELTA_CAMERA;

	//Right
	if (aladdinPos.x > cameraXCenter + DELTA_CAMERA)
		this->_vx = aladdinPos.x - cameraXCenter - DELTA_CAMERA;

	//Top
	if (aladdinPos.y < cameraYCenter - DELTA_CAMERA)
		this->_vy = aladdinPos.y - cameraYCenter + DELTA_CAMERA;

	//Bottom
	if (aladdinPos.y > cameraYCenter + DELTA_CAMERA)
		this->_vy = aladdinPos.y - cameraYCenter - DELTA_CAMERA;


	this->_position.x += _vx;
	this->_position.y += _vy;

	CameraOnWORLD();
}

void Camera::SetPosition(D3DXVECTOR3 position)
{
	this->_position = position;
}

void Camera::SetPositionY(int y)
{
	this->_position.y = y;
}

RECT Camera::GetRect()
{
	RECT r;
	r.left = this->_position.x;
	r.top = this->_position.y;
	r.right = r.left + _width;
	r.bottom = r.top + _height;
	return r;
}

D3DXVECTOR3 Camera::GetPosition()
{
	return this->_position;
}

void Camera::Create(D3DXVECTOR3 position, int width, int height)
{
	this->_position = position;
	this->_width = width;
	this->_height = height;
}
