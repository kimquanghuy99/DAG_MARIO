#include "Plant.h"
#include "Coin.h"

CPlant::CPlant(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = PLANT_GRAVITY;
	die_start = -1;
	SetState(PLANT_STATE_WALKING);
}

void CPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == PLANT_STATE_DIE)
	{
		left = x - PLANT_BBOX_WIDTH / 2;
		top = y - PLANT_BBOX_HEIGHT_DIE / 2;
		right = left + PLANT_BBOX_WIDTH;
		bottom = top + PLANT_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - PLANT_BBOX_WIDTH / 2;
		top = y - PLANT_BBOX_HEIGHT / 2;
		right = left + PLANT_BBOX_WIDTH;
		bottom = top + PLANT_BBOX_HEIGHT;
	}
}

void CPlant::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPlant*>(e->obj)) return;

	if (e->ny != 0)
	{
		//vx = 0;
		vy = 0;
	}
	else if (e->nx != 0)
	{
		//vy = -vy;
		vx = -vx;
	}
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	if ((state == PLANT_STATE_DIE) && (GetTickCount64() - die_start > PLANT_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	vx = 0;

	if (vy > 0 && y > 369) {
		y = 369; vy = -vy;
	}
	if (vy < 0 && y < 369 - 22) {
		y = 369 - 22; vy = -vy;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPlant::Render()
{
	int aniId = ID_ANI_PLANT_WALKING;
	if (state == PLANT_STATE_DIE)
	{
		aniId = ID_ANI_PLANT_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	RenderBoundingBox();
}

void CPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PLANT_STATE_DIE:
		die_start = GetTickCount64();
		y += (PLANT_BBOX_HEIGHT - PLANT_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case PLANT_STATE_WALKING:
		//vx = -PLANT_WALKING_SPEED;
		vy = -PLANT_WALKING_SPEED;
		break;
	}
}
