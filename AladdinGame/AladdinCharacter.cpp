#include "AladdinCharacter.h"

AladdinCharacter::AladdinCharacter()
{
	type = PLAYER;
}

AladdinCharacter::~AladdinCharacter()
{
}

AladdinCharacter* AladdinCharacter::instance = 0;

AladdinCharacter* AladdinCharacter::getInstance()
{
	if (!instance)
	{
		instance = new AladdinCharacter();
	}
	return instance;
}

void AladdinCharacter::Init(HINSTANCE hInstance, HWND hWnd)
{
	this->hInstance = hInstance;
	this->hWnd = hWnd;
	this->id = CHARACTER;
	this->type = PLAYER;
	this->currentAction = STAND;
	this->direct = RIGHT;
	this->x = 500;
	this->y = 360;
	this->isClimbingY = false;
	this->isFalling = false;
	this->isJumping = false;
	this->listAction = new Animation[19];
	this->InitKeyBoard(hInstance, hWnd);
	SetListAction();
}

void AladdinCharacter::UpdateAction()
{
	if (listAction[currentAction].Update(TimeGame::getInstance()->currentTime) == 0)
	{
		isActionDone = false;
	}
	else
	{
		isActionDone = true;
	}
}

void AladdinCharacter::UpdatePosition(float time)
{
	this->x += vx*time;
	this->y += vy*time;

}

void AladdinCharacter::Draw(float time)
{
	D3DXVECTOR3 position;
	position.x = x;
	position.y = y;
	position.z = 0;
	listAction[currentAction].Draw(position, direct, time);
}

void AladdinCharacter::Update(float time)
{
	this->ProcessKeyBoard(hWnd);
	UpdatePosition(time);

	#pragma region Giu frame cuoi cua state ngoi/nhin len
	if ((currentAction == SIT || currentAction == LOOK_UP) && listAction[currentAction].GetIndex() == (listAction[currentAction].GetTotalFrame() - 1))
	{
		listAction[currentAction].SetIndex(listAction[currentAction].GetIndex() - 1);
	}

	#pragma endregion
	
	#pragma region Dung yen sau khi stop
	if (currentAction == STOP && listAction[currentAction].GetIndex() == 4)
	{
		a = 0;
		vx = 0;
	}
	if (currentAction == STOP && listAction[currentAction].GetIndex() == (listAction[currentAction].GetTotalFrame() - 1))
	{
		Stand();
	}
	#pragma endregion

	#pragma region Roi xuong Jump - RunJump - JumpAttack - JumpThrow
	if ((currentAction == JUMP || currentAction == RUN_JUMP || currentAction == JUMP_ATTACK || currentAction == JUMP_THROW) && vy < 0)
	{
		if (currentAction == JUMP)
		{
			if (listAction[currentAction].GetIndex() == 6)
			{
				listAction[currentAction].SetIndex(6);
			}
		}
		if (currentAction == RUN_JUMP || currentAction == JUMP_ATTACK || currentAction == JUMP_THROW)
		{
			if (listAction[currentAction].GetIndex() == (listAction[currentAction].GetTotalFrame() - 1))
			{
				listAction[currentAction].SetIndex(listAction[currentAction].GetTotalFrame() - 1);
			}
		}
		vy += GRAVITY;
		if (press_key_run)
		{
			vx = direct*VELOCITY_X;
		}
	}
	else if ((currentAction == JUMP || currentAction == RUN_JUMP || currentAction == JUMP_ATTACK || currentAction == JUMP_THROW ||currentAction == FALLING) && vy >= 0)
	{
		a += GRAVITY;
		vy = VELOCITY_Y + a;
		isFalling = true;
		isClimbingY = false;
		if (!press_key_run)
		{
			vx = 0;
		}
	}

	if (isFalling)
	{
		if (currentAction == RUN_JUMP || currentAction == JUMP_ATTACK || currentAction == JUMP_THROW)
		{
			if (currentAction == RUN_JUMP || currentAction == JUMP_ATTACK || currentAction == JUMP_THROW)
			{
				if (listAction[currentAction].GetIndex() == (listAction[currentAction].GetTotalFrame() - 1))
				{
					listAction[currentAction].SetIndex(listAction[currentAction].GetTotalFrame() - 1);
				}
			}
			if (y >= 360)
			{
				y = 360;
				vy = 0;
				isJumping = false;
				isClimbingY = false;
				isFalling = false;
				if (press_key_run)
				{
					currentAction = RUN;
					vx = direct * VELOCITY_X;
				}
				else
				{
					Stand();
				}
			}
		}
		else if (currentAction == JUMP || currentAction == FALLING)
		{
			listAction[currentAction].SetIndex(6);
			if (y >= 360)
			{
				y = 360;
				isJumping = false;
				isClimbingY = false;
				isFalling = false;
				Stand();
			}
		}
	}
	#pragma endregion

	#pragma region Hoan thanh state chem/nem tap  roi moi dung len
	if ((currentAction == STAND_ATTACK || currentAction == STAND_THROW) && listAction[currentAction].GetIndex() == (listAction[currentAction].GetTotalFrame() - 1))
		Stand();
	
	if ((currentAction == SIT_ATTACK || currentAction == SIT_THROW) && listAction[currentAction].GetIndex() == (listAction[currentAction].GetTotalFrame() - 1))
	{
		if (press_key_sit)
		{
			Sit();
		}
		else
			Stand();
	}
	#pragma endregion

	#pragma region Kiem tra va cham/leo day Y
	if (!isClimbingY && x >= 535 && x <= 539 && y > 10)
	{
		ClimbY();
	}

	if (currentAction == CLIMB_Y && !press_key_lookup && !press_key_sit)
	{
		currentIndex = listAction[currentAction].GetIndex();
		listAction[currentAction].SetIndex(6);
	}
	if (currentAction == CLIMB_Y)
	{
		if (y >= 360)
			y = 360;
		if (y <= 10)
			ClimbXStop();
	}
	#pragma endregion

#pragma region Hoan thanh state chem/nem tap  roi moi leo/rot
	
	if ((currentAction == CLIMB_ATTACK || currentAction == CLIMB_THROW) && listAction[currentAction].GetIndex() == (listAction[currentAction].GetTotalFrame() - 1))
	{
		if (isClimbingY == true)
		{
			ClimbY();
		}
		else
			ClimbXStop();
	}
	
#pragma endregion

}

void AladdinCharacter::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
	case DIK_DOWN:
		press_key_sit = 0;
		if (currentAction == JUMP || currentAction == FALLING || currentAction == RUN_JUMP)
			break;
		else if (currentAction == SIT_ATTACK || currentAction == SIT_THROW) //Neu bang frame cuoi thi dung len luon
		{
			if (listAction[currentAction].GetIndex() == (listAction[currentAction].GetTotalFrame() - 1))
			{
				Stand();
			}
			break;
				
		}
		else if (currentAction == CLIMB_Y || currentAction == CLIMB_ATTACK || currentAction == CLIMB_THROW)
		{
			vy = 0;
			break;
		}
		else
		{
			Stand();
			break;
		}
		
	case DIK_UP:
		press_key_lookup = 0;
		if (currentAction == JUMP || currentAction == FALLING || currentAction == RUN_JUMP)
			break;
		else if (currentAction == CLIMB_Y || currentAction == CLIMB_X || currentAction == CLIMB_X_STOP || currentAction == CLIMB_ATTACK || currentAction == CLIMB_THROW) {
			vy = 0;
			break;
		}
		Stand();
		break;
	case DIK_RIGHT:
		press_key_run = 0;
		if (currentAction == CLIMB_X) {
			ClimbXStop();
			break;
		}
		else if (isClimbingY == true && (currentAction == CLIMB_Y || currentAction == CLIMB_ATTACK || currentAction == CLIMB_THROW))
		{
			break;
		}
		Stop();
		break;
	case DIK_LEFT:
		press_key_run = 0;
		if (currentAction == CLIMB_X) {
			ClimbXStop();
			break;
		}
		else if (isClimbingY == true && (currentAction == CLIMB_Y || currentAction == CLIMB_ATTACK || currentAction == CLIMB_THROW))
		{
			break;
		}
		Stop();
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
	UpdateAction();
	switch (keyCode)
	{
	case DIK_DOWN:
		press_key_sit = 1;
		if (currentAction == CLIMB_Y) {
			vy = 80.0f;
			break;
		}
		else if (currentAction == CLIMB_X || currentAction == CLIMB_X_STOP) {
			Falling();
			break;
		}
		Sit();
		break;
	case DIK_UP:
		press_key_lookup = 1;
		if (currentAction == CLIMB_Y) {
			vy = -80.0f;
			break;
		}
		LookUp();
		break;
	case DIK_RIGHT:
		press_key_run = 1;
		direct = RIGHT;
		if (isClimbingY == true && (currentAction == CLIMB_Y || currentAction == CLIMB_ATTACK || currentAction == CLIMB_THROW))
		{
			break;
		}
		else if (currentAction == CLIMB_X || currentAction == CLIMB_X_STOP || currentAction == CLIMB_ATTACK || currentAction == CLIMB_THROW) {
			vx = direct * VELOCITY_X;
			ClimbX();
			break;
		}
		Run();
		break;
	case DIK_LEFT:
		press_key_run = 1;
		direct = LEFT;
		if (isClimbingY == true && (currentAction == CLIMB_Y || currentAction == CLIMB_ATTACK || currentAction == CLIMB_THROW))
		{
			break;
		}
		else if (currentAction == CLIMB_X || currentAction == CLIMB_X_STOP || currentAction == CLIMB_ATTACK || currentAction == CLIMB_THROW) {
			vx = direct * VELOCITY_X;
			ClimbX();
			break;
		}
		Run();
		break;
	case DIK_D:
		if (currentAction == RUN)
		{
			RunJump();
			break;
		}
		else if (currentAction == STOP)
		{
			break;
		}
		else if (isClimbingY && (currentAction == CLIMB_Y || currentAction == CLIMB_ATTACK || currentAction == CLIMB_THROW))
		{
			if(press_key_run && direct > 0)
			{
				Jump();
				x += 20;
				isClimbingY = false;
				break;
				
			}
			if (press_key_run && direct < 0)
			{
				Jump();
				x += -20;
				isClimbingY = false;
				break;
			}
			else
			{
				Jump();
				break;
			}	
		}
		else
		{
			Jump();
			break;
		}
	case DIK_A:
		if (currentAction == SIT)
		{
			SitAttack();
		}
		else if (currentAction == CLIMB_X_STOP || currentAction == CLIMB_Y)
		{
			ClimbAttack();
		}
		else if (currentAction == RUN_JUMP)
		{
			RunJumpAttack();
		}
		else
			StandAttack();
		break;
	case DIK_S:
		if (currentAction == SIT)
		{
			SitThrow();
		}
		else if (currentAction == CLIMB_X_STOP || currentAction == CLIMB_Y)
		{
			ClimbThrow();
		}
		else if (currentAction == RUN_JUMP)
		{
			RunJumpThrow();
		}
		else
			StandThrow();
		break;
	}
	
}

void AladdinCharacter::Run()
{
	if (currentAction == SIT || currentAction == LOOK_UP || currentAction == RUN_JUMP || currentAction == JUMP_ATTACK)
	{
		return;
	}
	else if (currentAction == JUMP || currentAction == FALLING)
	{
		vx = direct * VELOCITY_X;
	}
	else
	{
		currentAction = RUN;
		vx = direct * VELOCITY_X;
		listAction[currentAction].SetIndex(0);
	}
	return;
}

void AladdinCharacter::Stop()
{
	if (currentAction == RUN)
	{
		a = -(direct * ACCELERATOR);
		vx += a;
		currentAction = STOP;
		listAction[currentAction].SetIndex(0);
	}
	return;
}

void AladdinCharacter::Stand()
{
	a = 0;
	vx = 0;
	vy = 0;
	isClimbingY = false;
	isJumping = false;
	isFalling = false;
	currentAction = STAND;
	listAction[currentAction].SetIndex(0);
}

void AladdinCharacter::StandAttack()
{
	if (currentAction == STAND)
	{
		currentAction = STAND_ATTACK;
		listAction[currentAction].SetIndex(0);
	}
	return;
	
}

void AladdinCharacter::StandThrow()
{
	if (currentAction == STAND)
	{
		currentAction = STAND_THROW;
		listAction[currentAction].SetIndex(0);
	}
	return;
}

void AladdinCharacter::Sit()
{
	if (currentAction == STAND)
	{
		currentAction = SIT;
		listAction[currentAction].SetIndex(0);
	}
	else if (currentAction == SIT_ATTACK || currentAction == SIT_THROW)
	{
		currentAction = SIT;
		listAction[currentAction].SetIndex(listAction[currentAction].GetTotalFrame()-1);
	}
	else
		return;
}

void AladdinCharacter::SitAttack()
{
	if (currentAction == SIT)
	{
		currentAction = SIT_ATTACK;
		listAction[currentAction].SetIndex(0);
	}
	return;
}

void AladdinCharacter::SitThrow()
{
	if (currentAction == SIT)
	{
		currentAction = SIT_THROW;
		listAction[currentAction].SetIndex(0);
	}
	return;
}

void AladdinCharacter::Jump()
{
	if (!isJumping)
	{
		vy = -VELOCITY_Y;
		currentAction = JUMP;
		isJumping = true;
		listAction[currentAction].SetIndex(0);
	}
	return;
}

void AladdinCharacter::RunJump() 
{
	if (!isJumping) {
		vy = -VELOCITY_Y;
		vx = direct*VELOCITY_X;
		isJumping = true;
		currentAction = RUN_JUMP;
		listAction[currentAction].SetIndex(0);
	}
	return;
}

void AladdinCharacter::RunJumpAttack() 
{
	if (currentAction == RUN_JUMP)
	{
		currentAction = JUMP_ATTACK;
		listAction[currentAction].SetIndex(0);
	}
	return;
}

void AladdinCharacter::RunJumpThrow()
{
	if (currentAction == RUN_JUMP)
	{
		currentAction = JUMP_THROW;
		listAction[currentAction].SetIndex(0);
	}
	return;
}

void AladdinCharacter::Falling()
{
	
	vy = VELOCITY_Y;
	currentAction = FALLING;
	isFalling = true;
	listAction[currentAction].SetIndex(1);
	
}

void AladdinCharacter::LookUp()
{
	if (currentAction == STAND)
	{
		currentAction = LOOK_UP;
		listAction[currentAction].SetIndex(0);
	}
	else
		return;
}

void AladdinCharacter::ClimbY()
{
	isClimbingY = true;
	isFalling = false;
	isJumping = false;
	currentAction = CLIMB_Y;
	vx = 0;
	vy = 0;
	listAction[currentAction].SetIndex(0);
}

void AladdinCharacter::ClimbX()
{
	isClimbingY = false;
	currentAction = CLIMB_X;
	vy = 0;
	listAction[currentAction].SetIndex(0);
}

void AladdinCharacter::ClimbXStop()
{
	currentAction = CLIMB_X_STOP;
	isClimbingY = false;
	vx = 0;
	vy = 0;
	listAction[currentAction].SetIndex(0);
}

void AladdinCharacter::ClimbAttack()
{
	if (currentAction == CLIMB_X_STOP  || (currentAction == CLIMB_Y && !press_key_lookup && !press_key_sit))
	{
		currentAction = CLIMB_ATTACK;
		listAction[currentAction].SetIndex(0);
	}
	return;
}

void AladdinCharacter::ClimbThrow()
{
	if (currentAction == CLIMB_X_STOP || (currentAction == CLIMB_Y && (!press_key_lookup && !press_key_sit)))
	{
		currentAction = CLIMB_THROW;
		listAction[currentAction].SetIndex(0);
	}
	return;
}

void AladdinCharacter::SetListAction()
{
	listAction[0].Create(RUN_PATH, 715, 55, 13, 0.06f, RIGHT);
	listAction[1].Create(STOP_PATH, 495, 55, 9, 0.06f, RIGHT);
	listAction[2].Create(STAND_PATH, 935, 55, 17, 0.1f, RIGHT);
	listAction[3].Create(STAND_ATTACK_PATH, 275, 55, 5, 0.1f, RIGHT);
	listAction[4].Create(STAND_THROW_PATH, 330, 55, 6, 0.1f, RIGHT);
	listAction[5].Create(SIT_PATH, 220, 55, 4, 0.1f, RIGHT);
	listAction[6].Create(SIT_ATTACK_PATH, 385, 55, 7, 0.1f, RIGHT);
	listAction[7].Create(SIT_THROW_PATH, 275, 55, 5, 0.1f, RIGHT);
	listAction[8].Create(JUMP_PATH, 550, 55, 10, 0.06f, RIGHT);
	listAction[9].Create(LOOK_UP_PATH, 165, 55, 3, 0.1f, RIGHT);
	listAction[10].Create(CLIMB_Y_PATH, 550, 55, 10, 0.05f, RIGHT);
	listAction[11].Create(JUMP_PATH, 550, 55, 10, 0.1f, RIGHT);
	listAction[12].Create(RUN_JUMP_PATH, 495, 55, 9, 0.1f, RIGHT);
	listAction[13].Create(JUMP_THROW_PATH, 275, 55, 5, 0.1f, RIGHT);
	listAction[14].Create(JUMP_ATTACK_PATH, 330, 55, 6, 0.1f, RIGHT);
	listAction[15].Create(CLIMB_X_PATH, 550, 55, 10, 0.1f, LEFT);
	listAction[16].Create(CLIMB_ATTACK_PATH, 385, 55, 7, 0.1f, LEFT);
	listAction[17].Create(CLIMB_THROW_PATH, 275, 55, 5, 0.1f, LEFT);
	listAction[18].Create(CLIMB_X_STOP_PATH, 275, 55, 5, 0.15f, LEFT);

}
