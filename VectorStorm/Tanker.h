#pragma once
#ifndef __TANKER_H__
#define __TANKER_H__

#include "Enemy.h"
#include "Utility.h"

class Tanker : public Enemy
{
public:
	Tanker();
	~Tanker();
	void Init(Point2Df start, Point2Df finish);
	void Update(float dt) override;
	void Draw() override;
private:
	Point2Df start;
	Point2Df finish;
	float shootCooldown;
	float climbTime;
	float angle;
};

#endif
