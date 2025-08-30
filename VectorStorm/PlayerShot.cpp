#define _USE_MATH_DEFINES
#include <cmath>
#include "PlayerShot.h"
#include "Models.h"
#include "Level.h"

const float SHOT_SPEED = 200.0f;
const float SPIN_TIME = 0.5;
const float SHOT_RADIUS = 3.0f;

PlayerShot::PlayerShot() : Shot()
{
	alive = true;
	angle = 0.0f;
	direction = 0.0f;
	distance = 0.0f;
	speed = SHOT_SPEED;
	x = 0.0f;
	y = 0.0f;
}

PlayerShot::~PlayerShot()
{

}

void PlayerShot::Init(float x, float y, int segmentIdx)
{
	Point2Df aBegin, aEnd, bBegin, bEnd;
	int idx = (segmentIdx - 1) % levels[levelIdx]->points.size();
	aBegin = levels[levelIdx]->points[segmentIdx];
	aEnd = levels[levelIdx]->pointsInner[segmentIdx];
	bBegin = levels[levelIdx]->points[idx];
	bEnd = levels[levelIdx]->pointsInner[idx];

	Point2Df begin, end;
	begin.x = aBegin.x + ((bBegin.x - aBegin.x) / 2.0);
	begin.y = aBegin.y + ((bBegin.y - aBegin.y) / 2.0);
	end.x = aEnd.x + ((bEnd.x - aEnd.x) / 2.0);
	end.y = aEnd.y + ((bEnd.y - aEnd.y) / 2.0);

	float dx = end.x - x;
	float dy = end.y - y;

	this->angle = 2.0 * M_PI * ((float)rand() / (float)RAND_MAX);
	this->direction = atan2f(dy, dx);
	this->distance = sqrt(dx * dx + dy * dy);
	this->x = begin.x;
	this->y = begin.y;
	
}

void PlayerShot::Draw()
{
	if (!alive)
		return;

	playerShot.x = x;
	playerShot.y = y;
	playerShot.angle = angle;
	playerShot.Draw();
}

void PlayerShot::Update(float dt)
{
	if (!alive)
		return;

	angle += SPIN_TIME * 2.0 * M_PI * dt;
	while (angle > (2.0 * M_PI))
		angle -= (2.0 * M_PI);

	x += speed * dt * cos(direction);
	y += speed * dt * sin(direction);
	distance -= speed * dt;

	if (distance <= 0.0f || x < 0.0f || x >= (float)SCREEN_WIDTH || y < 0.0f || y >= (float)SCREEN_HEIGHT)
		alive = false;
}

bool PlayerShot::Collide(Point2Df center, float radius)
{
	float dx = abs(x - center.x);
	float dy = abs(y - center.y);

	return ((dx * dx) + (dy * dy) < (radius * radius));
}