#pragma once
#ifndef __VECTOR_FONT_H__
#define __VECTOR_FONT_H__
#include <map>
#include <string>
#include <vector>
#include <SDL.h>
#include "Utility.h"

class VectorFont
{
public:
	VectorFont();
	~VectorFont();
	void Construct(float scaleX, float scaleY);
	void DrawText(std::string message, int x, int y, SDL_Color color);
	void MeasureText(std::string message, int* width, int* height);
protected:
	std::map<char, std::vector<std::vector<Point2Df>>>* characters;
	float scaleX, scaleY;
};

#endif

