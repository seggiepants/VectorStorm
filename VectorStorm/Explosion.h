#pragma once
#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#define _USE_MATH_DEFINES
#include <cmath>
#include <list>
#include <SDL.h>
#include "Globals.h"
#include "Utility.h"

const float PARTICLE_SPEED = 100.0f;

class Particle
{
public:
	Particle();
	~Particle();
	void Init(float x, float y, SDL_Color color, float lifeTime, float direction, float size);
	void Update(float dt);
	void Draw();
	bool IsAlive();

private:
	bool alive;
	float x;
	float y;
	float lifeTime;
	float direction;
	SDL_Color color;
	Point2Df points[3];
};

class Explosion
{
public:
	Explosion();
	~Explosion();
	void Init(float x, float y, SDL_Color color, float lifeTime, int maxCount, int blockSize);
	void Update(float dt, std::list<Particle*>* storage);
	bool IsAlive() { return lifeTime > 0.0f && generated < maxCount; };
private:
	float x, y, lifeTime;
	int maxCount, blockSize;
	int generated;
	SDL_Color color;
};

#endif
