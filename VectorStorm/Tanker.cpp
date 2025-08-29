#include <cmath>
#include <SDL.h>
#include "Models.h"
#include "Tanker.h"

const float CLIMB_TIME = 3.0;
const float SPIN_TIME = 1.0;

Tanker::Tanker() : Enemy()
{
	climbTime = 0.0f;
	angle = 0.0f;
}

Tanker::~Tanker()
{

}

void Tanker::Init(Point2Df start, Point2Df finish)
{
	this->start = start;
	this->finish = finish;
	this->x = start.x;
	this->y = start.y;
	climbTime = 0.0f;
	angle = 2.0 * M_PI * ((float)rand() / (float)RAND_MAX);
}

void Tanker::Update(float dt)
{
	climbTime += dt;
	angle += SPIN_TIME * 2.0 * M_PI * dt;
	while (angle > (2.0 * M_PI))
		angle -= (2.0 * M_PI);

	if (climbTime >= CLIMB_TIME)
	{
		x = finish.x;
		y = finish.y;
		alive = false;
	}
	else
	{
		x = start.x + ((finish.x - start.x) * (climbTime / CLIMB_TIME));
		y = start.y + ((finish.y - start.y) * (climbTime / CLIMB_TIME));
	}

}

void Tanker::Draw()
{
	tanker.x = x;
	tanker.y = y;
	tanker.angle = angle;
	tanker.Draw();
}
