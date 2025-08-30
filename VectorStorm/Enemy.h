#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Shot.h"

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();
	virtual void Update(float dt);
	virtual void Draw();
	bool IsDead() { return !alive; }
	virtual Shot* SpawnShot() = 0;
	float x, y;
	virtual float GetRadius() = 0;
	virtual long Hit() = 0;
	virtual bool Collide(Point2Df centerX, float radius) = 0;
	virtual void Respawn() = 0;
protected:
	float angle;
	bool alive;
};

#endif
