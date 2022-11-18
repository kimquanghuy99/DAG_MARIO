#include "Brick3.h"

void CBrick3::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	// simple fall down
	vy += BRICK3_GRAVITY * dt;

	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	DebugOutTitle(L"vx = %0.5f", this->vx);


	// BAD & sinful platform collision handling, see next sample for correct collision handling
	if (y > GROUND_Y)
	{
		vy = 0; y = GROUND_Y;
	}

	// simple screen edge collision!!!
	if (vx > 0 && x > 290) x = 290;
	if (vx < 0 && x < 0) x = 0;
}

void CBrick3::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	// Mario is still on air check, this will not work when Mario is just stand up
	if (y < GROUND_Y)
	{
		if (abs(ax) == BRICK3_ACCEL_RUN_X) // TODO: need to optimize this
		{
			if (nx >= 0)
				aniId = ID_ANI_BRICK3_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_BRICK3_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_BRICK3_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_BRICK3_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_BRICK3_SIT_RIGHT;
			else
				aniId = ID_ANI_BRICK3_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_BRICK3_IDLE_RIGHT;
				else aniId = ID_ANI_BRICK3_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_BRICK3_BRACE_RIGHT;
				else if (ax == BRICK3_ACCEL_RUN_X)
					aniId = ID_ANI_BRICK3_RUNNING_RIGHT;
				else if (ax == BRICK3_ACCEL_WALK_X)
					aniId = ID_ANI_BRICK3_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_BRICK3_BRACE_LEFT;
				else if (ax == -BRICK3_ACCEL_RUN_X)
					aniId = ID_ANI_BRICK3_RUNNING_LEFT;
				else if (ax == -BRICK3_ACCEL_WALK_X)
					aniId = ID_ANI_BRICK3_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_BRICK3_IDLE_RIGHT;

	float d = 0;
	if (isSitting) d = BRICK3_SIT_HEIGHT_ADJUST;

	animations->Get(aniId)->Render(x, y + d);
}

void CBrick3::SetState(int state)
{
	switch (state)
	{
	case BRICK3_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = BRICK3_RUNNING_SPEED;
		ax = BRICK3_ACCEL_RUN_X;
		nx = 1;
		break;
	case BRICK3_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -BRICK3_RUNNING_SPEED;
		ax = -BRICK3_ACCEL_RUN_X;
		nx = -1;
		break;
	case BRICK3_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = BRICK3_WALKING_SPEED;
		ax = BRICK3_ACCEL_WALK_X;
		nx = 1;
		break;
	case BRICK3_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -BRICK3_WALKING_SPEED;
		ax = -BRICK3_ACCEL_WALK_X;
		nx = -1;
		break;
	case BRICK3_STATE_JUMP:
		if (isSitting) break;
		if (y == GROUND_Y)
		{
			if (abs(this->vx) == BRICK3_RUNNING_SPEED)
				vy = -BRICK3_JUMP_RUN_SPEED_Y;
			else
				vy = -BRICK3_JUMP_SPEED_Y;
		}
		break;

	case BRICK3_STATE_RELEASE_JUMP:
		if (vy < 0) vy += BRICK3_JUMP_SPEED_Y / 2;
		break;

	case BRICK3_STATE_SIT:
		if (y == GROUND_Y)
		{
			state = BRICK3_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0;
			//y += BRICK3_SIT_HEIGHT_ADJUST;
		}
		break;

	case BRICK3_STATE_SIT_RELEASE:
		isSitting = false;
		state = BRICK3_STATE_IDLE;
		//y -= BRICK3_SIT_HEIGHT_ADJUST;
		break;

	case BRICK3_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;
	}

	CGameObject::SetState(state);
}

