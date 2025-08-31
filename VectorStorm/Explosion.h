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
	Particle() { Init(0.0, 0.0, WHITE, 5.0, 0.0, 4.0); };
	~Particle() {};
	void Init(float x, float y, SDL_Color color, float lifeTime, float direction, float size)
	{
		this->x = x;
		this->y = y;
		this->color = color;
		this->lifeTime = lifeTime;
		this->direction = direction;
		bool alive = true;

		float offset = M_PI * 2.0f * ((float)rand() / (float)RAND_MAX);
		float step = (2.0 / 3.0) * M_PI; // 60 degrees
		for (int i = 0; i < 3; i++)
		{
			points[i].x = size * cos(offset + (step * i));
			points[i].y = size * sin(offset + (step * i));
		}
	};
	void Update(float dt)
	{
		lifeTime -= dt;
		if (lifeTime <= 0.0f)
			alive = false;

		x += dt * PARTICLE_SPEED * cos(direction);
		y += dt * PARTICLE_SPEED * sin(direction);

		if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT)
			alive = false;
	};

	void Draw()
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		std::vector<SDL_Vertex> verts;
		for (int i = 0; i < 3; i++)
		{
			SDL_Vertex v;
			v.position.x = x + points[i].x;
			v.position.y = y + points[i].y;
			v.color = color;
			verts.push_back(v);
		}
		SDL_RenderGeometry(renderer, nullptr, verts.data(), verts.size(), nullptr, 0);
	};

	bool IsAlive() { return alive; };

private:
	bool alive;
	float x, y, lifeTime, direction;
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
