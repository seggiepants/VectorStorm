#pragma once

#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

#include <string>
#include <vector>
#include <SDL.h>
#include "Scene.h"
#include "VectorFont.h"

class SceneTitle : public Scene
{
public:
	SceneTitle();
	~SceneTitle();
	void Init() override;
	Scene* Update(float dt) override;
	void Draw() override;
private:
	VectorFont* font;
	bool up, down, left, right;
	std::vector<std::string> menuItems;
	int menuIndex;
};

#endif
