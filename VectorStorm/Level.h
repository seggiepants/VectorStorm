#pragma once
#ifndef __LEVEL_H__
#include <vector>
#include <SDL.h>
#include "Utility.h"


class Level
{
public:
	bool closedShape;
	std::vector<Point2Df> points;
	std::vector<Point2Df> pointsInner;
	SDL_Color color;	
};

extern std::vector<Level*> levels;
extern int levelIdx;

void LevelInit();
void LevelDestroy();

#endif