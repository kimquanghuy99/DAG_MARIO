#pragma once
#include "GameObject.h"
#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f


#define KOOPA_BBOX_WIDTH 18
#define KOOPA_BBOX_HEIGHT 24
#define KOOPA_BBOX_HEIGHT_SHELL 14
#define KOOPA_BBOX_WIDTH_SHELL 16

#define KOOPA_DIE_TIMEOUT 2000

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_SHELL 200

#define ID_ANI_KOOPA_WALKING 6000
#define ID_ANI_KOOPA_SHELL 6001


#define KOOPA_JUMP_DEFLECT_SPEED	0.2f
#define KOOPA_ROLLING_SPEED			0.1f

class CKoopa : public CGameObject
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
	CKoopa(float x, float y);
	virtual void SetState(int state);
};