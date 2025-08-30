#define _USE_MATH_DEFINES
#include <cmath>
#include "EnemyShot.h"
#include "Level.h"
#include "Models.h"

const float SHOT_SPEED = 250.0f;
const float SPIN_TIME = 0.125;
const float SHOT_RADIUS = 3.0f;

EnemyShot::EnemyShot() : Shot()
{
	alive = true;
	angle = 0.0f;
	distance = 0.0f;
	direction = 0.0f;
	speed = SHOT_SPEED;
	x = 0.0f;
	y = 0.0f;
}

EnemyShot::~EnemyShot()
{

}

void EnemyShot::Init(float x, float y, int segmentIdx)
{
	Point2Df aBegin, aEnd, bBegin, bEnd;
	int idx = (segmentIdx + 1) % levels[levelIdx]->points.size();
	aEnd = levels[levelIdx]->points[segmentIdx];
	bEnd = levels[levelIdx]->points[idx];
	this->x = x;
	this->y = y;	

	Point2Df end;
	end.x = aEnd.x + ((bEnd.x - aEnd.x) / 2.0);
	end.y = aEnd.y + ((bEnd.y - aEnd.y) / 2.0);

	float dx = end.x - x;
	float dy = end.y - y;

	this->angle = 2.0 * M_PI * ((float)rand() / (float)RAND_MAX);
	this->direction = atan2f(dy, dx);
	this->distance = sqrt(dx * dx + dy * dy);
}

void EnemyShot::Draw()
{
	if (!alive)
		return;

	enemyShot.x = x;
	enemyShot.y = y;
	enemyShot.angle = angle;	
	enemyShot.Draw();
}

void EnemyShot::Update(float dt)
{
	if (!alive)
		return;

	angle += SPIN_TIME * 2.0 * M_PI * dt;
	while (angle > (2.0 * M_PI))
		angle -= (2.0 * M_PI);

	distance -= (speed * dt);
	x += speed * dt * cos(direction);
	y += speed * dt * sin(direction);

	if (distance <= 0.0f || x < 0.0f || x >= (float)SCREEN_WIDTH || y < 0.0f || y >= (float)SCREEN_HEIGHT)
		alive = false;
}

bool EnemyShot::Collide(Point2Df center, float radius)
{
	float dx = abs(x - center.x);
	float dy = abs(y - center.y);

	return ((dx * dx) + (dy * dy) < (radius * radius));
}