#pragma once

#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

#include <SDL.h>
#include "Scene.h"

class SceneTitle : public Scene
{
public:
	SceneTitle();
	Scene* Update(float dt) override;
	void Draw() override;
private:
	bool up, down, left, right;
	// Declare rect of square
	SDL_Rect squareRect;
};

#endif
