#include "Goomba1.h"

CGoomba1::CGoomba1(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA1_GRAVITY;
	die_start = -1;
	SetState(GOOMBA1_STATE_WALKING);
}

void CGoomba1::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA1_STATE_DIE)
	{
		left = x - GOOMBA1_BBOX_WIDTH / 2;
		top = y - GOOMBA1_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA1_BBOX_WIDTH;
		bottom = top + GOOMBA1_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - GOOMBA1_BBOX_WIDTH / 2;
		top = y - GOOMBA1_BBOX_HEIGHT / 2;
		right = left + GOOMBA1_BBOX_WIDTH;
		bottom = top + GOOMBA1_BBOX_HEIGHT;
	}
}

void CGoomba1::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba1::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba1*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == GOOMBA1_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA1_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba1::Render()
{
	int aniId = ID_ANI_GOOMBA1_WALKING;
	if (state == GOOMBA1_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA1_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CGoomba1::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA1_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA1_BBOX_HEIGHT - GOOMBA1_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA1_STATE_WALKING:
		//vx = 0;
		vx = -GOOMBA1_WALKING_SPEED;
		break;
	}
}
