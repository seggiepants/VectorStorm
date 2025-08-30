#include <cmath>
#include <SDL.h>
#include "Models.h"
#include "Tanker.h"
#include "Level.h"

const float CLIMB_TIME = 3.0;
const float SPIN_TIME = 1.0;
const float COOLDOWN_MAX = 3.0;

const long TANKER_DESTROY_POINTS = 10;

Tanker::Tanker() : Enemy()
{
	climbTime = 0.0f;
	angle = 0.0f;
	segmentIdx = 0;
	shootCooldown = ((float)rand() / (float)RAND_MAX) * COOLDOWN_MAX;
}

Tanker::~Tanker()
{

}

void Tanker::Init(int segmentIdx)
{
	this->segmentIdx = segmentIdx;
	climbTime = 0.0f;
	angle = 2.0 * M_PI * ((float)rand() / (float)RAND_MAX);



	int idx = (this->segmentIdx + 1) % levels[levelIdx]->points.size();
	Point2Df aBegin, aEnd, bBegin, bEnd;
	aBegin = levels[levelIdx]->pointsInner[this->segmentIdx];
	bBegin = levels[levelIdx]->pointsInner[idx];
	aEnd = levels[levelIdx]->points[this->segmentIdx];
	bEnd = levels[levelIdx]->points[idx];
	Point2Df begin, end;
	begin.x = aBegin.x + ((bBegin.x - aBegin.x) / 2.0);
	begin.y = aBegin.y + ((bBegin.y - aBegin.y) / 2.0);
	end.x = aEnd.x + ((bEnd.x - aEnd.x) / 2.0);
	end.y = aEnd.y + ((bEnd.y - aEnd.y) / 2.0);

	this->start = begin;
	this->finish = end;
	this->x = begin.x;
	this->y = begin.y;
}

void Tanker::Update(float dt)
{
	climbTime += dt;
	angle += SPIN_TIME * 2.0 * M_PI * dt;
	while (angle > (2.0 * M_PI))
		angle -= (2.0 * M_PI);

	shootCooldown -= dt;

	if (climbTime >= CLIMB_TIME)
	{
		/*
		x = finish.x;
		y = finish.y;
		alive = false;
		*/
		Respawn();
	}
	else
	{
		x = start.x + ((finish.x - start.x) * (climbTime / CLIMB_TIME));
		y = start.y + ((finish.y - start.y) * (climbTime / CLIMB_TIME));
	}

}

EnemyShot* Tanker::SpawnShot()
{
	if (shootCooldown <= 0.0f)
	{
		shootCooldown = COOLDOWN_MAX;
		EnemyShot* shot = new EnemyShot();
		shot->Init(x, y, segmentIdx);
		return shot;
	}
	return nullptr;
}

void Tanker::Draw()
{
	tanker.x = x;
	tanker.y = y;
	tanker.angle = angle;
	tanker.Draw();
}

float Tanker::GetRadius()
{
	return tanker.GetRadius();
}

long Tanker::Hit()
{
	alive = false;
	if (sfx[AudioClips::ENEMY_DESTROY] != nullptr)
	{
		Mix_PlayChannel(-1, sfx[AudioClips::ENEMY_DESTROY], 0);
	}
	return TANKER_DESTROY_POINTS;
}

bool Tanker::Collide(Point2Df center, float radius)
{
	float dx = abs(x - center.x);
	float dy = abs(y - center.y);

	return ((dx * dx) + (dy * dy) < (radius * radius));
}

void Tanker::Respawn()
{
	int segmentIdx = rand() % levels[levelIdx]->points.size();
	Init(segmentIdx);
	alive = true;
}