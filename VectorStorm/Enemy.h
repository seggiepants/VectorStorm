#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

class Enemy
{
public:
	Enemy();
	~Enemy();
	virtual void Update(float dt);
	virtual void Draw();
	bool IsDead() { return !alive; }
protected:
	float x, y;
	float angle;
	bool alive;
};

#endif
