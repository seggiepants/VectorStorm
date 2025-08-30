#pragma once

#ifndef __ENEMY_SHOT_H__
#define __ENEMY_SHOT_H__

#include "Shot.h"


class EnemyShot : public Shot
{
public:
	EnemyShot();
	~EnemyShot();
	void Init(float x, float y, int segmentIdx);
	void Draw() override;
	void Update(float dt) override;
	bool Collide(Point2Df center, float radius) override;
protected:
	float distance;
};

#endif
