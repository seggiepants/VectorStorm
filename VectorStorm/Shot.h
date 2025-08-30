#pragma once
#ifndef __SHOT_H__
#define __SHOT_H__

#include "Utility.h"

class Shot
{
public:
	Shot() { alive = true; x = 0.0f; y = 0.0f; angle = 0.0f, direction = 0.0f; speed = 0.0f; }
	~Shot() {}
	virtual void Draw() {}
	virtual void Update(float dt) {}
	virtual bool Collide(Point2Df center, float radius) = 0;	
	bool IsDead() { return !alive; };
	void Destroy() { alive = false; }
protected:
	bool alive;
	float x, y;
	float angle;
	float direction;
	float speed;
};

#endif
