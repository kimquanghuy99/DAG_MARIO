#pragma once
#include "GameObject.h"

#define GOOMBA1_GRAVITY 0.002f
#define GOOMBA1_WALKING_SPEED 0.05f


#define GOOMBA1_BBOX_WIDTH 16
#define GOOMBA1_BBOX_HEIGHT 14
#define GOOMBA1_BBOX_HEIGHT_DIE 7

#define GOOMBA1_DIE_TIMEOUT 500

#define GOOMBA1_STATE_WALKING 100
#define GOOMBA1_STATE_DIE 200

#define ID_ANI_GOOMBA1_WALKING 5100
#define ID_ANI_GOOMBA1_DIE 5101

class CGoomba1 : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CGoomba1(float x, float y);
	virtual void SetState(int state);
};