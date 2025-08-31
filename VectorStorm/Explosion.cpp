#include "Explosion.h"

Explosion::Explosion()
{
	Init(0.0f, 0.0f, WHITE, 2.0f, 200, 10);
}

Explosion::~Explosion()
{

}

void Explosion::Init(float x, float y, SDL_Color color, float lifeTime, int maxCount, int blockSize)
{
	this->x = x;
	this->y = y;
	this->color = color;
	this->lifeTime = lifeTime;
	this->maxCount = maxCount;
	this->blockSize = blockSize;
	this->generated = 0;
}

void Explosion::Update(float dt, std::list<Particle*>* storage)
{
	if (lifeTime > 0.0f)
	{
		int numAdded = 0;
		while (numAdded < blockSize && generated + numAdded < maxCount)
		{
			Particle* p = new Particle();
			p->Init(x, y, color, 0.25, 2.0 * M_PI * ((float)rand() / (float)RAND_MAX), 4.0f);
			storage->push_back(p);
			numAdded++;
		}
		generated += numAdded;
		lifeTime -= dt;
	}
}