#pragma once
#ifndef __LEVEL_H__
#include <list>
#include <tuple>
#include <vector>
#include <SDL.h>
#include "Utility.h"
#include "Enemy.h"
#include "Tanker.h"


class Level
{
public:
	bool closedShape;
	std::vector<Point2Df> points;
	std::vector<Point2Df> pointsInner;
	std::list<std::tuple<float, char>> enemyList;
	std::list<std::tuple<float, char>> enemyListBase;
	SDL_Color color;	
	Level();
	~Level();
	void Update(float dt);
	void Draw();
	void Init();
	Enemy* SpawnEnemy();
	bool AllEnemiesSpawned();
private:
	float levelTime;
};

extern std::vector<Level*> levels;
extern int levelIdx;

void LevelInit();
void LevelDestroy();

#endif