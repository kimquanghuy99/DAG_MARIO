#pragma once
#include "GameObject.h"

#define PLANT_GRAVITY 0.002f
#define PLANT_WALKING_SPEED 0.02f


#define PLANT_BBOX_WIDTH 17
#define PLANT_BBOX_HEIGHT 22
#define PLANT_BBOX_HEIGHT_DIE 7

#define PLANT_DIE_TIMEOUT 5000

#define PLANT_STATE_WALKING 100
#define PLANT_STATE_DIE 200

#define ID_ANI_PLANT_WALKING 7000
#define ID_ANI_PLANT_DIE 7001

class CPlant : public CGameObject
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
	CPlant(float x, float y);
	virtual void SetState(int state);
};