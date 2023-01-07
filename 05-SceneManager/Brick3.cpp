#include "Brick3.h"

void CBrick3::Render()
{
	//CAnimations* animations = CAnimations::GetInstance();
	RenderBoundingBox();
}

void CBrick3::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - w / 2;
	t = y - h / 2;
	r = l + w;
	b = t + h;
}