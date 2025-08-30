#pragma once
#ifndef __MODELS_H__

#include <vector>
#include <SDL.h>
#include "Globals.h"
#include "Utility.h"

class Model
{
public:
	Model();
	void Draw();
	float x, y;
	float scaleX, scaleY;
	std::vector<Point2Df> points;
	std::vector<Point3Di> triangles;
	SDL_Color color;
	float angle;
	float GetRadius();
private:
	SDL_Vertex ProjectPoint(Point2Df point);
};

extern Model player;
extern Model playerShot;
extern Model tanker;
extern Model enemyShot;

void ModelInit();

#endif