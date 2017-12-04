#include "AladdinCharacter.h"

AladdinCharacter::AladdinCharacter()
{
	_id = PLAYER;
}

AladdinCharacter::~AladdinCharacter()
{
}

AladdinCharacter* AladdinCharacter::_instance = 0;

AladdinCharacter* AladdinCharacter::getInstance()
{
	if (!AladdinCharacter::_instance)
	{
		AladdinCharacter::_instance = new AladdinCharacter();
	}
	return AladdinCharacter::_instance;
}

void AladdinCharacter::Init(HINSTANCE hInstance, HWND hWnd)
{
	this->_hInstance = hInstance;
	this->_hWnd = hWnd;
	this->_id = PLAYER;
	this->_currentAction = STAND;
	this->_direct = RIGHT;
	this->_position = D3DXVECTOR3(100, WORLD_BASE_Y, 0);
	this->_rectBound = GetRect();
	this->_vx = this->_vy = 0;
	this->_ax = this->_ay = 0;

	this->_isFalling = false;
	this->_isJumping = false;
	this->_isStoping = false;
	this->_isClimbingY = false;
	this->_isClimbingX = false;

	this->_isPressKeyRight = false;
	this->_isPressKeyLeft = false;
	this->_isPressKeyDown = false;
	this->_isPressKeyUp = false;

	this->_listAction = new Animation[28];
	this->InitKeyBoard(hInstance, hWnd);

	SetListAction(); //Set image for action
}

void AladdinCharacter::UpdatePosition(float time)
{
	if (this->_isStoping)
	{
		this->_ax = -(this->_direct * GRAVITY);
	}

	this->_dx = (this->_vx + this->_ax) * time;
	this->_dy = (this->_vy + this->_ay) * time;

	this->_position.x += this->_dx;
	this->_position.y += this->_dy;
}

//CollisionResult AladdinCharacter::AladdinCollision(GameObject * obj, float time)
//{
//	CollisionResult result;
//
//	result = Collision::SweptAABB(obj->GetRect(), D3DXVECTOR2(obj->GetVx(), obj->GetVy()),
//		this->_rectBound, D3DXVECTOR2(this->GetVx(), this->GetVy()), time);
//}

void AladdinCharacter::Update(float time)
{
	this->ProcessKeyBoard(_hWnd);
	UpdatePosition(time);
	
	//Position x, y
	if (this->_position.x <= 0)
		this->_position.x = 0;
	if (this->_position.x + this->_width >= WORLD_X)
		this->_position.x = WORLD_X - this->_width;

	if (this->_position.y  <= WORLD_BASE_Y)
	this->_position.y = WORLD_BASE_Y;
	if (this->_position.y + this->_height >= WORLD_Y)
	this->_position.y = WORLD_Y - this->_height;

	

	#pragma region Update apple
	if (_myApple)
	{
		if (_myApple->_isDead)
		{
			free(_myApple);
			_myApple = nullptr;
		}
		else
			_myApple->Update(time);
	}
	#pragma endregion 

	switch (this->_currentAction)
	{
	case STAND:
		break;
	
	case STAND_THROW:
	#pragma region Hoan thanh xong trang thai attack hoac throw
		if (_listAction[_currentAction].GetIndex() == 4)
		{
			CreateApple();
		}
	case STAND_ATTACK:
		if (_listAction[_currentAction].GetIndex() == (_listAction[_currentAction].GetTotalFrame() - 1))
		{
			Stand();
		}
		break;
	#pragma endregion

	case LOOK_UP:
		_camY += 2;
		if (_camY >= Camera::getInstance()->GetPosition().y + 30)
			_camY = Camera::getInstance()->GetPosition().y + 30;
		Camera::getInstance()->SetPositionY(_camY);
	case SIT:
		if (_listAction[_currentAction].GetIndex() == (_listAction[_currentAction].GetTotalFrame() - 1))
			_listAction[_currentAction].SetIndex(_listAction[_currentAction].GetIndex() - 1);
		break;

	case LOOK_UP_ATTACK:
		Camera::getInstance()->SetPositionY(_camY);
		if (_listAction[_currentAction].GetIndex() == (_listAction[_currentAction].GetTotalFrame() - 1))
		{
			if (_isPressKeyUp) //Neu van giu phim down
			{
				LookUp();
				_listAction[_currentAction].SetIndex(_listAction[_currentAction].GetTotalFrame() - 1);
			}
			else
				Stand();
		}
		break;

	case SIT_THROW:
		if (_listAction[_currentAction].GetIndex() == 5)
		{
			CreateApple();
		}
	case SIT_ATTACK:
	#pragma region Hoan thanh xong trang thai attack hoac throw
		if (_listAction[_currentAction].GetIndex() == (_listAction[_currentAction].GetTotalFrame() - 1))
		{
			if (_isPressKeyDown) //Neu van giu phim down
			{
				Sit();
				_listAction[_currentAction].SetIndex(_listAction[_currentAction].GetTotalFrame() - 2);
			}
			else
				Stand();
		}
		break;
	#pragma endregion


	case RUN_THROW:
		if (_listAction[_currentAction].GetIndex() == 4)
		{
			CreateApple();
		}
	case RUN_ATTACK:
	#pragma region Hoan thanh xong trang thai attack hoac throw
		if (_listAction[_currentAction].GetIndex() == (_listAction[_currentAction].GetTotalFrame() - 1))
		{
			if (_isPressKeyRight || _isPressKeyLeft) //Neu van giu phim down
			{
				Run();
			}
			else
				Stand();
		}
		this->_runCount += 1;
		break;
	#pragma endregion
	case RUN:
		if (_listAction[_currentAction].GetIndex() == (_listAction[_currentAction].GetTotalFrame() - 1))
			_listAction[_currentAction].SetIndex(4);
		this->_runCount += 1;
		break;
	case STOP_RUN:
	#pragma region Thuc hien animation STOP_RUN
		if (_listAction[_currentAction].GetIndex() == 4)
		{
			_ax = 0;
			_vx = 0;
		}
		if(_listAction[_currentAction].GetIndex() == (_listAction[_currentAction].GetTotalFrame() - 1))
		{
			Stand();
		}
		break;
	#pragma endregion

	case JUMP_THROW:
		if (_listAction[_currentAction].GetIndex() == 3)
		{
			CreateApple();
		}
	case JUMP:
		if (_listAction[_currentAction].GetIndex() == 5 && _vy > 0)
			_listAction[_currentAction].SetIndex(_listAction[_currentAction].GetIndex() - 1);
	case RUN_JUMP:
	case JUMP_ATTACK:
	case FALLING:
	#pragma region Kiem tra velocity, pos khi jump

		if (_isFalling) //Fall down
		{
			_ay -= GRAVITY;
			
		}
		else if (!_isFalling && _isJumping) //Fly up
		{
			_ay -= GRAVITY;
			_vy = VELOCITY_Y;
			if (_vy + _ay <= 0)
			{
				_vy = 0;
				_ay = 0;
				_isFalling = true;
			}
		}

		if (_isPressKeyRight || _isPressKeyLeft)
			_vx = _direct * VELOCITY_X;
		else
			_vx = 0;

		if (_position.y <= WORLD_BASE_Y && _vy <= 0)
		{
			
			_isJumping = false;
			_isFalling = false;

			if (_isPressKeyLeft || _isPressKeyRight)
			{
				_currentAction = RUN;
				_vy = 0;
				_vx = _direct * VELOCITY_X;
				
			}
			else
			{
				Stand();
				
			}
		}
		
		break;
	#pragma endregion

	case CLIMB_Y:
	#pragma region Kiem tra va cham/leo day Y
		if (!_isPressKeyDown && !_isPressKeyUp)
		{
			_listAction[_currentAction].SetIndex(_listAction[_currentAction].GetIndex() - 1);
			_vy = 0;
		}
		break;
	#pragma endregion

	case CLIMB_X:
	case CLIMB_X_STOP:
		break;

	case CLIMB_ATTACK:
	case CLIMB_THROW:
	#pragma region Hoan thanh state chem/nem tao

		if (_listAction[_currentAction].GetIndex() == (_listAction[_currentAction].GetTotalFrame() - 1))
		{
			if (_isClimbingY)
			{
				ClimbY();
			}
			else if(_isClimbingX)
				ClimbXStop();
		}
		break;
	#pragma endregion
	}


	//Update _rect
	UpdateRect();

}

void AladdinCharacter::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
	case DIK_DOWN:
		_isPressKeyDown = 0;
		if (_currentAction == CLIMB_Y || _currentAction == CLIMB_ATTACK || _currentAction == CLIMB_THROW)
		{
			_vy = 0;
			break;
		}
		else if (_currentAction == SIT)
		{
			Stand();
			break;
		}
		break;
	case DIK_UP:
		_isPressKeyUp = 0;
		if (_currentAction == CLIMB_Y || _currentAction == CLIMB_ATTACK || _currentAction == CLIMB_THROW) 
		{
			_vy = 0;
			break;
		}
		else if (_currentAction == LOOK_UP)
		{
			Stand();
			break;
		}
		break;
	case DIK_RIGHT:
		_isPressKeyRight = 0;
		if (_currentAction == CLIMB_X) {
			ClimbXStop();
			break;
		}
		else if (_currentAction == JUMP || _currentAction == RUN_JUMP
			|| _currentAction == JUMP_ATTACK || _currentAction == JUMP_THROW || _currentAction == FALLING)
		{
			_vx = 0;
			break;
		}
		else if ((_currentAction == RUN || _currentAction == RUN_ATTACK || _currentAction == RUN_THROW) 
			&& !_isPressKeyLeft)
		{
			if (_runCount >= 50)
			{
				StopRun();
				_runCount = 0;
			}
			else
				Stand();
				
			break;
		}
		break;
	case DIK_LEFT:
		_isPressKeyLeft = 0;
		if (_currentAction == CLIMB_X) {
			ClimbXStop();
			break;
		}
		else if (_currentAction == JUMP || _currentAction == RUN_JUMP
			|| _currentAction == JUMP_ATTACK || _currentAction == JUMP_THROW || _currentAction == FALLING)
		{
			_vx = 0;
			break;
		}
		else if (_currentAction == RUN && !_isPressKeyRight)
		{
			if (_runCount >= 50)
			{
				StopRun();
				_runCount = 0;
			}
			else
				Stand();

			break;
		}
		break;
	case DIK_D:
		break;
	case DIK_A:
		break;
	case DIK_S:
		break;
	}
}

void AladdinCharacter::OnKeyDown(int keyCode){
	switch (keyCode)
	{
	case DIK_DOWN:
		_isPressKeyDown = 1;
		if (_currentAction == CLIMB_Y) {
			_vy = -VELOCITY_Y;
			break;
		}
		else if (_currentAction == CLIMB_X || _currentAction == CLIMB_X_STOP) {
			Falling();
			break;
		}
		else if (_currentAction == STAND)
		{
			Sit();
			break;
		}
		break;
	case DIK_UP:
		_isPressKeyUp = 1;
		if (_currentAction == CLIMB_Y) {
			_vy = VELOCITY_Y;
			break;
		}
		else if (_currentAction == STAND)
		{
			_camY = Camera::getInstance()->GetPosition().y;
			LookUp();
			break;
		}
		break;
	case DIK_RIGHT:
		_isPressKeyRight = 1;
		if (_isPressKeyLeft || _currentAction == STOP_RUN)
			break;
		_direct = RIGHT;
		if (_isClimbingX && (_currentAction == CLIMB_X || 
			_currentAction == CLIMB_X_STOP || _currentAction == CLIMB_ATTACK || _currentAction == CLIMB_THROW)) 
		{
			ClimbX();
			break;
		}
		else if (_currentAction == STAND)
		{
			Run();
			break;
		}
		break;
	case DIK_LEFT:
		_isPressKeyLeft = 1;
		if (_isPressKeyRight || _currentAction == STOP_RUN)
			break;
		_direct = LEFT;
		if (_isClimbingX == true && (_currentAction == CLIMB_X ||
			_currentAction == CLIMB_X_STOP || _currentAction == CLIMB_ATTACK || _currentAction == CLIMB_THROW)) {
			ClimbX();
			break;
		}
		else if (_currentAction == STAND)
		{
			Run();
			break;
		}
		break;
	case DIK_D:
		if (_currentAction == STAND)
		{
			Jump();
			break;
		}
		else if (_currentAction == RUN)
		{
			RunJump();
			break;
		}
		else if (_isClimbingY && (_currentAction == CLIMB_Y ||
			_currentAction == CLIMB_ATTACK || _currentAction == CLIMB_THROW))
		{
			if(_isPressKeyRight)
				_position.x += 5;
			if (_isPressKeyLeft)
				_position.x += -5;
			ClimbJump();
			break;
		}
		break;
	case DIK_A:
		if (_currentAction == SIT)
		{
			SitAttack();
		}
		else if (_currentAction == CLIMB_X_STOP || _currentAction == CLIMB_Y)
		{
			ClimbAttack();
		}
		else if (_currentAction == RUN_JUMP)
		{
			RunJumpAttack();
		}
		else if (_currentAction == STAND)
		{
			StandAttack();
		}
		else if (_currentAction == RUN)
		{
			RunAttack();
		}
		else if (_currentAction == LOOK_UP)
		{
			LookUpAttack();
		}
		break;
	case DIK_S:
		if (_currentAction == SIT)
		{
			SitThrow();
		}
		else if (_currentAction == CLIMB_X_STOP || _currentAction == CLIMB_Y)
		{
			ClimbThrow();
		}
		else if (_currentAction == RUN_JUMP)
		{
			RunJumpThrow();
		}
		else if(_currentAction == STAND)
		{
			StandThrow();
		}
		else if (_currentAction == RUN)
		{
			RunThrow();
		}
		break;
	}
}

void AladdinCharacter::Run()
{
	if (_currentAction == SIT || _currentAction == LOOK_UP || _currentAction == RUN_JUMP || _currentAction == JUMP_ATTACK)
	{
		return;
	}
	else if (_currentAction == JUMP || _currentAction == FALLING)
	{
		_vx = _direct * VELOCITY_X;
		return;
	}

	_isFalling = false;
	_isJumping = false;
	_isClimbingX = false;
	_isClimbingY = false;
	_isStoping = false;

	_currentAction = RUN;
	_vx = _direct * VELOCITY_X;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::RunAttack()
{
	_currentAction = RUN_ATTACK;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::RunThrow()
{
	_currentAction = RUN_THROW;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::StopRun()
{
	_isStoping = true;
	_isFalling = false;
	_isJumping = false;
	_isClimbingX = false;
	_isClimbingY = false;

	_currentAction = STOP_RUN;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::Stand()
{
	_ax = _ay = 0;
	_vx = _vy = 0;

	_isFalling = false;
	_isJumping = false;
	_isClimbingX = false;
	_isClimbingY = false;
	_isStoping = false;

	_currentAction = STAND;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::StandAttack()
{
	_currentAction = STAND_ATTACK;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::StandThrow()
{
	_currentAction = STAND_THROW;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::Sit()
{
	_currentAction = SIT;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::SitAttack()
{
	_currentAction = SIT_ATTACK;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::SitThrow()
{
	_currentAction = SIT_THROW;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::Jump()
{
	_isFalling = false;
	_isJumping = true;
	_isClimbingX = false;
	_isClimbingY = false;
	_isStoping = false;

	_vy = VELOCITY_Y;
	_currentAction = JUMP;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::RunJump() 
{
	_isFalling = false;
	_isJumping = true;
	_isClimbingX = false;
	_isClimbingY = false;
	_isStoping = false;

	_vy = VELOCITY_Y;
	_vx = _direct*VELOCITY_JUMP_X;
	_currentAction = RUN_JUMP;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::RunJumpAttack() 
{
	_currentAction = JUMP_ATTACK;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::RunJumpThrow()
{
	_currentAction = JUMP_THROW;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::Falling()
{
	_isFalling = true;
	_isJumping = false;
	_isClimbingX = false;
	_isClimbingY = false;
	_isStoping = false;
	
	_currentAction = FALLING;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::LookUp()
{
	_currentAction = LOOK_UP;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::LookUpAttack()
{
	_currentAction = LOOK_UP_ATTACK;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::ClimbY()
{
	_isFalling = false;
	_isJumping = false;
	_isClimbingX = false;
	_isClimbingY = true; //
	_isStoping = false;

	_v0 = 0;
	_vx = 0;

	_currentAction = CLIMB_Y;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::ClimbX()
{
	_isFalling = false;
	_isJumping = false;
	_isClimbingX = true; //
 	_isClimbingY = false;
	_isStoping = false;

	_vy = 0;
	_vx = _direct * VELOCITY_X;

	_currentAction = CLIMB_X;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::ClimbXStop()
{
	_isFalling = false;
	_isJumping = false;
	_isClimbingX = true; //
	_isClimbingY = false;
	_isStoping = false;

	_vy = 0;
	_vx = 0;

	_currentAction = CLIMB_X_STOP;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::ClimbAttack()
{
	_currentAction = CLIMB_ATTACK;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::ClimbThrow()
{
	_currentAction = CLIMB_THROW;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::ClimbJump()
{
	_currentAction = CLIMB_JUMP;
	_listAction[_currentAction].SetIndex(0);
}

void AladdinCharacter::CreateApple()
{
	int xApple;
	int yApple;
	float vxApple;
	float vyApple;

	//Toa do ban dau cua apple
	xApple = this->_position.x;
	yApple = this->_position.y + this->_height;

	vxApple = _direct*APPLE_VX;
	vyApple = 0;

	D3DXVECTOR3 posApple = D3DXVECTOR3(xApple, yApple, 0);

	_myApple = new Apple(posApple, vxApple, vyApple);

}

void AladdinCharacter::SetListAction()
{
	std::vector<Rect> _temp;

	//RUN
	_temp.push_back(Rect(117, 83, 167, 120));
	_temp.push_back(Rect(117, 42, 165, 82));
	_temp.push_back(Rect(56, 103, 107, 146));
	_temp.push_back(Rect(0, 0, 58, 55));
	_temp.push_back(Rect(0, 56, 55, 111));
	_temp.push_back(Rect(0, 159, 57, 203));
	_temp.push_back(Rect(59, 189, 112, 230));
	_temp.push_back(Rect(58, 147, 115, 188));
	_temp.push_back(Rect(59, 0, 116, 52));
	_temp.push_back(Rect(0, 112, 54, 158));
	_temp.push_back(Rect(0, 204, 58, 246));
	_temp.push_back(Rect(117, 0, 169, 41));
	_temp.push_back(Rect(116, 121, 170, 155));
	_temp.push_back(Rect(59, 53, 116, 102));
	
	_listAction[0].Create(RUN_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//STOP
	_temp.push_back(Rect(0, 56, 57, 110, D3DXVECTOR3(0, -5, 0)));
	_temp.push_back(Rect(125, 43, 181, 81, D3DXVECTOR3(0, -5, 0)));
	_temp.push_back(Rect(58, 53, 124, 104, D3DXVECTOR3(0, -5, 0)));
	_temp.push_back(Rect(53, 155, 118, 202, D3DXVECTOR3(0, -5, 0)));
	_temp.push_back(Rect(92, 0, 156, 42, D3DXVECTOR3(0, -5, 0)));
	_temp.push_back(Rect(0, 0, 46, 55, D3DXVECTOR3(0, -7, 0)));
	_temp.push_back(Rect(47, 0, 91, 52, D3DXVECTOR3(0, -7, 0)));
	_temp.push_back(Rect(51, 203, 103, 249, D3DXVECTOR3(0, -7, 0)));
	_temp.push_back(Rect(58, 105, 105, 154, D3DXVECTOR3(0, -3, 0)));
	_temp.push_back(Rect(0, 111, 52, 162, D3DXVECTOR3(0, -2, 0)));
	_temp.push_back(Rect(0, 163, 50, 214));
	_temp.push_back(Rect(125, 82, 175, 119));

	_listAction[1].Create(STOP_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();


	//STAND
	_temp.push_back(Rect(0, 540, 50, 577));
	_temp.push_back(Rect(55, 256, 102, 297));
	_temp.push_back(Rect(55, 339, 107, 379));
	_temp.push_back(Rect(55, 0, 110, 44));
	_temp.push_back(Rect(146, 171, 197, 212));
	_temp.push_back(Rect(78, 129, 129, 171));
	_temp.push_back(Rect(55, 45, 108, 89));
	_temp.push_back(Rect(109, 297, 161, 337));
	_temp.push_back(Rect(0, 63, 53, 124));
	_temp.push_back(Rect(0, 0, 54, 62));
	_temp.push_back(Rect(0, 297, 53, 338));
	_temp.push_back(Rect(54, 380, 107, 419));
	_temp.push_back(Rect(0, 578, 53, 614));
	_temp.push_back(Rect(103, 256, 156, 296));
	_temp.push_back(Rect(130, 129, 185, 170));
	_temp.push_back(Rect(0, 125, 73, 168));
	_temp.push_back(Rect(0, 169, 77, 211));
	_temp.push_back(Rect(0, 212, 71, 254));
	_temp.push_back(Rect(111, 0, 173, 42));
	_temp.push_back(Rect(128, 214, 182, 255));
	_temp.push_back(Rect(0, 339, 54, 379));
	_temp.push_back(Rect(109, 338, 162, 377));
	_temp.push_back(Rect(51, 538, 104, 574));
	_temp.push_back(Rect(0, 380, 53, 420));
	_temp.push_back(Rect(72, 214, 127, 255));
	_temp.push_back(Rect(130, 418, 193, 456));
	_temp.push_back(Rect(78, 172, 145, 213));
	_temp.push_back(Rect(109, 86, 167, 128));
	_temp.push_back(Rect(0, 501, 49, 539));
	_temp.push_back(Rect(108, 378, 157, 417));
	_temp.push_back(Rect(80, 420, 129, 459));
	_temp.push_back(Rect(122, 460, 183, 498));
	_temp.push_back(Rect(54, 461, 121, 499));
	_temp.push_back(Rect(50, 501, 124, 537));
	_temp.push_back(Rect(0, 421, 79, 460));
	_temp.push_back(Rect(111, 43, 173, 85));
	_temp.push_back(Rect(0, 255, 54, 296));
	_temp.push_back(Rect(54, 298, 108, 338));
	_temp.push_back(Rect(0, 461, 53, 500));

	_listAction[2].Create(STAND_PATH, _temp.size(), _temp, 0.1f, RIGHT);
	_temp.clear();

	//STAND_ATTACK
	_temp.push_back(Rect(75, 104, 125, 141));
	_temp.push_back(Rect(0, 150, 51, 195));
	_temp.push_back(Rect(53, 0, 115, 51));
	_temp.push_back(Rect(0, 104, 74, 149));
	_temp.push_back(Rect(0, 0, 52, 82));
	_temp.push_back(Rect(53, 52, 106, 103));

	_listAction[3].Create(STAND_ATTACK_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//STAND_THROW
	_temp.push_back(Rect(0, 177, 50, 214));
	_temp.push_back(Rect(64, 0, 120, 43));
	_temp.push_back(Rect(64, 44, 123, 85));
	_temp.push_back(Rect(0, 100, 58, 138));
	_temp.push_back(Rect(0, 0, 63, 52));
	_temp.push_back(Rect(0, 53, 60, 99));
	_temp.push_back(Rect(0, 139, 58, 176));
	_temp.push_back(Rect(61, 86, 113, 125));

	_listAction[4].Create(STAND_THROW_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//SIT
	_temp.push_back(Rect(36, 49, 86, 86));
	_temp.push_back(Rect(72, 0, 121, 41));
	_temp.push_back(Rect(31, 0, 71, 48));
	_temp.push_back(Rect(0, 0, 30, 54));
	_temp.push_back(Rect(0, 55, 35, 108));

	_listAction[5].Create(SIT_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//SIT ATTACK
	_temp.push_back(Rect(69, 72, 102, 119));
	_temp.push_back(Rect(0, 93, 31, 138));
	_temp.push_back(Rect(69, 0, 102, 71));
	_temp.push_back(Rect(0, 0, 34, 92));
	_temp.push_back(Rect(35, 0, 68, 84));

	_listAction[6].Create(SIT_ATTACK_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//SIT THROW
	_temp.push_back(Rect(38, 58, 73, 111));
	_temp.push_back(Rect(38, 0, 75, 57));
	_temp.push_back(Rect(0, 150, 44, 187));
	_temp.push_back(Rect(0, 112, 48, 149));
	_temp.push_back(Rect(74, 58, 118, 107));
	_temp.push_back(Rect(0, 0, 37, 82));
	_temp.push_back(Rect(76, 0, 113, 57));

	_listAction[7].Create(SIT_THROW_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//JUMP
	_temp.push_back(Rect(130, 106, 180, 143));
	_temp.push_back(Rect(115, 0, 162, 41));
	_temp.push_back(Rect(0, 60, 44, 119));
	_temp.push_back(Rect(0, 120, 62, 172));
	_temp.push_back(Rect(45, 55, 106, 109));
	_temp.push_back(Rect(45, 0, 114, 54));
	_temp.push_back(Rect(0, 173, 74, 224));
	_temp.push_back(Rect(63, 110, 129, 148));
	_temp.push_back(Rect(75, 187, 138, 223));
	_temp.push_back(Rect(0, 225, 79, 260));
	_temp.push_back(Rect(0, 261, 93, 295));
	_temp.push_back(Rect(107, 55, 192, 105));
	_temp.push_back(Rect(0, 0, 44, 59));
	_temp.push_back(Rect(75, 149, 125, 186));

	_listAction[8].Create(JUMP_PATH, _temp.size(), _temp, 0.1f, RIGHT);
	_temp.clear();

	//LOOK UP
	_temp.push_back(Rect(60, 39, 110, 76));
	_temp.push_back(Rect(59, 0, 112, 38));
	_temp.push_back(Rect(0, 50, 59, 95));
	_temp.push_back(Rect(0, 0, 58, 49));

	_listAction[9].Create(LOOK_UP_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//CLIMB Y
	_temp.push_back(Rect(0, 151, 86, 180));
	_temp.push_back(Rect(0, 211, 89, 239));
	_temp.push_back(Rect(64, 58, 138, 86));
	_temp.push_back(Rect(0, 0, 62, 42));
	_temp.push_back(Rect(0, 119, 76, 150));
	_temp.push_back(Rect(0, 181, 86, 210));
	_temp.push_back(Rect(63, 29, 142, 57));
	_temp.push_back(Rect(0, 86, 63, 118));
	_temp.push_back(Rect(0, 43, 62, 85));
	_temp.push_back(Rect(63, 0, 144, 28));


	_listAction[10].Create(CLIMB_Y_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//FALLING
	_temp.push_back(Rect(130, 106, 180, 143));
	_temp.push_back(Rect(115, 0, 162, 41));
	_temp.push_back(Rect(0, 60, 44, 119));
	_temp.push_back(Rect(0, 120, 62, 172));
	_temp.push_back(Rect(45, 55, 106, 109));
	_temp.push_back(Rect(45, 0, 114, 54));
	_temp.push_back(Rect(0, 173, 74, 224));
	_temp.push_back(Rect(63, 110, 129, 148));
	_temp.push_back(Rect(75, 187, 138, 223));
	_temp.push_back(Rect(0, 225, 79, 260));
	_temp.push_back(Rect(0, 261, 93, 295));
	_temp.push_back(Rect(107, 55, 192, 105));
	_temp.push_back(Rect(0, 0, 44, 59));
	_temp.push_back(Rect(75, 149, 125, 186));

	_listAction[11].Create(FALLING_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//RUN JUMP
	_temp.push_back(Rect(77, 159, 127, 196));
	_temp.push_back(Rect(59, 117, 101, 158));
	_temp.push_back(Rect(0, 175, 76, 220));
	_temp.push_back(Rect(54, 59, 111, 116));
	_temp.push_back(Rect(49, 0, 91, 58));
	_temp.push_back(Rect(0, 0, 48, 61));
	_temp.push_back(Rect(0, 62, 53, 120));
	_temp.push_back(Rect(0, 121, 58, 174));

	_listAction[12].Create(RUN_JUMP_PATH, _temp.size(), _temp, 0.12f, RIGHT);
	_temp.clear();

	//JUMP THROW
	_temp.push_back(Rect(56, 53, 111, 102));
	_temp.push_back(Rect(0, 115, 52, 158));
	_temp.push_back(Rect(56, 103, 109, 142));
	_temp.push_back(Rect(0, 59, 55, 114));
	_temp.push_back(Rect(54, 0, 107, 52));
	_temp.push_back(Rect(0, 159, 52, 199));
	_temp.push_back(Rect(0, 0, 53, 58));

	_listAction[13].Create(JUMP_THROW_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//JUMP ATTACK
	_temp.push_back(Rect(48, 54, 104, 106));
	_temp.push_back(Rect(0, 160, 52, 210));
	_temp.push_back(Rect(57, 107, 123, 154));
	_temp.push_back(Rect(0, 107, 56, 159));
	_temp.push_back(Rect(0, 0, 47, 83));
	_temp.push_back(Rect(57, 155, 112, 202));
	_temp.push_back(Rect(48, 0, 106, 53));

	_listAction[14].Create(JUMP_THROW_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//CLIMBX
	_temp.push_back(Rect(78, 178, 156, 212));
	_temp.push_back(Rect(81, 0, 162, 47));
	_temp.push_back(Rect(0, 0, 80, 57));
	_temp.push_back(Rect(0, 166, 77, 216));
	_temp.push_back(Rect(78, 93, 161, 136));
	_temp.push_back(Rect(0, 217, 83, 253));
	_temp.push_back(Rect(81, 48, 161, 92));
	_temp.push_back(Rect(0, 113, 77, 165));
	_temp.push_back(Rect(0, 58, 72, 112));
	_temp.push_back(Rect(78, 137, 156, 177));

	_listAction[15].Create(CLIMB_X_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//CLIMB ATTACK
	_temp.push_back(Rect(92, 105, 179, 153));
	_temp.push_back(Rect(90, 0, 179, 52));
	_temp.push_back(Rect(0, 73, 91, 134));
	_temp.push_back(Rect(92, 53, 182, 104));
	_temp.push_back(Rect(0, 197, 89, 251));
	_temp.push_back(Rect(0, 135, 91, 196));
	_temp.push_back(Rect(0, 0, 89, 72));
	_temp.push_back(Rect(92, 154, 179, 202));

	_listAction[16].Create(CLIMB_ATTACK_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//CLIMB THROW
	_temp.push_back(Rect(0, 152, 87, 189));
	_temp.push_back(Rect(0, 110, 87, 151));
	_temp.push_back(Rect(0, 58, 88, 109));
	_temp.push_back(Rect(0, 190, 89, 221));
	_temp.push_back(Rect(0, 0, 89, 57));
	_temp.push_back(Rect(0, 222, 89, 251));

	_listAction[17].Create(CLIMB_THROW_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//CLIMB X STOP
	_temp.push_back(Rect(0, 181, 88, 219));
	_temp.push_back(Rect(0, 140, 88, 180));
	_temp.push_back(Rect(0, 98, 88, 139));
	_temp.push_back(Rect(0, 50, 87, 97));
	_temp.push_back(Rect(0, 0, 88, 49));

	_listAction[18].Create(CLIMB_X_STOP_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//WAIT1 
	_temp.push_back(Rect(55, 0, 110, 44));
	_temp.push_back(Rect(0, 63, 53, 124));
	_temp.push_back(Rect(0, 0, 54, 62));
	_temp.push_back(Rect(78, 149, 131, 190));
	_temp.push_back(Rect(126, 207, 179, 246));
	_temp.push_back(Rect(0, 294, 53, 330));
	_temp.push_back(Rect(0, 254, 53, 293));
	_temp.push_back(Rect(133, 126, 186, 166));
	_temp.push_back(Rect(128, 43, 183, 84));
	_temp.push_back(Rect(0, 211, 67, 253));
	_temp.push_back(Rect(54, 63, 127, 106));
	_temp.push_back(Rect(0, 125, 77, 167));
	_temp.push_back(Rect(0, 168, 71, 210));
	_temp.push_back(Rect(111, 0, 173, 42));
	_temp.push_back(Rect(78, 107, 132, 148));
	_temp.push_back(Rect(133, 85, 187, 125));
	_temp.push_back(Rect(72, 191, 125, 230));
	_temp.push_back(Rect(132, 167, 185, 206));

	_listAction[19].Create(WAIT1_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//WAIT2
	_temp.push_back(Rect(54, 128, 107, 167));
	_temp.push_back(Rect(0, 286, 53, 322));
	_temp.push_back(Rect(0, 128, 53, 168));
	_temp.push_back(Rect(63, 0, 118, 41));
	_temp.push_back(Rect(108, 126, 171, 164));
	_temp.push_back(Rect(0, 86, 67, 127));
	_temp.push_back(Rect(0, 43, 58, 85));
	_temp.push_back(Rect(108, 207, 157, 245));
	_temp.push_back(Rect(119, 0, 168, 39));
	_temp.push_back(Rect(114, 42, 163, 81));
	_temp.push_back(Rect(142, 165, 196, 203));
	_temp.push_back(Rect(80, 168, 141, 206));
	_temp.push_back(Rect(123, 82, 190, 120));
	_temp.push_back(Rect(0, 249, 74, 285));
	_temp.push_back(Rect(0, 169, 79, 208));
	_temp.push_back(Rect(0, 0, 62, 42));
	_temp.push_back(Rect(59, 43, 113, 84));
	_temp.push_back(Rect(68, 85, 122, 125));
	_temp.push_back(Rect(0, 209, 53, 248));
	_temp.push_back(Rect(54, 209, 107, 248));

	_listAction[20].Create(WAIT2_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//LOOK UP ATTACK
	_temp.push_back(Rect(141, 98, 191, 135));
	_temp.push_back(Rect(87, 103, 140, 145));
	_temp.push_back(Rect(87, 146, 147, 184));
	_temp.push_back(Rect(0, 75, 61, 140));
	_temp.push_back(Rect(72, 55, 130, 102));
	_temp.push_back(Rect(131, 50, 185, 97));
	_temp.push_back(Rect(72, 0, 120, 54));
	_temp.push_back(Rect(0, 0, 71, 74));
	_temp.push_back(Rect(0, 141, 86, 195));
	_temp.push_back(Rect(121, 0, 192, 49));
	_temp.push_back(Rect(0, 196, 67, 247));

	_listAction[21].Create(LOOK_UP_ATTACK_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//PUSH_WALL 
	_temp.push_back(Rect(91, 190, 141, 227));
	_temp.push_back(Rect(91, 133, 137, 189));
	_temp.push_back(Rect(90, 67, 134, 132));
	_temp.push_back(Rect(45, 154, 90, 224));
	_temp.push_back(Rect(45, 0, 89, 77));
	_temp.push_back(Rect(0, 158, 44, 230));
	_temp.push_back(Rect(90, 0, 134, 66));
	_temp.push_back(Rect(0, 82, 44, 157));
	_temp.push_back(Rect(0, 0, 44, 81));
	_temp.push_back(Rect(45, 78, 89, 153));

	_listAction[22].Create(PUSH_WALL_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//ROLLING
	_temp.push_back(Rect(0, 0, 44, 59));
	_temp.push_back(Rect(0, 60, 54, 109));
	_temp.push_back(Rect(39, 157, 84, 198));
	_temp.push_back(Rect(0, 110, 43, 156));
	_temp.push_back(Rect(55, 50, 97, 98));
	_temp.push_back(Rect(45, 0, 86, 49));
	_temp.push_back(Rect(87, 0, 123, 46));
	_temp.push_back(Rect(0, 157, 38, 200));
	_temp.push_back(Rect(44, 110, 86, 153));

	_listAction[23].Create(ROLLING_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//RUN_ATTACK
	_temp.push_back(Rect(61, 112, 113, 147));
	_temp.push_back(Rect(0, 74, 60, 125));
	_temp.push_back(Rect(61, 61, 114, 111));
	_temp.push_back(Rect(0, 126, 60, 174));
	_temp.push_back(Rect(0, 0, 51, 73));
	_temp.push_back(Rect(52, 0, 102, 60));

	_listAction[24].Create(RUN_ATTACK_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//RUN_THROW
	_temp.push_back(Rect(0, 107, 53, 144));
	_temp.push_back(Rect(62, 0, 114, 49));
	_temp.push_back(Rect(62, 50, 114, 98));
	_temp.push_back(Rect(0, 0, 61, 56));
	_temp.push_back(Rect(0, 57, 61, 106));
	_temp.push_back(Rect(0, 145, 55, 180));

	_listAction[25].Create(RUN_THROW_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//DIE
	_temp.push_back(Rect(0, 0, 48, 80));
	_temp.push_back(Rect(49, 0, 100, 61));
	_temp.push_back(Rect(0, 81, 58, 126));
	_temp.push_back(Rect(59, 62, 117, 107));
	_temp.push_back(Rect(52, 191, 102, 230));
	_temp.push_back(Rect(57, 150, 108, 190));
	_temp.push_back(Rect(118, 77, 169, 112));
	_temp.push_back(Rect(118, 40, 169, 76));
	_temp.push_back(Rect(101, 0, 150, 39));
	_temp.push_back(Rect(0, 127, 56, 171));
	_temp.push_back(Rect(59, 108, 112, 149));
	_temp.push_back(Rect(0, 213, 50, 252));
	_temp.push_back(Rect(0, 172, 51, 212));

	_listAction[26].Create(DIE_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();

	//CLIMB_JUMP
	_temp.push_back(Rect(110, 0, 183, 34));
	_temp.push_back(Rect(110, 35, 187, 60));
	_temp.push_back(Rect(0, 214, 71, 250));
	_temp.push_back(Rect(42, 60, 106, 108));
	_temp.push_back(Rect(0, 0, 54, 59));
	_temp.push_back(Rect(0, 60, 41, 119));
	_temp.push_back(Rect(55, 0, 109, 52));
	_temp.push_back(Rect(0, 120, 67, 167));
	_temp.push_back(Rect(0, 168, 75, 213));

	_listAction[27].Create(CLIMB_JUMP_PATH, _temp.size(), _temp, 0.07f, RIGHT);
	_temp.clear();
}

void AladdinCharacter::Draw(float time)
{
	this->_transform._positionInViewport = this->GetPositionInViewport();
	D3DXVECTOR3 cameraPosition = Viewport::getInstance()->getViewPortPositon(Camera::getInstance()->GetPosition());
	this->_transform._translation = D3DXVECTOR2(-cameraPosition.x, -cameraPosition.y);

	this->_listAction[_currentAction].Draw(_transform._positionInViewport, this->_direct, time, D3DXVECTOR2(2, 2.5), _transform._translation);

	if (_myApple)
		_myApple->Draw(time);
}
