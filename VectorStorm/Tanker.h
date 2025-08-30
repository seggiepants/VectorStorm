#pragma once
#ifndef __TANKER_H__
#define __TANKER_H__

#include "Enemy.h"
#include "EnemyShot.h"
#include "Utility.h"

class Tanker : public Enemy
{
public:
	Tanker();
	~Tanker() override;
	void Init(int segmentIdx);
	void Update(float dt) override;
	void Draw() override;
	EnemyShot* SpawnShot() override;
	float GetRadius() override;
	long Hit() override;
	bool Collide(Point2Df centerX, float radius) override;
	void Respawn() override;
private:
	Point2Df start;
	Point2Df finish;
	float shootCooldown;
	float climbTime;
	float angle;
	int segmentIdx;
};

#endif
