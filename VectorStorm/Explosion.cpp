#include "Explosion.h"

Particle::Particle() { 
	Init(0.0, 0.0, WHITE, 5.0, 0.0, 4.0); 
}

Particle::~Particle() 
{
}

void Particle::Init(float x, float y, SDL_Color color, float lifeTime, float direction, float size)
{
	this->x = x;
	this->y = y;
	this->color = color;
	this->lifeTime = lifeTime;
	this->direction = direction;
	this->alive = true;

	float offset = M_PI * 2.0f * ((float)rand() / (float)RAND_MAX);
	float step = (2.0 / 3.0) * M_PI; // 60 degrees
	for (int i = 0; i < 3; i++)
	{
		points[i].x = size * cos(offset + (step * i));
		points[i].y = size * sin(offset + (step * i));
	}
}

void Particle::Update(float dt)
{
	lifeTime -= dt;
	if (lifeTime <= 0.0f)
		alive = false;

	float dx = dt * PARTICLE_SPEED * cos(direction);
	float dy = dt * PARTICLE_SPEED * sin(direction);
	this->x += dx;
	this->y += dy;

	if (this->x < 0 || this->x > SCREEN_WIDTH || this->y < 0 || this->y > SCREEN_HEIGHT)
		alive = false;
}

void Particle::Draw()
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_Vertex verts[3];
	for (int i = 0; i < 3; i++)
	{
		verts[i].position.x = this->x + this->points[i].x;
		verts[i].position.y = this->y + this->points[i].y;
		verts[i].color = color;
		verts[i].tex_coord.x = 0.0f;
		verts[i].tex_coord.y = 0.0f;
	}
	SDL_RenderGeometry(renderer, nullptr, verts, 3, nullptr, 3);
}

bool Particle::IsAlive() { 
	return alive; 
}

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
			float angle = 2.0 * M_PI * ((float)rand() / (float)RAND_MAX);
			float dx = 4.0f * cos(angle);
			float dy = 4.0f * sin(angle);
			p->Init(x + dx, y + dy, color, 0.25, angle, 4.0f);
			storage->push_back(p);
			numAdded++;
		}
		generated += numAdded;
		lifeTime -= dt;
	}
}