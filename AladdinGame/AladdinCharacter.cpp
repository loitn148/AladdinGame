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
	this->_position = D3DXVECTOR3(100, WORLD_BASE_Y + this->_height, 0);
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

	this->_listAction = new Animation[19];
	this->InitKeyBoard(hInstance, hWnd);

	SetListAction(); //Set image for action
}

void AladdinCharacter::UpdatePosition(float time)
{
	//if (this->_isFalling) //Fall down
	//{
	//	this->_vy = 0;
	//	this->_ay += GRAVITY;
	//}
	//else if (!this->_isFalling && this->_isJumping) //Fly up
	//{
	//	this->_ay += GRAVITY;
	//	this->_vy = this->_v0;
	//	if (this->_vy + this->_ay >= 0)
	//		this->_isFalling = true;
	//}
	
	if (this->_isStoping)
	{
		this->_ax = -(this->_direct * GRAVITY);
	}

	this->_dx = (this->_vx + this->_ax) * time;
	this->_dy = (this->_vy + this->_ay) * time;

	this->_position.x += this->_dx;
	this->_position.y += this->_dy;
}

void AladdinCharacter::Update(float time)
{
	this->ProcessKeyBoard(_hWnd);
	UpdatePosition(time);

	//Position x, y
	if (this->_position.x <= 0)
		this->_position.x = 0;
	if (this->_position.x + this->_width >= WORLD_X)
		this->_position.x = WORLD_X - this->_width;

	if (this->_position.y  <= WORLD_BASE_Y + this->_height)
		this->_position.y = WORLD_BASE_Y + this->_height;
	if (this->_position.y >= WORLD_Y)
		this->_position.y = WORLD_Y;

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
	case STAND_ATTACK:
	case STAND_THROW:
	#pragma region Hoan thanh xong trang thai attack hoac throw
		if (_listAction[_currentAction].GetIndex() == (_listAction[_currentAction].GetTotalFrame() - 1))
		{
			Stand();
		}
		break;
	#pragma endregion

	case LOOK_UP:
		_camY += 2;
		if (_camY >= Camera::getInstance()->GetPosition().y + 20)
			_camY = Camera::getInstance()->GetPosition().y + 20;
		Camera::getInstance()->SetPositionY(_camY);
	case SIT:
	#pragma region Giu frame cuoi neu dang ngoi hoac nhin len
		if (_listAction[_currentAction].GetIndex() == (_listAction[_currentAction].GetTotalFrame() - 1))
			_listAction[_currentAction].SetIndex(_listAction[_currentAction].GetIndex() - 1);
		break;
	#pragma endregion

	case SIT_ATTACK:
	case SIT_THROW:
	#pragma region Hoan thanh xong trang thai attack hoac throw
		if (_listAction[_currentAction].GetIndex() == (_listAction[_currentAction].GetTotalFrame() - 1))
		{
			if (_isPressKeyDown) //Neu van giu phim down
			{
				Sit();
			}
			else
				Stand();
		}
		break;
	#pragma endregion

	case RUN:
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

	case JUMP:
	case RUN_JUMP:
	case JUMP_ATTACK:
	case JUMP_THROW:
	case FALLING:
	#pragma region Kiem tra velocity, pos khi jump

		if (_isFalling) //Fall down
		{
			_vy = 0;
			_ay -= GRAVITY;
		}
		else if (!_isFalling && _isJumping) //Fly up
		{
			_ay -= GRAVITY;
			_vy = VELOCITY_Y;
			if (_vy + _ay <= 0)
				_isFalling = true;
		}

		if (_listAction[_currentAction].GetIndex() == (_listAction[_currentAction].GetTotalFrame() - 1))
		{
			_listAction[_currentAction].SetIndex(_listAction[_currentAction].GetIndex() - 1);
		}

		if (_isPressKeyRight || _isPressKeyLeft)
			_vx = _direct * VELOCITY_X;
		else
			_vx = 0;

		//Kiem tra toa do y = WORLD_BASE_Y?
		if ((_position.y == WORLD_BASE_Y + _height) && _vy == 0)
		{
			_isJumping = false;
			_isFalling = false;

			if (_isPressKeyLeft || _isPressKeyRight)
			{
				_currentAction = RUN;
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
		else if (_currentAction == RUN)
		{
			StopRun();
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
		else if (_currentAction == RUN)
		{
			StopRun();
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
		_direct = RIGHT;
		if (_isClimbingY == true && (_currentAction == CLIMB_Y ||
			_currentAction == CLIMB_ATTACK || _currentAction == CLIMB_THROW))
		{
			break;
		}
		else if (_isClimbingX == true && (_currentAction == CLIMB_X || 
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
	case DIK_LEFT:
		_isPressKeyLeft = 1;
		_direct = LEFT;
		if (_isClimbingY == true && (_currentAction == CLIMB_Y ||
			_currentAction == CLIMB_ATTACK || _currentAction == CLIMB_THROW))
		{
			break;
		}
		else if (_isClimbingX == true && (_currentAction == CLIMB_X ||
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
			{
				Jump();
				_position.x += 10;
				break;
				
			}
			if (_isPressKeyLeft)
			{
				Jump();
				_position.x += -10;
				break;
			}
			else
			{
				Jump();
				break;
			}	
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
		else if(_currentAction == STAND)
			StandAttack();
		break;
	case DIK_S:
		if (_currentAction == SIT)
		{
			CreateApple();
			SitThrow();
		}
		else if (_currentAction == CLIMB_X_STOP || _currentAction == CLIMB_Y)
		{
			CreateApple();
			ClimbThrow();
		}
		else if (_currentAction == RUN_JUMP)
		{
			CreateApple();
			RunJumpThrow();
		}
		else if(_currentAction == STAND)
		{
			CreateApple();
			StandThrow();
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

	if (_currentAction == SIT_ATTACK || _currentAction == SIT_THROW)
	{
		//Chuyen ve frame cuoi cung
		_listAction[_currentAction].SetIndex(_listAction[_currentAction].GetTotalFrame() - 1);
	}
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
	_vx = _direct*VELOCITY_X;
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

void AladdinCharacter::CreateApple()
{
	int xApple;
	int yApple;
	float vxApple;
	float vyApple;

	//Toa do ban dau cua apple
	xApple = this->_position.x;
	yApple = this->_position.y;

	vxApple = _direct*APPLE_VX;
	vyApple = 0;

	D3DXVECTOR3 posApple = D3DXVECTOR3(xApple, yApple, 0);

	_myApple = new Apple(posApple, vxApple, vyApple);

}

void AladdinCharacter::SetListAction()
{
	_listAction[0].Create(RUN_PATH, 715, 55, 13, 0.07f, RIGHT);
	_listAction[1].Create(STOP_PATH, 495, 55, 9, 0.05f, RIGHT);
	_listAction[2].Create(STAND_PATH, 935, 55, 17, 0.1f, RIGHT);
	_listAction[3].Create(STAND_ATTACK_PATH, 275, 55, 5, 0.1f, RIGHT);
	_listAction[4].Create(STAND_THROW_PATH, 330, 55, 6, 0.1f, RIGHT);
	_listAction[5].Create(SIT_PATH, 220, 55, 4, 0.1f, RIGHT);
	_listAction[6].Create(SIT_ATTACK_PATH, 385, 55, 7, 0.1f, RIGHT);
	_listAction[7].Create(SIT_THROW_PATH, 275, 55, 5, 0.1f, RIGHT);
	_listAction[8].Create(JUMP_PATH, 550, 55, 10, 0.05f, RIGHT);
	_listAction[9].Create(LOOK_UP_PATH, 165, 55, 3, 0.1f, RIGHT);
	_listAction[10].Create(CLIMB_Y_PATH, 550, 55, 10, 0.05f, RIGHT);
	_listAction[11].Create(JUMP_PATH, 550, 55, 10, 0.1f, RIGHT);
	_listAction[12].Create(RUN_JUMP_PATH, 495, 55, 9, 0.1f, RIGHT);
	_listAction[13].Create(JUMP_THROW_PATH, 275, 55, 5, 0.1f, RIGHT);
	_listAction[14].Create(JUMP_ATTACK_PATH, 330, 55, 6, 0.1f, RIGHT);
	_listAction[15].Create(CLIMB_X_PATH, 550, 55, 10, 0.1f, LEFT);
	_listAction[16].Create(CLIMB_ATTACK_PATH, 385, 55, 7, 0.1f, LEFT);
	_listAction[17].Create(CLIMB_THROW_PATH, 550, 55, 5, 0.1f, LEFT);
	_listAction[18].Create(CLIMB_X_STOP_PATH, 550, 55, 5, 0.15f, LEFT);
}

void AladdinCharacter::Draw(float time)
{
	this->_transform._positionInViewport = this->GetPositionInViewport();
	D3DXVECTOR3 cameraPosition = Viewport::getInstance()->getViewPortPositon(Camera::getInstance()->GetPosition());
	this->_transform._translation = D3DXVECTOR2(-cameraPosition.x, -cameraPosition.y);

	if (_currentAction == JUMP)
	{
		int c = 0;
	}

	this->_listAction[_currentAction].Draw(_transform._positionInViewport, this->_direct, time, D3DXVECTOR2(2.2, 2.5), _transform._translation);

	if (_myApple)
		_myApple->Draw(time);
}
