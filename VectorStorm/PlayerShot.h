#pragma once

#ifndef __PLAYER_SHOT_H__
#define __PLAYER_SHOT_H__

#include "Shot.h"


class PlayerShot : public Shot
{
public:
	PlayerShot();
	~PlayerShot();
	void Init(float x, float y, int segmentIdx);
	void Draw() override;
	void Update(float dt) override;
	bool Collide(Point2Df center, float radius) override;
protected:
	float distance;
};

#endif
